// Copyright (c) 2007,2009  INRIA Sophia-Antipolis (France).  All rights reserved.
//
// This file is part of CGAL (www.cgal.org)
//
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-5.0/STL_Extension/include/CGAL/Default.h $
// $Id: Default.h 52164b1 2019-10-19T15:34:59+02:00 Sébastien Loriot
// SPDX-License-Identifier: LGPL-3.0-or-later OR LicenseRef-Commercial
//
// Author(s)     : Sylvain Pion
 
#ifndef CGAL_DEFAULT_H
#define CGAL_DEFAULT_H

namespace CGAL {

// Default is a tag that can be used to shrink mangled names and
// error messages in place of the default value of template arguments.
// It could also be used by users to specify default values to arguments which
// are not at the end of the argument list.
// It can also be useful to easily break cyclic dependencies in templates.

struct Default
{
    template <typename Argument, typename Value>
    struct Get {
        typedef Argument type;
    };

    template <typename Value>
    struct Get <Default, Value> {
        typedef Value type;
    };

  template <typename Argument, typename Fct>
    struct Lazy_get {
        typedef Argument type;
    };

    template <typename Fct>
    struct Lazy_get <Default, Fct> {
        typedef typename Fct::type type;
    };
};

}

#endif // CGAL_DEFAULT_H
