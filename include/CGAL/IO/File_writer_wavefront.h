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
// file          : include/CGAL/IO/File_writer_wavefront.h
// package       : Polyhedron_IO (1.11)
// chapter       : $CGAL_Chapter: Support Library ... $
// source        : polyhedron_io.fw
// revision      : $Revision: 1.8 $
// revision_date : $Date: 1998/10/08 22:46:22 $
// author(s)     : Lutz Kettner
//
// coordinator   : Herve Bronnimann
//
// Writer for polyhedral surfaces in Wavefront file format (.obj)
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_IO_FILE_WRITER_WAVEFRONT_H
#define CGAL_IO_FILE_WRITER_WAVEFRONT_H 1
#ifndef CGAL_IO_BINARY_FILE_IO_H
#include <CGAL/IO/binary_file_io.h>
#endif // CGAL_IO_BINARY_FILE_IO_H

#ifndef CGAL_PROTECT_IOSTREAM_H
#include <iostream.h>
#define CGAL_PROTECT_IOSTREAM_H
#endif // CGAL_PROTECT_IOSTREAM_H
#ifndef CGAL_PROTECT_STDDEF_H
#include <stddef.h>
#define CGAL_PROTECT_STDDEF_H
#endif // CGAL_PROTECT_STDDEF_H

class CGAL_File_writer_wavefront {
    ostream*  m_out;
    size_t    m_facets;
public:
    ostream& out() const { return *m_out; }
    void write_header( ostream& out,
                       size_t vertices,
                       size_t halfedges,
                       size_t facets);
    void write_footer() const {
        out() << "\n# End of Wavefront obj format #" << endl;
    }
    void write_vertex( const double& x, const double& y, const double& z) {
        out() << "v " << x << ' ' << y << ' ' << z << '\n';
    }
    void write_facet_header() {
        out() << "\n# " << m_facets << " facets\n";
        out() << "# ------------------------------------------\n\n";
    }
    void write_facet_begin( size_t) {  // no unused
        out() << "f ";
    }
    void write_facet_vertex_index( size_t index) {
        out() << ' ' << index + 1;
    }
    void write_facet_end() {
        out() << '\n';
    }
};
#endif // CGAL_IO_FILE_WRITER_WAVEFRONT_H //
// EOF //
