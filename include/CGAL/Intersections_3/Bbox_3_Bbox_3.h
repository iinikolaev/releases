// Copyright (c) 2010 GeometryFactory (France).
// All rights reserved.
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
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-4.14.2/Intersections_3/include/CGAL/Intersections_3/Bbox_3_Bbox_3.h $
// $Id: Bbox_3_Bbox_3.h 057f4ea 2018-11-02T14:17:16+01:00 Sébastien Loriot
// SPDX-License-Identifier: LGPL-3.0+
//
//
// Author(s)     : Sebastien Loriot
//

#ifndef CGAL_INTERSECTIONS_3_BBOX_3_BBOX_3_H
#define CGAL_INTERSECTIONS_3_BBOX_3_BBOX_3_H


#include <CGAL/Bbox_3.h>

namespace CGAL {
bool
inline
do_intersect(const CGAL::Bbox_3& c,
             const CGAL::Bbox_3& bbox)
{
  return CGAL::do_overlap(c, bbox);
}

} //namespace CGAL


#endif // CGAL_INTERSECTIONS_3_BBOX_3_BBOX_3_H
