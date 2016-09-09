// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium
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
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// file          : include/CGAL/Pm_segment_epsilon_traits.h
// package       : pm (2.052)
// source        :
// revision      :
// revision_date :
// author(s)     : Iddo Hanniel
//                 Eyal Flato
//                 Oren Nechushtan
//
// coordinator   : Tel-Aviv University (Dan Halperin)
// chapter       : Planar Map
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_PM_SEGMENT_EPSILON_TRAITS_H
#define CGAL_PM_SEGMENT_EPSILON_TRAITS_H

#ifndef CGAL_PM_CONFIG_H
#include <CGAL/Pm_config.h>
#endif

#ifndef CGAL_POINT_2_H
#include <CGAL/Point_2.h>
#endif
#ifndef CGAL_SEGMENT_2_H
#include <CGAL/Segment_2.h>
#endif

#include <assert.h>
#include <math.h>

typedef double epsilon_type;

template <class R
#ifndef CGAL_CFG_NO_DEFAULT_TEMPLATE_ARGUMENTS 
, long numer = 1, long denom = 10000
#endif
>
class CGAL_Pm_segment_epsilon_traits
{
public:
  
  typedef CGAL_Segment_2<R>	X_curve;
  typedef CGAL_Point_2<R>		Point;
  typedef CGAL_Vector_2<R>		Vector;
  
  typedef enum 
  {		
    CURVE_VERTICAL_UP = 0,
    CURVE_VERTICAL_DOWN = 2,
    CURVE_LEFT = 3,
    CURVE_RIGHT = 1
  } Curve_status;  
  
  typedef enum
  {
    UNDER_CURVE = -1,
    ABOVE_CURVE = 1,
    ON_CURVE = 2,
    CURVE_NOT_IN_RANGE = 0,
  } Curve_point_status;
  
  
/*	
#ifdef _PM_TRAITS_WITH_INTERSECTIONS
typedef CGAL_Segment_2<R>      	Curve;
#endif
*/
  
public:
#ifndef CGAL_CFG_NO_DEFAULT_TEMPLATE_ARGUMENTS
  CGAL_Pm_segment_epsilon_traits()
  {
    epsilon_type eps = (double)(numer)/(double)(denom);
    EPSILON = eps;
  }
#else
  CGAL_Pm_segment_epsilon_traits(epsilon_type eps = 0.0001)
  {
    EPSILON = eps;
  }
#endif

private:
  epsilon_type EPSILON;
  
  
  
public:
  
  Point curve_source(const X_curve& cv) const
  { 
    return cv.source(); 
  }
  
  Point curve_target(const X_curve& cv) const
  {
    return cv.target(); 
  }
  
  
  
public:
  
  bool curve_is_vertical(const X_curve &cv) const 
  {
    return is_same_x(cv.source(), cv.target()); 
  }
  
  bool curve_is_in_x_range(const X_curve &cv, const Point& q) const
  { 
    return !( is_right(q, rightmost(cv.source(), cv.target())) ||
              is_left(q, leftmost(cv.source(), cv.target()))	 );
  }
  
  bool curve_is_in_y_range(const X_curve &cv, const Point& q) const
  { 
    bool r = !( is_lower(q, lowest(cv.source(), cv.target())) ||
                is_higher(q, highest(cv.source(), cv.target())) );
    return r;
  }
  

  Curve_point_status 
  curve_get_point_status(const X_curve &cv, const Point& p) const
  {
    if (!curve_is_in_x_range(cv, p))
      return CURVE_NOT_IN_RANGE;
	if (!curve_is_vertical(cv))
	{
	    int res = compare_y(p, curve_calc_point(cv, p));
	    if (res == CGAL_SMALLER) return UNDER_CURVE;
		if (res == CGAL_LARGER) return ABOVE_CURVE;
	    //if (res == CGAL_EQUAL) 
		return ON_CURVE;
	}
	else
	{
		if (is_lower(p,lowest(curve_source(cv),curve_target(cv))))
			return UNDER_CURVE;
		if (is_higher(p,highest(curve_source(cv),curve_target(cv))))
			return ABOVE_CURVE;
		// if (curve_is_in_y_range(cv,p))
		return ON_CURVE;
	}
  }
  
  
  bool is_point_on_curve(const X_curve &cv, const Point& p) const
  {
    if (!curve_is_in_x_range(cv, p))
      return false;
    if (curve_is_vertical(cv))
      {
        if (curve_is_in_y_range(cv,p))
          return true;
        else
          return false;
      }
    int res = compare_y(p, curve_calc_point(cv, p));
    if (res == CGAL_EQUAL)
      return true;
    return false;
  }
  


