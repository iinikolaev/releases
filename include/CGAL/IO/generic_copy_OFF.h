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
// file          : include/CGAL/IO/generic_copy_OFF.h
// package       : Polyhedron_IO (1.11)
// chapter       : $CGAL_Chapter: Support Library ... $
// source        : polyhedron_io.fw
// revision      : $Revision: 1.8 $
// revision_date : $Date: 1998/10/08 22:46:22 $
// author(s)     : Lutz Kettner
//
// coordinator   : Herve Bronnimann
//
// Generic copy of an object file format (OFF) file
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_IO_GENERIC_COPY_OFF_H
#define CGAL_IO_GENERIC_COPY_OFF_H 1
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

#ifndef CGAL_PROTECT_IOSTREAM_H
#include <iostream.h>
#define CGAL_PROTECT_IOSTREAM_H
#endif // CGAL_PROTECT_IOSTREAM_H

template <class Writer>
void
CGAL_generic_copy_OFF( CGAL_File_scanner_OFF& scanner,
                      ostream& out,
                      Writer& writer) {
    istream& in = scanner.in();
    // scans a polyhedral surface in OFF from `in' and writes it
    // to `out' in the format provided by `writer'.
    if ( ! in) {
        if ( scanner.verbose()) {
            cerr << " " << endl;
            cerr << "CGAL_generic_copy_OFF(): "
                    "input error: file format is not in OFF." << endl;
        }
        return;
    }

    // Print header. Number of halfedges is only trusted if it is
    // a polyhedral surface.
    writer.write_header( out,
                         scanner.size_of_vertices(),
                         scanner.polyhedral_surface() ?
                             scanner.size_of_halfedges() : 0,
                         scanner.size_of_facets());

    // read in all vertices
    double  x,  y,  z;  // Point coordinates.
    int  i;
    for ( i = 0; i < scanner.size_of_vertices(); i++) {
        scanner.scan_vertex( x, y, z);
        writer.write_vertex( x, y, z);
        scanner.skip_to_next_vertex( i);
    }

    // read in all facets
    writer.write_facet_header();
    for ( i = 0; i < scanner.size_of_facets(); i++) {
        if ( ! in)
            return;
        CGAL_Integer32 no;
        scanner.scan_facet( no, i);
        writer.write_facet_begin( no);
        for ( int j = 0; j < no; j++) {
            CGAL_Integer32 index;
            scanner.scan_facet_vertex_index( index, i);
            writer.write_facet_vertex_index( index);
        }
        writer.write_facet_end();
        scanner.skip_to_next_facet( i);
    }
    writer.write_footer();
}


template <class Writer>
void
CGAL_generic_copy_OFF( istream& in, ostream& out, Writer& writer,
                      bool verbose = false) {
    // scans a polyhedral surface in OFF from `in' and writes it
    // to `out' in the format provided by `writer'.
    CGAL_File_scanner_OFF scanner( in, verbose);
    CGAL_generic_copy_OFF( scanner, out, writer);
}
#endif // CGAL_IO_GENERIC_COPY_OFF_H //
// EOF //
