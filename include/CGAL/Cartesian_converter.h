// Copyright (c) 2001-2004  
// Utrecht University (The Netherlands),
// ETH Zurich (Switzerland),
// INRIA Sophia-Antipolis (France),
// Max-Planck-Institute Saarbruecken (Germany),
// and Tel-Aviv University (Israel).  All rights reserved. 
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; either version 3 of the License,
// or (at your option) any later version.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-4.14-beta1/Cartesian_kernel/include/CGAL/Cartesian_converter.h $
// $Id: Cartesian_converter.h 319893b %aI Maxime Gimeno
// SPDX-License-Identifier: LGPL-3.0+
// 
//
// Author(s)     : Sylvain Pion
//                 Menelaos Karavelas <mkaravel@cse.nd.edu>

#ifndef CGAL_CARTESIAN_CONVERTER_H
#define CGAL_CARTESIAN_CONVERTER_H

// This file contains the definition of a kernel converter, based on Cartesian
// representation.  It should work between *Cartesian<A> and *Cartesian<B>,
// provided you give a NT converter from A to B.
// There's a Homogeneous counterpart.

#include <CGAL/Cartesian_converter_fwd.h>
#include <CGAL/basic.h>
#include <CGAL/NT_converter.h>
#include <CGAL/Enum_converter.h>
#include <CGAL/Bbox_2.h>
#include <CGAL/Bbox_3.h>
#include <CGAL/Origin.h>
#include <CGAL/Kernel/Type_mapper.h>
#include <vector>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/logical.hpp>
#include <boost/mpl/remove.hpp>

namespace CGAL {

// Guess which compiler needs this work around ?
// ... VC++, again!
namespace internal {
template < typename K1, typename K2 >
struct Default_converter {
  typedef typename K1::FT FT1;
  typedef typename K2::FT FT2;
  typedef ::CGAL::NT_converter<FT1, FT2> Type;
};

// Out will be a variant, source kernel and target kernel
template<typename Converter, typename Output>
struct Converting_visitor : boost::static_visitor<> {
  Converting_visitor(const Converter& conv, Output& out) : conv(&conv), out(&out) {}
  const Converter* conv;
  Output* out;

  template<typename T>
  void operator()(const T& t) { *out = conv->operator()(t); }

  template<typename T>
  void operator()(const std::vector<T>& t) {
    typedef typename 
      Type_mapper< T, typename Converter::Source_kernel, 
                   typename Converter::Target_kernel >::type 
    value_type;
    
    std::vector< value_type > tmp;
    tmp.reserve(t.size());
    for(typename std::vector< T >::const_iterator it = t.begin();
        it !=  t.end(); ++it) {
      tmp.push_back(conv->operator()(*it));
    }
    
    *out = tmp;
  }
};

} // namespace internal

template < class K1, class K2,
//          class Converter = NT_converter<typename K1::FT, typename K2::FT> >
           class Converter>
class Cartesian_converter : public Enum_converter
{
    typedef Enum_converter   Base;
    typedef Cartesian_converter Self;
public:
    typedef K1         Source_kernel;
    typedef K2         Target_kernel;
    typedef Converter  Number_type_converter;

    using Base::operator();

    Origin
    operator()(const Origin& o) const
    {
        return o;
    }

    Null_vector
    operator()(const Null_vector& n) const
    {
        return n;
    }

    Bbox_2
    operator()(const Bbox_2& b) const
    {
        return b;
    }

    Bbox_3
    operator()(const Bbox_3& b) const
    {
        return b;
    }

    typename K2::FT
    operator()(const typename K1::FT &a) const
    {
        return c(a);
    }

    // drop the boost::detail::variant::void_ generated by the macros
    // from the sequence, transform with the type mapper and throw the
    // new list into a variant
    // visit to get the type, and copy construct inside the return type 
    template<BOOST_VARIANT_ENUM_PARAMS(typename U)>
    typename
    Type_mapper< boost::optional< boost::variant< BOOST_VARIANT_ENUM_PARAMS(U) > >,
                 K1, K2 >::type
    operator()(const boost::optional< boost::variant< BOOST_VARIANT_ENUM_PARAMS(U) > >& o) const {
      typedef typename 
        Type_mapper< boost::optional< boost::variant< BOOST_VARIANT_ENUM_PARAMS(U) > >,
                     K1, K2 >::type result_type;
      result_type res;
      if(!o) {
        // empty converts to empty
        return res;
      }

      internal::Converting_visitor<Self, result_type> 
        conv_visitor = internal::Converting_visitor<Self, result_type>(*this, res);
      boost::apply_visitor(conv_visitor, *o);
      return res;
    }