  CGAL_Comparison_result 
  curve_compare_at_x(const X_curve &cv1, const X_curve &cv2, const Point& q) 
    const 
  {
    if ((!curve_is_in_x_range(cv1, q)) || (!curve_is_in_x_range(cv2, q)))
      return CGAL_EQUAL;
    
    Point p1 = curve_calc_point(cv1, q);
    Point p2 = curve_calc_point(cv2, q);
    
    if (curve_is_vertical(cv1))
      {
        if (curve_is_vertical(cv2))
          {
            // both cv1 and cv2 are vertical
            if ( is_lower(cv1.target(), cv2.source()) )
              return CGAL_SMALLER;
            if ( is_higher(cv1.source(), cv2.target()) )
              return CGAL_LARGER;
            return CGAL_SMALLER;
          }
        // cv1 is vertical and cv2 not
        if ( is_lower(cv1.target(), p2) )
          return CGAL_SMALLER;
        if ( is_higher(cv1.source(), p2) )
          return CGAL_LARGER;
        return CGAL_EQUAL;
      }
    
    if (curve_is_vertical(cv2))
      {
        // cv2 is vertical and cv1 - not
        if (is_lower(cv2.target(), p1) )
          return CGAL_LARGER;
        if ( is_higher(cv2.source(), p1) )
          return CGAL_SMALLER;
        return CGAL_EQUAL;
      }
    
    // both are not vertical
    if (is_higher(p1, p2)) return CGAL_LARGER;
    if (is_lower(p1, p2)) return CGAL_SMALLER;
    return CGAL_EQUAL;
  }

 
  CGAL_Comparison_result 
  curve_compare_at_x_left(const X_curve &cv1, const X_curve &cv2, const Point& q) 
    const 
  {
    // cases  in which the function isn't defined
    //assert(!curve_is_vertical(cv1));
    //assert(!curve_is_vertical(cv2));
    //assert(is_left(leftmost(cv1.source(), cv1.target()), q));
    //assert(is_left(leftmost(cv2.source(), cv2.target()), q));
    
    if (curve_is_vertical(cv1) || (curve_is_vertical(cv2))) return CGAL_EQUAL;
    if (!is_left(leftmost(cv1.source(), cv1.target()), q)) return CGAL_EQUAL;
    if (!is_left(leftmost(cv2.source(), cv2.target()), q)) return CGAL_EQUAL;
    
    CGAL_Comparison_result r = curve_compare_at_x(cv1, cv2, q);
    
    if ( r != CGAL_EQUAL)
      return r;     // since the curve is continous 
    
    // <cv2> and <cv1> meet at a point with the same x-coordinate as q
    // compare their derivatives
    return compare_value(curve_derivative(cv2), curve_derivative(cv1));
  }
  
  CGAL_Comparison_result 
  curve_compare_at_x_right(const X_curve &cv1, const X_curve &cv2, const Point& q) 
    const 
  {
    // cases  in which the function isn't defined
    //assert(!curve_is_vertical(cv1));
    //assert(!curve_is_vertical(cv2));
    //assert(is_right(rightmost(cv1.source(), cv1.target()), q));
    //assert(is_right(rightmost(cv2.source(), cv2.target()), q));
    
    if (curve_is_vertical(cv1) || (curve_is_vertical(cv2))) return CGAL_EQUAL;
    if (!is_right(rightmost(cv1.source(), cv1.target()), q)) return CGAL_EQUAL;
    if (!is_right(rightmost(cv2.source(), cv2.target()), q)) return CGAL_EQUAL;
    
    CGAL_Comparison_result r = curve_compare_at_x(cv1, cv2, q);
    
    if ( r != CGAL_EQUAL)
      return r;     // since the curve is continous 
    
    // <cv1> and <cv2> meet at a point with the same x-coordinate as q
    // compare their derivatives
    return compare_value(curve_derivative(cv1), curve_derivative(cv2));
  }


  X_curve curve_flip(const X_curve &cv) const
  {
    return X_curve(cv.target(), cv.source());
  }
  
  
  Curve_status curve_get_status(const X_curve &cv) const
  {
    if (curve_is_vertical(cv)) 
      {
        if ( is_higher(cv.target(), cv.source()) )
          return CURVE_VERTICAL_UP;
        else
          return CURVE_VERTICAL_DOWN;
      }
    else
      {
        if ( is_right(cv.target(), cv.source()) )
          return CURVE_RIGHT;
        else
          return CURVE_LEFT;
      }
  }

