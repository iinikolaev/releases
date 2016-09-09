// Copyright (c) 2003-2004  INRIA Sophia-Antipolis (France).
// All rights reserved.
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Mesh_2/demo/Mesh_2/Show_segments_base.cpp $
// $Id: Show_segments_base.cpp 45453 2008-09-09 21:35:22Z lrineau $
//
//
// Author(s)     : Laurent Rineau

#include <CGAL/basic.h>


#include "Show_segments_base.h"

namespace CGAL {

  Show_segments_base::Show_segments_base(Color c,
                                         int linewidth,
                                         QObject* parent,
                                         const char* name)
    : Qt_widget_styled_layer(0, parent, name)
  {
    color=tr("Color");
    width=tr("Line width");

    setColor(QColor(c.red(), c.green(), c.blue()));
    setLineWidth(linewidth);
  }

  Show_segments_base::Show_segments_base(Style* style,
                                         QString line_color_name,
                                         QString line_width_name,
                                         QObject* parent,
                                         const char* name)
    : Qt_widget_styled_layer(style, parent, name),
      color(line_color_name),
      width(line_width_name)
  {}

  void Show_segments_base::setColor(QColor c)
  { style()->setColor(color, c); }

  void Show_segments_base::setLineWidth(int line_width)
  { style()->setInt(width, line_width); }

} // namespace CGAL

// moc_source_file: Show_segments_base.h
#include "Show_segments_base.moc"

