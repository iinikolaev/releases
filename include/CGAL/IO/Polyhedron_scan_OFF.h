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
// file          : include/CGAL/IO/Polyhedron_scan_OFF.h
// package       : Polyhedron_IO (1.11)
// chapter       : $CGAL_Chapter: Support Library ... $
// source        : polyhedron_io.fw
// revision      : $Revision: 1.8 $
// revision_date : $Date: 1998/10/08 22:46:22 $
// author(s)     : Lutz Kettner
//
// coordinator   : Herve Bronnimann
//
// Scanner for OFF as polyhedral surface builder
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_IO_POLYHEDRON_SCAN_OFF_H
#define CGAL_IO_POLYHEDRON_SCAN_OFF_H 1
#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif

#ifndef CGAL_PROTECT_STDDEF_H
#include <stddef.h>
#define CGAL_PROTECT_STDDEF_H
#endif // CGAL_PROTECT_STDDEF_H

#ifndef CGAL_IO_FILE_HEADER_OFF_H
#include <CGAL/IO/File_header_OFF.h>
#endif // CGAL_IO_FILE_HEADER_OFF_H

#ifndef CGAL_IO_FILE_SCANNER_OFF_H
#include <CGAL/IO/File_scanner_OFF.h>
#endif // CGAL_IO_FILE_SCANNER_OFF_H

#ifndef CGAL_MODIFIER_BASE_H
#include <CGAL/Modifier_base.h>
#endif

#ifndef CGAL_POLYHEDRON_INCREMENTAL_BUILDER_3_H
#include <CGAL/Polyhedron_incremental_builder_3.h>
#endif // CGAL_POLYHEDRON_INCREMENTAL_BUILDER_3_H

#ifndef CGAL_POLYHEDRON_3_H
#include <CGAL/Polyhedron_3.h>
#endif

#ifndef CGAL_PROTECT_IOSTREAM_H
#include <iostream.h>
#define CGAL_PROTECT_IOSTREAM_H
#endif // CGAL_PROTECT_IOSTREAM_H

template < class HDS>
class CGAL_Polyhedron_scan_OFF :  public CGAL_Modifier_base<HDS> {
protected:
    istream&             m_in;
    CGAL_File_header_OFF  m_file_header;
public:

    typedef HDS Halfedge_data_structure;

// DEFINITION
//
// CGAL_Polyhedron_scan_OFF<Traits> is a polyhedral surface builder.
// It scans a polyhedron given in OFF from a stream and appends it
// incrementally using the incremental builder.

    CGAL_Polyhedron_scan_OFF( istream& in, bool verbose = false)
        : m_in(in), m_file_header( verbose) {}

    // Activation
    void operator()( HDS& hds);

    const CGAL_File_header_OFF&  header() const { return m_file_header; }
};

template < class HDS >
void
CGAL_Polyhedron_scan_OFF<HDS>:: operator()( HDS& target) {
    CGAL_File_scanner_OFF scanner( m_in, m_file_header.verbose());
    if ( ! m_in) {
        if ( scanner.verbose()) {
            cerr << " " << endl;
            cerr << "CGAL_Polyhedron_scan_OFF<HDS>::" << endl;
            cerr << "operator(): input error: file format is not in OFF."
                 << endl;
        }
        return;
    }
    m_file_header = scanner;  // Remember file header after return.

    CGAL_Polyhedron_incremental_builder_3<HDS> B( target,
                                                 scanner.verbose());
    B.begin_surface( scanner.size_of_vertices(),
                     scanner.size_of_facets(),
                     scanner.size_of_halfedges());

    typedef typename HDS::Point Point;
    typedef typename Point::RT  RT;

    // read in all vertices
    int  i;
    for ( i = 0; i < scanner.size_of_vertices(); i++) {
        Point p;
        CGAL_file_scan_vertex( scanner, p);
        B.add_vertex( p);
        scanner.skip_to_next_vertex( i);
    }
    if ( ! m_in  || B.error()) {
        B.rollback();
        m_in.clear( ios::badbit);
        return;
    }

    // read in all facets
    for ( i = 0; i < scanner.size_of_facets(); i++) {
        B.begin_facet();
        CGAL_Integer32 no;
        scanner.scan_facet( no, i);
        if( ! m_in || B.error() || no < 3) {
            if ( scanner.verbose()) {
                cerr << " " << endl;
                cerr << "CGAL_Polyhedron_scan_OFF<Traits>::" << endl;
                cerr << "operator()(): input error: facet " << i
                     << " has less than 3 vertices." << endl;
            }
            B.rollback();
            m_in.clear( ios::badbit);
            return;
        }
        for ( int j = 0; j < no; j++) {
            CGAL_Integer32 index;
            scanner.scan_facet_vertex_index( index, i);
            B.add_vertex_to_facet( index);
        }
        B.end_facet();
        scanner.skip_to_next_facet( i);
    }
    if ( ! m_in  || B.error()) {
        B.rollback();
        m_in.clear( ios::badbit);
        return;
    }
    if ( B.check_unconnected_vertices()) {
        if ( ! B.remove_unconnected_vertices()) {
            if ( scanner.verbose()) {
                cerr << " " << endl;
                cerr << "CGAL_Polyhedron_scan_OFF<Traits>::" << endl;
                cerr << "operator()(): input error: cannot succesfully "
                        " remove isolated vertices." << endl;
            }
            B.rollback();
            m_in.clear( ios::badbit);
            return;
        }
    }
    B.end_surface();
}
#endif // CGAL_IO_POLYHEDRON_SCAN_OFF_H //
// EOF //