  bool curve_is_between_cw(const X_curve &cv, 
                           const X_curve &first, 
                           const X_curve &second, 
                           const Point &point)	const
    // TRUE if cv is between first and second in cw direction
    // precondition: this, first and second have a common endpoint
    // precondition: first, second, this are pairwise interior disjoint
  {
    // assert(is_intersection_simple(first, second);
    // assert(is_intersection_simple(first, *this);
    // assert(is_intersection_simple(*this, second);
    
    Curve_status cv0_status, cv1_status, cvx_status;
    int cv0_cv1, cv0_cvx, cv1_cvx;
    cv0_cv1 = cv0_cvx = cv1_cvx = -1;
    
    Point cp = point;
    
    X_curve cv0 = first;
    X_curve cv1 = second;
    X_curve cvx = cv;

    if ( !is_same(cv0.source(),cp) ) cv0 = curve_flip(cv0);
    if ( !is_same(cv1.source(),cp) ) cv1 = curve_flip(cv1);
    if ( !is_same(cvx.source(),cp) ) cvx = curve_flip(cvx);

    cv0_status = curve_get_status(cv0);
    cv1_status = curve_get_status(cv1);
    cvx_status = curve_get_status(cvx);
    
    //	the circle:				    0
    //						 ** | **
    //						*	*
    //					     3 *	 * 1
    //						*	*
    //						 ** | **
    //						    2
    
    if (cv0_status == cv1_status)
      {
        if (cv0_status == CURVE_RIGHT)
          cv0_cv1 = curve_compare_at_x_right(cv0, cv1, cp);
        if (cv0_status == CURVE_LEFT)
          cv0_cv1 = curve_compare_at_x_left(cv0, cv1, cp);
      }
    if (cv0_status == cvx_status)
      {
        if (cv0_status == CURVE_RIGHT)
          cv0_cvx = curve_compare_at_x_right(cv0, cvx, cp);
        if (cv0_status == CURVE_LEFT)
          cv0_cvx = curve_compare_at_x_left(cv0, cvx, cp);
      }
    if (cv1_status == cvx_status)
      {
        if (cv1_status == CURVE_RIGHT)
          cv1_cvx = curve_compare_at_x_right(cv1, cvx, cp);
        if (cv1_status == CURVE_LEFT)
          cv1_cvx = curve_compare_at_x_left(cv1, cvx, cp);
      }
    
    if (cv0_status == cv1_status)
      {
        if (cv0_status == CURVE_LEFT)
          {
            if ( ((cv0_cv1==1) && (cvx_status==cv0_status) && 
                  ((cv0_cvx==-1) || (cv1_cvx==1))) ||
                 ((cv0_cv1==1) && (cvx_status!=cv0_status)) ||
                 ((cv0_cv1==-1) && (cvx_status==cv0_status) && 
                  ((cv0_cvx==-1) && (cv1_cvx==1))) )
              return true;
          }
        if (cv0_status == CURVE_RIGHT)
          {
            if ( ((cv0_cv1==1) && (cvx_status==cv0_status) && 
                  ((cv0_cvx==1) && (cv1_cvx==-1))) ||
                 ((cv0_cv1==-1) && (cvx_status!=cv0_status)) ||
                 ((cv0_cv1==-1) && (cvx_status==cv0_status) && 
                  ((cv0_cvx==1) || (cv1_cvx==-1))) )
              return true;
          }

        return false;
      }
    // else do the following
    
    if (cv0_status == cvx_status)
      {
        if ( ((cv0_status == CURVE_LEFT) && (cv0_cvx==-1)) ||
             ((cv0_status == CURVE_RIGHT) && (cv0_cvx==1)) )
          return true;

        //addition to prevent infinite loop in null segments - needs testing
        if ( (cv0_status==CURVE_VERTICAL_DOWN)&&
             ((cv0.source()==cv0.target())||(cvx.source()==cvx.target())) )  
          return true; //a null segment (=point)
        
        return false;
      }
    
    if (cv1_status == cvx_status)
      {
        if ( ((cv1_status == CURVE_LEFT) && (cv1_cvx==1)) ||
             ((cv1_status == CURVE_RIGHT) && (cv1_cvx==-1)) )
          return true;

        //addition by iddo to prevent infinite loop in null segments - 
        //needs testing
        if ( (cv1_status==CURVE_VERTICAL_DOWN)&&
             ((cv1.source()==cv1.target())||(cvx.source()==cvx.target())) )
          return true; //a null segment (=point) 

        return false;
      }
    
    // cv1 and cv0 are on diffrent part of the circle - it is easy
    if ( ((cv1_status - cv0_status + 4)%4) < 
         ((cvx_status - cv0_status + 4)%4) )
      return false;
    else
      // if there is an equality or inequality to the other side
      // everything is ok
      return true;
  }
  
public:

