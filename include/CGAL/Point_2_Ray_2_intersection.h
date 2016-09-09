
// ======================================================================
//
// Copyright (c) 1998 The CGAL Consortium
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
// file          : include/CGAL/Point_2_Ray_2_intersection.h
// package       : Intersections_2 (1.7)
// source        : intersection_2_1.fw
// author(s)     : Geert-Jan Giezeman
//
// coordinator   : Saarbruecken
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_POINT_2_RAY_2_INTERSECTION_H
#define CGAL_POINT_2_RAY_2_INTERSECTION_H

#ifndef CGAL_RAY_2_H
#include <CGAL/Ray_2.h>
#endif // CGAL_RAY_2_H
#ifndef CGAL_POINT_2_H
#include <CGAL/Point_2.h>
#endif // CGAL_POINT_2_H


template <class R>
inline bool
CGAL_do_intersect(const CGAL_Point_2<R> &pt, const CGAL_Ray_2<R> &ray)
{
    return ray.has_on(pt);
}

#ifndef CGAL_OBJECT_H
#include <CGAL/Object.h>
#endif // CGAL_OBJECT_H

template <class R>
CGAL_Object
CGAL_intersection(const CGAL_Point_2<R> &pt, const CGAL_Ray_2<R> &ray)
{
    if (CGAL_do_intersect(pt,ray)) {
        return CGAL_Object(new CGAL_Wrapper< CGAL_Point_2<R> >(pt));
    }
    return CGAL_Object();
}


template <class R>
inline bool
CGAL_do_intersect(const CGAL_Ray_2<R> &ray, const CGAL_Point_2<R> &pt)
{
    return ray.has_on(pt);
}


template <class R>
inline CGAL_Object
CGAL_intersection(const CGAL_Ray_2<R> &ray, const CGAL_Point_2<R> &pt)
{
    if (CGAL_do_intersect(pt,ray)) {
        return CGAL_Object(new CGAL_Wrapper< CGAL_Point_2<R> >(pt));
    }
    return CGAL_Object();
}

#endif
