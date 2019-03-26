// Copyright (c) 2008  GeometryFactory, Sophia-Antipolis (France).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org).
// You can redistribute it and/or modify it under the terms of the GNU
// General Public License as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-4.14-beta1/Surface_mesher/include/CGAL/IO/Complex_2_in_triangulation_3_to_vtk.h $
// $Id: Complex_2_in_triangulation_3_to_vtk.h 799260f %aI Andreas Fabri
// SPDX-License-Identifier: GPL-3.0+
//
//
// Author(s)     : Laurent Rineau

#ifndef CGAL_COMPLEX_2_IN_TRIANGULATION_3_TO_VTK
#define CGAL_COMPLEX_2_IN_TRIANGULATION_3_TO_VTK

#include <CGAL/license/Surface_mesher.h>

#include <CGAL/disable_warnings.h>

#include <map>

#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkCellArray.h>
#include <vtkType.h>

namespace CGAL {

template <typename C2T3>
vtkPolyData* output_c2t3_to_vtk_polydata(const C2T3& c2t3, 
                                         vtkPolyData* polydata = 0)
{
  typedef typename C2T3::Triangulation Triangulation;
  typedef typename Triangulation::Vertex_handle Vertex_handle;

  const Triangulation& tr = c2t3.triangulation();

  vtkPoints* const vtk_points = vtkPoints::New();
  vtkCellArray* const vtk_cells = vtkCellArray::New();

  vtk_points->Allocate(c2t3.triangulation().number_of_vertices());
  vtk_cells->Allocate(c2t3.number_of_facets());

  std::map<Vertex_handle, vtkIdType> V;
  vtkIdType inum = 0;

  for(typename Triangulation::Finite_vertices_iterator 
        vit = tr.finite_vertices_begin(),
        end = tr.finite_vertices_end();
      vit != end;
      ++vit)
  {
    typedef typename Triangulation::Point Point;
    const Point& p = vit->point();
    vtk_points->InsertNextPoint(CGAL::to_double(p.x()),
                                CGAL::to_double(p.y()),
                                CGAL::to_double(p.z()));
    V[vit] = inum++;
  }
  for(typename C2T3::Facet_iterator 
        fit = c2t3.facets_begin(),
        end = c2t3.facets_end();
      fit != end; ++fit) 
  {
    vtkIdType cell[3];
    int j=0;
    for (int i = 0; i < 4; ++i)
      if (i != fit->second)
        cell[j++] =  V[(*fit).first->vertex(i)];
    CGAL_assertion(j==3);
    vtk_cells->InsertNextCell(3, cell);
  }
  if(!polydata) {
    polydata = vtkPolyData::New();
  }

  polydata->SetPoints(vtk_points);
  vtk_points->Delete();

  polydata->SetPolys(vtk_cells);
  vtk_cells->Delete();
  return polydata;
}

} // end namespace CGAL

#include <CGAL/enable_warnings.h>

#endif // CGAL_COMPLEX_2_IN_TRIANGULATION_3_TO_VTK
