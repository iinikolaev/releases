// Copyright (c) 1997  ETH Zurich (Switzerland).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org).
//
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-5.0-beta2/Polyhedron_IO/include/CGAL/IO/print_inventor.h $
// $Id: print_inventor.h 254d60f 2019-10-19T15:23:19+02:00 Sébastien Loriot
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
// 
//
// Author(s)     : Lutz Kettner  <kettner@mpi-sb.mpg.de>

#ifndef CGAL_IO_PRINT_INVENTOR_H
#define CGAL_IO_PRINT_INVENTOR_H 1

#include <CGAL/license/Polyhedron.h>


#include <CGAL/IO/Polyhedron_inventor_ostream.h>


namespace CGAL {

template <class Polyhedron>
void print_polyhedron_inventor( std::ostream& out, const Polyhedron& P) {
    Inventor_ostream os( out);
    os << P;
}

// Deprecated global functions, replaced with functions above

template < class Traits,
           class Items,
           template < class T, class I, class A>
           class HDS, class Alloc>
void
print_inventor( std::ostream& out,
                const Polyhedron_3<Traits,Items,HDS,Alloc>& P) {
    Inventor_ostream os( out);
    os << P;
}

} //namespace CGAL
#endif // CGAL_IO_PRINT_INVENTOR_H //
// EOF //
