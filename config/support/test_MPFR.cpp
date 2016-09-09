// Copyright (c) 2005  Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbruecken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).  All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.4-branch/Installation/config/support/test_MPFR.cpp $
// $Id: test_MPFR.cpp 32424 2006-07-12 09:26:22Z spion $
// 
//
// Author(s)     : various

// Tests if MPFR is available.

#include <iostream>
#include "gmp.h"
#include "mpfr.h"

int main()
{
    mpfr_t b, p;
    mpfr_init (p);
    mpfr_init_set_str (b, "31", 10, GMP_RNDN);
    mpfr_mul_ui (p, b, 75, GMP_RNDU);          /* generate product */

    char *str = new char[50]; // 50 should be enough
    mp_exp_t exp;
    str = mpfr_get_str(str, &exp, 10, 0, p, GMP_RNDU);
    std::cout << str << " E " << exp << std::endl;
    delete[] str;

#ifdef MPFR_VERSION
    std::cout << "version=" << MPFR_VERSION_MAJOR << "."
                            << MPFR_VERSION_MINOR << "."
                            << MPFR_VERSION_PATCHLEVEL << std::endl;
#else
    // MPFR versions < 2.2.0 did not have version strings
    std::cout << "version=unknown" << std::endl;
#endif

    return 0;
}
