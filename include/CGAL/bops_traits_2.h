// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
//
// This software and related documentation is part of the
// Computational Geometry Algorithms Library (CGAL).
//
// Every use of CGAL requires a license. Licenses come in three kinds:
//
// - For academic research and teaching purposes, permission to use and
//   copy the software and its documentation is hereby granted free of  
//   charge, provided that
//   (1) it is not a component of a commercial product, and
//   (2) this notice appears in all copies of the software and
//       related documentation.
// - Development licenses grant access to the source code of the library 
//   to develop programs. These programs may be sold to other parties as 
//   executable code. To obtain a development license, please contact
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.0
// release_date  : 1999, June 03
//
// file          : include/CGAL/bops_traits_2.h
// package       : bops (2.1.5)
// source        : include/CGAL/bops_traits_2.h
// revision      : $Revision: WIP $
// revision_date : $Date: Wed Dec  9 13:28:54 MET 1998  $
// author(s)     : Wolfgang Freiseisen
//
// coordinator   : RISC Linz
//  (Wolfgang Freiseisen)
//
// 
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef BOPS_TRAITS_2_H
#define BOPS_TRAITS_2_H
 
 
#include <CGAL/Cartesian.h> 
#include <CGAL/Homogeneous.h> 
#include <CGAL/basic.h> 
#include <list>
#include <CGAL/Object.h>
#include <CGAL/Point_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Triangle_2.h>
#include <CGAL/Iso_rectangle_2.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/Direction_2.h>

#include <CGAL/min_sqr_distance_traits.h>

CGAL_BEGIN_NAMESPACE

/*
    _R should be a representation class 
   (e.g. something like Cartesian<Rational> )
*/
template <class _R> 
struct Bops_default_I : public min_sqr_distance_traits<_R>
{
  Bops_default_I() {}

  /* representation class */
  //typedef _R R;
  typedef CGAL::Object                          Object;

  /*------ constant sized objects ------*/

  typedef CGAL::Bbox_2   Bbox;
  /* required operations:
     bool operator==(Bbox, Bbox);
  */

  bool do_overlap( const Bbox& a, const Bbox& b) const {
    return do_overlap(a,b);
  }

  bool box_is_contained_in_box( const Bbox& a, const Bbox& b) const {
    return xmin(b) <= xmin(a) &&
           xmax(b) >= xmax(a) &&
           ymin(b) <= ymin(a) &&
           ymax(b) >= ymax(a) ?  true : false;

  }


  typedef CGAL::Point_2<R>                      Point;
  /* required operations:
    R::NT Point::x() const
    R::NT Point::y() const
  */
  bool is_equal(const Point& p1, const Point& p2) const {
    return p1 == p2;
  }

  bool less_x(const Point& p1, const Point& p2) const {
    return p1.x() < p2.x();
  }
  

  typedef CGAL::Segment_2<R>                    Segment;
  /* required operations:
    Segment(Point,Point);
  */
  typedef CGAL::Triangle_2<R>                   Triangle;
  /* required operations:
    constructor with three points of type Point.
  */
  typedef CGAL::Iso_rectangle_2<R>              Iso_rectangle;
  /* required operations:
    constructor with three points of type Point.
  */

  /*------ non-constant sized objects ------*/
  typedef std::list<Object>                         Output_object_container;
  /* required operations:
     void Output_object_container::push_back(Object);
  */
  typedef std::list<Point>                          Container;
  typedef Container                            Input_polygon_container;
  typedef std::list<Point>                          Output_polygon_container;
  typedef Polygon_2<Polygon_traits_2<R>,Container>          Polygon;
  typedef Polygon                              Input_polygon;
  typedef typename Polygon::Vertex_const_iterator  
                   Polygon_vertex_const_iterator;
  /* required operations:
     Polygon_vertex_const_iterator Polygon::vertices_begin();
     Polygon_vertex_const_iterator Polygon::vertices_end();
  */
  typedef Polygon_2<Polygon_traits_2<R>,Output_polygon_container>
          Output_polygon;

  bool is_leftturn(const Point& p0, const Point& p1, const Point& p2) const {
    /* p0 ... origin */
    /* return direction_of(p0,p1) < direction_of(p0,p2);*/
    return leftturn(p0, p1, p2);
  }

  Object Make_object(const Point& p) const {
    return make_object(p);
  }
  Object Make_object(const Segment& seg) const {
    return make_object(seg);
  }
  Object Make_object(const Output_polygon& pgon) const {
    return make_object(pgon);
  }
  Object Make_object(const Iso_rectangle& irect) const {
    return make_object(irect);
  }
  Object Make_object(const Triangle& triangle) const {
    return make_object(triangle);
  }

  Bbox get_Bbox(const Polygon& pgon) const {
    return pgon.bbox();
  }

  bool has_on_bounded_side(const Polygon& pgon, const Point& pt) const {
    /* will be used if there is a better intersection algorithm implemented */
    //return pgon.has_on_bounded_side(pt);
    //return pgon.has_on_bounded_side(pt) || pgon.has_on_boundary(pt);
    return pgon.bounded_side(pt)==ON_UNBOUNDED_SIDE ? false : true;
  }
  void reverse_orientation(Polygon& pgon) const {
    pgon.reverse_orientation();
  }
  Polygon_vertex_const_iterator most_left_vertex(const Polygon& pgon) const {
    return pgon.left_vertex();
  }

  /* for intersection plug-in:
     -------------------------

     typedef Intersect_Polygons intersection_result;
     intersection_result Intersection(const Input_polygon& polygon_A,
                                      const Input_polygon& polygon_B)
     {
       return intersection_result(polygon_A, polygon_B);
     }
     int get_result( const intersection_result& result,
                     std::list<Point>&               point_list,
                     std::list<pair<int,int> >&      edge_list )
     {
        result.get_graph_information(point_list, edge_list);
     }
     int get_result_on_A( const intersection_result& result,
                          std::list<Point>&               point_list) {
        point_list= result.get_color_informationA();
     }
     int get_result_on_B( const intersection_result& result,
                          std::list<Point>&               point_list) {
        point_list= result.get_color_informationB();
     }
  */

  /* for nsquare-intersection algorithm:
     assign
     collinear_are_ordered_along_line
     compare_lexicographically_xy
     make_object
     do_intersect(Segment, Segment)
     intersection(Segment, Segment)
  */

protected:

  typedef CGAL::Direction_2<R>                  Direction;
  /* required operations:
     bool operator<(Direction, Direction);
  */

  Direction direction_of(const Point& from, const Point& to) const {
    return (to-from).direction();
  }

  double xmin(const Bbox& bbox) const { return bbox.xmin(); }
  double xmax(const Bbox& bbox) const { return bbox.xmax(); }
  double ymin(const Bbox& bbox) const { return bbox.ymin(); }
  double ymax(const Bbox& bbox) const { return bbox.ymax(); }

};

CGAL_END_NAMESPACE

#endif /* BOPS_TRAITS_2_H */