  CGAL_Comparison_result compare_x(const Point &p1, const Point &p2) const
  { return compare_value(p1.x(), p2.x()); }
  CGAL_Comparison_result compare_y(const Point &p1, const Point &p2) const
  { return compare_value(p1.y(), p2.y()); }
public:
  Point point_to_left(const Point& p) const {return p+Vector(-2*numer,0);}
  Point point_to_right(const Point& p) const {return p+Vector(2*numer,0);}
  bool curve_is_same(const X_curve &cv1, const X_curve &cv2) const
  {
	return is_same(curve_source(cv1),curve_source(cv2))&&
		is_same(curve_target(cv1),curve_target(cv2));
  }
private:
  bool is_left(const Point &p1, const Point &p2) const 
  { return (compare_x(p1, p2) == CGAL_SMALLER); }
  bool is_right(const Point &p1, const Point &p2) const 
  { return (compare_x(p1, p2) == CGAL_LARGER); }
  bool is_same_x(const Point &p1, const Point &p2) const 
  { return (compare_x(p1, p2) == CGAL_EQUAL); }
  bool is_lower(const Point &p1, const Point &p2) const 
  { return (compare_y(p1, p2) == CGAL_SMALLER); }
  bool is_higher(const Point &p1, const Point &p2) const 
  { return (compare_y(p1, p2) == CGAL_LARGER); }
  bool is_same_y(const Point &p1, const Point &p2) const 
  { return (compare_y(p1, p2) == CGAL_EQUAL); }
  
  bool is_same(const Point &p1, const Point &p2) const
  {
    return (compare_x(p1, p2) == CGAL_EQUAL) &&
      (compare_y(p1, p2) == CGAL_EQUAL);
  }
  
  const Point& leftmost(const Point &p1, const Point &p2) const
  { return (is_left(p1, p2) ? p1 : p2); }
  
  const Point& rightmost(const Point &p1, const Point &p2) const
  { return (is_right(p1, p2) ? p1 : p2); }
  
  const Point& lowest(const Point &p1, const Point &p2) const
  { return (is_lower(p1, p2) ? p1 : p2); }
  
  const Point& highest(const Point &p1, const Point &p2) const
  { return (is_higher(p1, p2) ? p1 : p2); }
  Point curve_calc_point(const X_curve &cv, const Point& q) const
  {
    // assert (!curve_is_in_s_range(cv, q));
    if ( !curve_is_in_x_range(cv, q) )
      return cv.source();
    
    if (curve_is_vertical(cv))
      return cv.source();
    
    //return Point(q.x(), cv.source().y() + 
    //             (cv.target().y() - cv.source().y()) / 
    //             (cv.target().x() - cv.source().x()) * 
    //             (q.x() - cv.source().x()) );
    
    Point a = cv.source();
    Point b = cv.target();
    return Point ((b.hx() * a.hw() - a.hx() * b.hw()) * q.hx() * a.hw(),
                  (b.hx() * a.hw() - a.hx() * b.hw()) * q.hw() * a.hy() + 
                  (b.hy() * a.hw() - a.hy() * b.hw()) * 
                  (q.hx() * a.hw() - a.hx() * q.hw()),  
                  (b.hx() * a.hw() - a.hx() * b.hw()) * q.hw() * a.hw());
  }
  
  
  typename R::FT curve_derivative(const X_curve &cv) const
  {
    assert(!curve_is_vertical(cv));
    return (cv.target().y() - cv.source().y()) / 
      (cv.target().x() - cv.source().x());
  }
  
  typename R::FT curve_b_const(const X_curve &cv)const
  {
    assert (!curve_is_vertical(cv));
    return ((cv.target().x() * cv.source().y() - 
             cv.target().y()*cv.source().x())     / 
            (cv.target().x() - cv.source().x()));
  }
  
  CGAL_Comparison_result compare_value(const typename R::FT &v1, 
                                       const typename R::FT &v2) const
  {
    epsilon_type d = CGAL_to_double(v1 - v2);
    if (CGAL_abs(d) < EPSILON)
      return CGAL_EQUAL;
    if (d > 0)
      return CGAL_LARGER;
    else
      return CGAL_SMALLER;
  }
  
  
};

#endif // CGAL_PM_SEGMENT_EPSILON_TRAITS_H




















