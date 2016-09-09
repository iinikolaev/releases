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
// file          : include/CGAL/Polyhedron_copy_3.h
// package       : Polyhedron (2.5)
// chapter       : $CGAL_Chapter: 3D-Polyhedral Surfaces $
// source        : polyhedron_builder.fw
// revision      : $Revision: 1.2 $
// revision_date : $Date: 1999/03/09 15:32:15 $
// author(s)     : Lutz Kettner
//
// coordinator   : MPI Saarbruecken (Stefan Schirra)
//
// Copy of Polyhedral Surfaces.
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_POLYHEDRON_COPY_3_H
#define CGAL_POLYHEDRON_COPY_3_H 1
#ifndef CGAL_MODIFIER_BASE_H
#include <CGAL/Modifier_base.h>
#endif // CGAL_MODIFIER_BASE_H
#ifndef CGAL_INVERSE_INDEX_H
#include <CGAL/Inverse_index.h>
#endif // CGAL_INVERSE_INDEX_H
#ifndef CGAL_POLYHEDRON_INCREMENTAL_BUILDER_3_H
#include <CGAL/Polyhedron_incremental_builder_3.h>
#endif // CGAL_POLYHEDRON_INCREMENTAL_BUILDER_3_H

CGAL_BEGIN_NAMESPACE

template < class Poly, class HDS >
class Polyhedron_copy_3
    : public Modifier_base<HDS> {
protected:
    const Poly& source;
public:
    typedef Poly Polyhedron;
    typedef HDS  Halfedge_data_structure;
    Polyhedron_copy_3( const Polyhedron& poly) : source(poly) {}
        // creates the copy modifier and stores the `source' in its
        // internal state.
    void operator()( HDS& target);
        // copies the `source' known from creation time into the `target'.
        // Postcondition: the `target' is a valid polyhedral surface.
};

template < class Poly, class HDS>
void
Polyhedron_copy_3<Poly,HDS>:: operator()( HDS& target) {
    typedef typename Poly::Vertex_const_iterator Vertex_const_iterator;
    typedef typename Poly::Facet_const_iterator  Facet_const_iterator;
    typedef Inverse_index< Vertex_const_iterator>  Index;
    typedef typename HDS::Point                  Point;

    target.delete_all();
    Polyhedron_incremental_builder_3<HDS> B( target);
    B.begin_surface( source.size_of_vertices(),
                     source.size_of_facets(),
                     source.size_of_halfedges());
    for( Vertex_const_iterator vi = source.vertices_begin();
         vi != source.vertices_end();
         ++vi) {
        B.add_vertex( Point( vi->point()));
    }
    Index index( source.vertices_begin(), source.vertices_end());

    for( Facet_const_iterator fi = source.facets_begin();
         fi != source.facets_end();
         ++fi) {
        B.begin_facet();
        typedef typename Poly::Halfedge_around_facet_const_circulator
            Halfedge_around_facet_const_circulator;
        Halfedge_around_facet_const_circulator hc = fi->facet_begin();
        Halfedge_around_facet_const_circulator hc_end = hc;
        CGAL_assertion( hc != NULL);
        do {
            B.add_vertex_to_facet( index[ Vertex_const_iterator(
                hc->vertex().ptr())]);
            ++hc;
        } while( hc != hc_end);
        B.end_facet();
    }
    B.end_surface();
    target.normalize_border();
}

CGAL_END_NAMESPACE
#endif // CGAL_POLYHEDRON_COPY_3_H //
// EOF //