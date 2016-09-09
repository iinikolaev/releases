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
// file          : include/CGAL/IO/Planar_map_iostream.h
// package       : pm (3.07)
// source        : 
// revision      : 
// revision_date : 
// author(s)     : Iddo Hanniel
//                 Oren Nechushtan
//
//
// coordinator   : Tel-Aviv University (Dan Halperin)
//
// Chapter       : 
// email         : cgal@cs.uu.nl
//
// ======================================================================
#include <iostream>

CGAL_BEGIN_NAMESPACE

template <class Dcel, class Traits>
::std::ostream& operator<<(::std::ostream& o, 
const Planar_map_2<Dcel,Traits>& pm) 
{
  o << "Vertices ---------------" << std::endl;
  typename CGAL::Planar_map_2<Dcel,Traits>::Vertex_const_iterator vi;
  for (vi = pm.vertices_begin(); vi != pm.vertices_end(); ++vi)
    {
      o << "(" << vi->point() << ")" << std::endl;
      }
  
  o << "Halfedges ------------------" << std::endl;
  typename CGAL::Planar_map_2<Dcel,Traits>::Halfedge_const_iterator ei;
  for (ei = pm.halfedges_begin(); ei != pm.halfedges_end(); ++ei)
    {
      o << "{" << ei->curve() << "}" << std::endl;
    } 
  
  o << "Faces ------------------" << std::endl;
  typename CGAL::Planar_map_2<Dcel,Traits>::Face_const_iterator fi;
  
  typename CGAL::Planar_map_2<Dcel,Traits>::Holes_const_iterator iccbit;
  //typename CGAL::Planar_map_2<Dcel,Traits>::Holes_iterator iccbit;
  
  
  typename CGAL::Planar_map_2<Dcel,Traits>::Ccb_halfedge_const_circulator ccb_circ;
  //typename CGAL::Planar_map_2<Dcel,Traits>::Ccb_halfedge_circulator ccb_circ;
  int ck;
  int fc_counter;
  for (fc_counter=0,fi = pm.faces_begin(); fi != pm.faces_end(); 
       ++fi,fc_counter++)
    {
      o << "Face " << fc_counter << " :\n";
      o << "outer ccb: " ;
      
      if (fi->is_unbounded())
        {
          o << "UNBOUNDED"  << std::endl;
        }
      else {
        //        typename CGAL::Planar_map_2<Dcel,Traits>::Ccb_halfedge_circulator 
        typename CGAL::Planar_map_2<Dcel,Traits>::Ccb_halfedge_const_circulator 
          first = fi->outer_ccb(), iter = first;
        
        o << "[";
        do
          {
            o << "(" << iter->source()->point() << ")-";
            ++iter;
          } while (iter != first);
        o << "(" << first->source()->point() << ")]" << std::endl;    
        }
      
      
      
      for (ck=0, iccbit = (*fi).holes_begin(); iccbit != (*fi).holes_end();
           ++iccbit, ck++)
        {
          o << "inner ccb " << ck << ": " ;
          ccb_circ = (*iccbit);
          typename CGAL::Planar_map_2<Dcel,Traits>::Ccb_halfedge_const_circulator 
          //typename CGAL::Planar_map_2<Dcel,Traits>::Ccb_halfedge_circulator 
            iter = ccb_circ;
          
          o << "[";
          do
            {
              o << "(" << iter->source()->point() << ")-";
              ++iter;
              } while (iter != ccb_circ);
          o << "(" << ccb_circ->source()->point() << ")]" ;
          
        }
      o << std::endl;
    }
  return o;
}

CGAL_END_NAMESPACE












