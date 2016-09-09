// ======================================================================
//
// Copyright (c) 2001 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/Convex_hull_projective_xz_traits_2.h
// package       : Convex_hull_2 (3.34)
// revision      : $Revision: 1.5 $
// revision_date : $Date: 2001/07/20 09:21:19 $
// author(s)     : Susan Hert
//
// coordinator   : MPI, Saarbruecken
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CONVEX_HULL_PROJECTIVE_XZ_TRAITS_2_H
#define CONVEX_HULL_PROJECTIVE_XZ_TRAITS_2_H

#include <CGAL/predicates/kernel_ftC2.h>
#include <CGAL/predicates_on_points_2.h>
#include <CGAL/functional_base.h>
#include <CGAL/function_objects.h>

namespace CGAL {

template <class Point_3>
class Less_xy_plane_xz_2 
{
public:
   typedef bool           result_type;
   typedef Arity_tag<2>   Arity;

   bool 
   operator()(const Point_3& p, const Point_3& q) const
   { 
      return 
        compare_lexicographically_xyC2(p.x(), p.z(), q.x(), q.z()) == SMALLER;
   }
};

template <class Point_3>
class Less_yx_plane_xz_2 
{
public:
   typedef bool           result_type;
   typedef Arity_tag<2>   Arity;

   bool 
   operator()(const Point_3& p, const Point_3& q) const
   { 
      return 
        compare_lexicographically_xyC2(p.z(), p.x(), q.z(), q.x()) == SMALLER;
   }
};

template <class Point_3>
class Left_turn_plane_xz_2 
{
public:
   typedef bool           result_type;
   typedef Arity_tag<2>   Arity;

   bool 
   operator()(const Point_3& p, const Point_3& q, const Point_3& r) const
   { 
    return orientationC2(p.x(), p.z(), q.x(), q.z(), r.x(), r.z()) == LEFTTURN;
   }
};


template <class Point_3>
class Less_dist_to_line_plane_xz_2
{
public:
   typedef bool           result_type;
   typedef Arity_tag<4>   Arity;

   bool
   operator()(const Point_3& p, const Point_3& q,
              const Point_3& r, const Point_3& s) const
   {
      Comparison_result
         res = cmp_signed_dist_to_lineC2(p.x(), p.z(), q.x(), q.z(),
                                         r.x(), r.z(), s.x(), s.z());
      if ( res == LARGER )
         return false;
      else if ( res == SMALLER )
         return true;
      else
         return compare_lexicographically_xyC2(r.x(), r.z(), s.x(), s.z())
             == SMALLER;
   }
};


template <class Point_3>
class Less_rotate_ccw_plane_xz_2
{
public:

   typedef bool         result_type;
   typedef Arity_tag<3> Arity;

   bool
   operator()(const Point_3& r, const Point_3& p, const Point_3& q) const
   {
      Orientation orient =
               orientationC2(r.x(), r.z(), p.x(), p.z(), q.x(), q.z());
      if ( orient ==  LEFTTURN )
         return true;
      else if ( orient == RIGHTTURN )
         return false;
      else
      {
         if (p.x() == r.x() && p.z() == r.z()) return false;
         if (q.x() == r.x() && q.z() == r.z()) return true;
         if (p.x() == q.x() && p.z() == q.z()) return false;
         return
            collinear_are_ordered_along_lineC2(r.x(), r.z(),
                                               q.x(), q.z(), p.x(), p.z());
      }
   }

};



template <class Point_3>
class Convex_hull_projective_xz_traits_2 
{
public:
    typedef Point_3                             Point_2;
    typedef Less_xy_plane_xz_2<Point_3>         Less_xy_2;
    typedef Less_yx_plane_xz_2<Point_3>         Less_yx_2;
    typedef Left_turn_plane_xz_2<Point_3>       Leftturn_2;
    typedef Less_rotate_ccw_plane_xz_2<Point_3> Less_rotate_ccw_2;
    typedef Less_dist_to_line_plane_xz_2<Point_3> 
                                                Less_signed_distance_to_line_2;

    Less_xy_2
    less_xy_2_object() const
    {  return Less_xy_2(); }

    Less_yx_2
    less_yx_2_object() const
    {  return Less_yx_2(); }

    Leftturn_2
    leftturn_2_object() const
    {  return Leftturn_2(); }

    Less_rotate_ccw_2
    less_rotate_ccw_2_object() const
    {  return Less_rotate_ccw_2(); }

    Less_signed_distance_to_line_2
    less_signed_distance_to_line_2_object() const
    {  return Less_signed_distance_to_line_2(); }

};

}
#endif // CONVEX_HULL_PROJECTIVE_XZ_TRAITS_2_H
