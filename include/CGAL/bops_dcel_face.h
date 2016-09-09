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
// file          : include/CGAL/bops_dcel_face.h
// package       : bops (2.1.5)
// source        : include/CGAL/bops_dcel_face.h
// revision      : $Revision: 1.1.2 $
// revision_date : $Date: Wed Dec  9 13:28:52 MET 1998  $
// author(s)     : Wolfgang Freiseisen
//
// coordinator   : RISC Linz
//  (Wolfgang Freiseisen)
//
// 
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL__DCEL_FACE_H
#define CGAL__DCEL_FACE_H

#include <CGAL/bops_dcel_element.h>

CGAL_BEGIN_NAMESPACE

/*
  FACE in the DCEL:
  -----------------
  face_type:        header (HF), color
  face:             typedef const _Dcel_face_type*   _Dcel_face;
  container:        vector<_Dcel_face_type>
  face_iterator:    typedef vector<_Dcel_face_type>::const_iterator
  conversion:       face and face_iterator are type-identical
*/


template<class I>
class _Dcel_face_type : public _Dcel_element_type {
public:
#ifdef CGAL_CFG_INCOMPLETE_TYPE_BUG_4
  typedef _Dcel_edge_type<I>* edge;
#else
  typedef typename I::const_edges_iterator  edge;
#endif

  _Dcel_face_type(int ind, _Dcel_Color col = _NO_COLOR)
        : _Dcel_element_type(ind, col), _header(NULL) {}
  _Dcel_face_type( _Dcel_Color col = _NO_COLOR )
        : _Dcel_element_type(col), _header(NULL) {}

  edge  header() const { return _header; }

protected:
  edge&  header()  { return _header; }

private:
  edge _header;
  friend class _Dcel_base<I>;
};

CGAL_END_NAMESPACE

#endif /* CGAL__DCEL_FACE_H */