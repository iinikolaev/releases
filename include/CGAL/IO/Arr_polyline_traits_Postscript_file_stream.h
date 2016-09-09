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
//
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/IO/Arr_polyline_traits_Postscript_file_stream.h
// package       : Arrangement (2.52)
// author(s)     : Eti Ezra
// coordinator   : Tel-Aviv University (Dan Halperin)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifdef CGAL_ARR_POLYLINE_TRAITS_H
#ifndef CGAL_ARR_POLYLINE_TRAITS_POSTSCRIPT_FILE_STREAM_H   
#define CGAL_ARR_POLYLINE_TRAITS_POSTSCRIPT_FILE_STREAM_H  

#include <CGAL/Segment_2.h> 

#ifndef CGAL_POSTSCRIPT_FILE_STREAM_H
#include <CGAL/IO/Postscript_file_stream.h>
#endif

CGAL_BEGIN_NAMESPACE

template <class Curve>
Postscript_file_stream& 
operator<<(Postscript_file_stream& ps, const Curve& cv)        
{
  typedef typename Curve::value_type           Point;
  typedef typename Curve::iterator             Curve_iter;
  typedef typename Point::R                    R;
  typedef CGAL::Segment_2<R>                   Segment;
  typedef typename Curve::const_iterator       Points_iterator;
  
  ps << *(cv.begin());
  
  Points_iterator points_iter;
  for (points_iter = cv.begin(); points_iter != cv.end(); ) {
    //for (unsigned int i = 0; i < cv.size() - 1; i++){
    Points_iterator source_point = points_iter;
    
    Points_iterator target_point =  (++points_iter);
    
    if (target_point == cv.end())
      break;
    
    ps << Segment(*source_point, *target_point);
  }

  ps << *(--points_iter);

  return ps;
 
  /*typedef typename Curve::value_type           Point;
    typedef typename Point::R                    R;
    typedef CGAL::Segment_2<R>          Segment;
    
    ps << cv[0];
    
    for (unsigned int i = 0; i < cv.size() - 1; i++){
    ps << Segment(cv[i], cv[i+1]);
    }
    
    ps << cv[cv.size() - 1];
    
    return ps;*/
}

CGAL_END_NAMESPACE

#endif
#endif 









