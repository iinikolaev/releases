// ======================================================================
//
// Copyright (c) 2000 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
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
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.2
// release_date  : 2000, September 30
//
// file          : include/CGAL/Cartesian/Sphere_rep_d.h
// package       : Cd (1.5)
// revision      : $Revision: 1.2 $
// revision_date : $Date: 2000/06/27 14:32:30 $
// author(s)     : Herve.Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_SPHERE_REP_D_H
#define CGAL_CARTESIAN_SPHERE_REP_D_H

CGAL_BEGIN_NAMESPACE

template < class R >
class Sphere_repC3 : public Rep
{
public:
  typedef typename R::FT                        FT;
#ifndef CGAL_CFG_NO_ADVANCED_KERNEL
  typedef typename R::Point_d                   Point_d;
#else
  typedef typename R::Point_D_base              Point_d;
#endif

  Point_d      center;
  FT           squared_radius;
  Orientation  orient;


  Sphere_repC3() {}

  Sphere_repC3(const Point_d & c, const FT & r, const Orientation &o)
    : center(c), squared_radius(r), orient(o) {}

  ~Sphere_repC3() {}
};

CGAL_END_NAMESPACE

#endif  // CGAL_CARTESIAN_SPHERE_REP_D_H