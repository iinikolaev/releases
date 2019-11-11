// Copyright (c) 1999  
// Utrecht University (The Netherlands),
// ETH Zurich (Switzerland),
// INRIA Sophia-Antipolis (France),
// Max-Planck-Institute Saarbruecken (Germany),
// and Tel-Aviv University (Israel).  All rights reserved. 
//
// This file is part of CGAL (www.cgal.org)
//
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-5.0-beta2/Kernel_23/include/CGAL/Origin.h $
// $Id: Origin.h 52164b1 2019-10-19T15:34:59+02:00 Sébastien Loriot
// SPDX-License-Identifier: LGPL-3.0-or-later OR LicenseRef-Commercial
// 
//
// Author(s)     : Andreas Fabri
//                 Stefan Schirra

#ifndef CGAL_ORIGIN_H
#define CGAL_ORIGIN_H

#include <CGAL/config.h>

namespace CGAL {

class Origin
{};

class Null_vector
{};

#ifndef CGAL_HEADER_ONLY

CGAL_EXPORT extern const Origin ORIGIN;
CGAL_EXPORT extern const Null_vector NULL_VECTOR;

#endif

} //namespace CGAL

#ifdef CGAL_HEADER_ONLY
#include <CGAL/Origin_impl.h>
#endif // CGAL_HEADER_ONLY

#endif // CGAL_ORIGIN_H