    template<BOOST_VARIANT_ENUM_PARAMS(typename U)>
    typename
    Type_mapper< boost::variant< BOOST_VARIANT_ENUM_PARAMS(U) >,
                 K1, K2 >::type
    operator()(const boost::variant< BOOST_VARIANT_ENUM_PARAMS(U) > & o) const {
      typedef typename 
        Type_mapper< boost::variant< BOOST_VARIANT_ENUM_PARAMS(U) >,
                     K1, K2 >::type result_type;
      result_type res;
      internal::Converting_visitor<Self, result_type> 
        conv_visitor = internal::Converting_visitor<Self, result_type>(*this, res);
      boost::apply_visitor(conv_visitor, o);
      return res;
    }

    typename K2::Object_2
    operator()(const typename K1::Object_2 &obj) const
    {
#define CGAL_Kernel_obj(X) \
      if (const typename K1::X * ptr = object_cast<typename K1::X>(&obj)) \
        return make_object(operator()(*ptr));

#include <CGAL/Kernel/interface_macros.h>

#define CGAL_Kernel_obj(X) \
      if (const std::vector<typename K1::X> * ptr = object_cast<std::vector<typename K1::X> >(&obj)) { \
	std::vector<typename K2::X> res; \
        res.reserve((*ptr).size()); \
	for(unsigned int i=0; i < (*ptr).size(); i++){ \
	  res.push_back(operator()((*ptr)[i])); \
	} \
	return make_object(res); \
      }

      CGAL_Kernel_obj(Point_2)
      CGAL_Kernel_obj(Point_3)
#undef CGAL_Kernel_obj
       
      CGAL_error_msg("Cartesian_converter is unable to determine what is wrapped in the Object");
      return Object();
	
    }

    std::vector<Object>
    operator()(const std::vector<Object>& v) const
    {
      std::vector<Object> res;
      res.reserve(v.size());
      for(unsigned int i = 0; i < v.size(); i++) {
        res.push_back(operator()(v[i]));
      }
      return res;
    }


    typename K2::Point_2
    operator()(const typename K1::Point_2 &a) const
    {
        typedef typename K2::Point_2 Point_2;
	return Point_2(c(a.x()), c(a.y()));
    }

    typename K2::Weighted_point_2
    operator()(const typename K1::Weighted_point_2 &a) const
    {
        typedef typename K2::Weighted_point_2 Weighted_point_2;
	return Weighted_point_2(operator()(a.point()), operator()(a.weight()));
    }

    typename K2::Vector_2
    operator()(const typename K1::Vector_2 &a) const
    {
        typedef typename K2::Vector_2  Vector_2;
	return Vector_2(c(a.x()), c(a.y()));
    }

    typename K2::Direction_2
    operator()(const typename K1::Direction_2 &a) const
    {
        typedef typename K2::Direction_2  Direction_2;
	return Direction_2(c(a.dx()), c(a.dy()));
    }

    typename K2::Segment_2
    operator()(const typename K1::Segment_2 &a) const
    {
        typedef typename K2::Segment_2  Segment_2;
	return Segment_2(operator()(a.source()), operator()(a.target()));
    }

    typename K2::Line_2
    operator()(const typename K1::Line_2 &a) const
    {
        typedef typename K2::Line_2 Line_2;
	return Line_2(c(a.a()), c(a.b()), c(a.c()));
    }

    typename K2::Ray_2
    operator()(const typename K1::Ray_2 &a) const
    {
        typedef typename K2::Ray_2  Ray_2;
	return Ray_2(operator()(a.source()), operator()(a.second_point()));
    }

    typename K2::Circle_2
    operator()(const typename K1::Circle_2 &a) const
    {
        typedef typename K2::Circle_2  Circle_2;
	return Circle_2(operator()(a.center()),
		        c(a.squared_radius()),
			K1().orientation_2_object()(a));
    }

    typename K2::Triangle_2
    operator()(const typename K1::Triangle_2 &a) const
    {
        typedef typename K2::Triangle_2  Triangle_2;
	return Triangle_2(operator()(a.vertex(0)),
		          operator()(a.vertex(1)),
		          operator()(a.vertex(2)));
    }

    typename K2::Iso_rectangle_2
    operator()(const typename K1::Iso_rectangle_2 &a) const
    {
        typedef typename K2::Iso_rectangle_2  Iso_rectangle_2;
	return Iso_rectangle_2(operator()((a.min)()), operator()((a.max)()), 0);
    }


