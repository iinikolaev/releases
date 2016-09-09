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
// file          : include/CGAL/basic_constructionsC2.h
// package       : C2 (1.7)
// source        : web/basic_constructionsC2.fw
// revision      : $Revision: 1.10 $
// revision_date : $Date: 1999/01/04 06:54:15 $
// author(s)     : Herve Bronnimann
//
// coordinator   : INRIA Sophia-Antipolis
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_BASIC_CONSTRUCTIONSC2_H
#define CGAL_BASIC_CONSTRUCTIONSC2_H 1

#ifndef CGAL_POINTC2_H
#  include <CGAL/PointC2.h>
#endif

template < class FT >
CGAL_PointC2<FT>
CGAL_midpoint( CGAL_PointC2<FT> const& p,
               CGAL_PointC2<FT> const& q )
{
  FT x,y;
  CGAL_midpointC2(p.x(),p.y(),q.x(),q.y(),x,y);
  return CGAL_PointC2<FT>(x,y);
}
template < class FT >
CGAL_PointC2<FT>
CGAL_circumcenter( CGAL_PointC2<FT> const& p,
                   CGAL_PointC2<FT> const& q,
                   CGAL_PointC2<FT> const& r)
{
  FT x,y;
  CGAL_circumcenterC2(p.x(),p.y(),q.x(),q.y(),r.x(),r.y(),x,y);
  return CGAL_PointC2<FT>(x,y);
}

template < class FT >
FT
CGAL_squared_distance( CGAL_PointC2<FT> const& p,
                        CGAL_PointC2<FT> const& q)
{
  return CGAL_squared_distanceC2(p.x(),p.y(),q.x(),q.y());
}

template < class FT >
FT
CGAL_scaled_distance_to_line( CGAL_LineC2<FT> const& l,
                              CGAL_PointC2<FT> const& p)
{
  return CGAL_squared_distance_to_lineC2(l.a(),l.b(),l.c(),p.x(),p.y());
}

template < class FT >
FT
CGAL_scaled_distance_to_line( CGAL_PointC2<FT> const& p,
                              CGAL_PointC2<FT> const& q,
                              CGAL_PointC2<FT> const& r)
{
  return CGAL_squared_distance_to_lineC2(p.x(),p.y(),q.x(),q.y(),r.x(),r.y());
}


#endif // CGAL_BASIC_CONSTRUCTIONS_2_H
