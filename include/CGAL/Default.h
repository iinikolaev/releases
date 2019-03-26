// Copyright (c) 2007,2009  INRIA Sophia-Antipolis (France).  All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; either version 3 of the License,
// or (at your option) any later version.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-4.14-beta1/STL_Extension/include/CGAL/Default.h $
// $Id: Default.h 0698f79 %aI Sébastien Loriot
// SPDX-License-Identifier: LGPL-3.0+
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