    typename K2::Point_3
    operator()(const typename K1::Point_3 &a) const
    {
        typedef typename K2::Point_3 Point_3;
	return Point_3(c(a.x()), c(a.y()), c(a.z()));
    }

    typename K2::Weighted_point_3
    operator()(const typename K1::Weighted_point_3 &a) const
    {
        typedef typename K2::Weighted_point_3 Weighted_point_3;
	return Weighted_point_3((*this)(a.point()), c(a.weight()));
    }

    typename K2::Vector_3
    operator()(const typename K1::Vector_3 &a) const
    {
        typedef typename K2::Vector_3  Vector_3;
	return Vector_3(c(a.x()), c(a.y()), c(a.z()));
    }

    typename K2::Direction_3
    operator()(const typename K1::Direction_3 &a) const
    {
        typedef typename K2::Direction_3  Direction_3;
	return Direction_3(c(a.dx()), c(a.dy()), c(a.dz()));
    }

    typename K2::Segment_3
    operator()(const typename K1::Segment_3 &a) const
    {
        typedef typename K2::Segment_3  Segment_3;
	return Segment_3(operator()(a.source()), operator()(a.target()));
    }

    typename K2::Line_3
    operator()(const typename K1::Line_3 &a) const
    {
        typedef typename K2::Line_3  Line_3;
	return Line_3(operator()(a.point()), operator()(a.to_vector()));
    }

    typename K2::Ray_3
    operator()(const typename K1::Ray_3 &a) const
    {
        typedef typename K2::Ray_3 Ray_3;
	return Ray_3(operator()(a.source()), operator()(a.second_point()));
    }

    typename K2::Sphere_3
    operator()(const typename K1::Sphere_3 &a) const
    {
        typedef typename K2::Sphere_3  Sphere_3;
	return Sphere_3(operator()(a.center()),
		        c(a.squared_radius()),
			K1().orientation_3_object()(a));
    }

    typename K2::Circle_3
    operator()(const typename K1::Circle_3 &a) const
    {
        typedef typename K2::Circle_3  Circle_3;
	return Circle_3(operator()(a.diametral_sphere()),
			operator()(a.supporting_plane()),1);
    }

    typename K2::Triangle_3
    operator()(const typename K1::Triangle_3 &a) const
    {
        typedef typename K2::Triangle_3  Triangle_3;
	return Triangle_3(operator()(a.vertex(0)),
		          operator()(a.vertex(1)),
		          operator()(a.vertex(2)));
    }

    typename K2::Tetrahedron_3
    operator()(const typename K1::Tetrahedron_3 &a) const
    {
        typedef typename K2::Tetrahedron_3  Tetrahedron_3;
	return Tetrahedron_3(operator()(a.vertex(0)),
		             operator()(a.vertex(1)),
		             operator()(a.vertex(2)),
		             operator()(a.vertex(3)));
    }

    typename K2::Plane_3
    operator()(const typename K1::Plane_3 &a) const
    {
        typedef typename K2::Plane_3  Plane_3;
	return Plane_3(c(a.a()), c(a.b()), c(a.c()), c(a.d()));
    }

    typename K2::Iso_cuboid_3
    operator()(const typename K1::Iso_cuboid_3 &a) const
    {
        typedef typename K2::Iso_cuboid_3 Iso_cuboid_3;
	return Iso_cuboid_3(operator()((a.min)()), operator()((a.max)()), 0);
    }

    std::pair<typename K2::Point_2, typename K2::Point_2>
    operator() (const std::pair<typename K1::Point_2, typename K1::Point_2>& pp) const
    {
      return std::make_pair(operator()(pp.first), operator()(pp.second));
    }

    typename K2::Aff_transformation_3
    operator()(const typename K1::Aff_transformation_3 &a) const
    {
        typedef typename K2::Aff_transformation_3 Aff_transformation_3;
      typename K2::FT t[12];
      for(int i=0; i< 3; ++i)
      {
        for(int j=0; j<4; ++j)
        {
          t[i*4+j] = a.m(i,j);
        }
      }
      return Aff_transformation_3(
            t[0],t[1],t[2],t[3],
            t[4],t[5],t[6],t[7],
            t[8],t[9],t[10],t[11],
            a.m(3,3));
    }
private:
    Converter c;
    K2 k;
};

// Specialization when converting to the same kernel,
// to avoid making copies.
template < class K, class C >
class Cartesian_converter <K, K, C>
{
public:
  typedef K Source_kernel;
  typedef K Target_kernel;
  typedef C Number_type_converter;

  template < typename T >
  const T& operator()(const T&t) const { return t; }
};

} //namespace CGAL

#endif // CGAL_CARTESIAN_CONVERTER_H
