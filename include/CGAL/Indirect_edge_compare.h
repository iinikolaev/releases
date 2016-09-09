// ======================================================================
//
// Copyright (c) 2000 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/Indirect_edge_compare.h
// package       : Partition_2 (1.38)
// chapter       : Planar Polygon Partitioning
//
// revision      : $Revision: 1.15 $
// revision_date : $Date: 2002/04/24 11:24:33 $
//
// author(s)     : Susan Hert
//
// coordinator   : MPI (Susan Hert)
//
// implementation: Comparison of edges represented by circulators to endpoints. 
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_INDIRECT_EDGE_COMPARE_H
#define CGAL_INDIRECT_EDGE_COMPARE_H

namespace CGAL {

//
// given circulators to endpoints of two edges, sorts the edges that come
// next (in the direction of circulator) from right to left. This ordering 
// makes finding the edge directly left of a given edge (needed for the 
// y-monotone decomposition algorithm) easy. 
//
template <class ForwardCirculator, class Traits>
class Indirect_edge_compare 
{
   public:
     typedef typename Traits::Compare_y_2        Compare_y_2;
     typedef typename Traits::Compare_x_2        Compare_x_2;
     typedef typename Traits::Construct_line_2   Construct_line_2;
     typedef typename Traits::Compare_x_at_y_2   Compare_x_at_y_2;
     typedef typename Traits::Is_horizontal_2    Is_horizontal_2;
     typedef typename Traits::Line_2             Line_2;
     typedef typename Traits::Point_2            Point_2;

     Indirect_edge_compare() : 
          _compare_y_2(Traits().compare_y_2_object()),
          _compare_x_2(Traits().compare_x_2_object()),
          _construct_line_2(Traits().construct_line_2_object()),
          _compare_x_at_y_2(Traits().compare_x_at_y_2_object()),
          _is_horizontal_2(Traits().is_horizontal_2_object())
     { }
     
     // determines if the edge (edge_vtx_1, edge_vtx_1++) has a larger
     // x value than vertex.x at y-value vertex.y
     bool
     larger_x_at_vertex_y(ForwardCirculator edge_vtx_1, 
                          ForwardCirculator vertex) const
     {
        ForwardCirculator edge_vtx_2 = edge_vtx_1;
        edge_vtx_2++;
        // check for horizontal edge
        if (_compare_y_2((*edge_vtx_1), (*edge_vtx_2)) == EQUAL)  
        { 
            // compare the smaller x and vertex x
           if (_compare_x_2(*edge_vtx_1, *edge_vtx_2) == SMALLER)
              return _compare_x_2(*edge_vtx_1, *vertex) == LARGER;
           else
              return _compare_x_2(*edge_vtx_2, *vertex) == LARGER;
        }
        else 
        { 
           // construct supporting line for edge
           Line_2  line = _construct_line_2(*edge_vtx_1, *edge_vtx_2);
           return _compare_x_at_y_2(*vertex, line) == SMALLER;
        }
     }               

     bool 
     operator()(ForwardCirculator p, ForwardCirculator q) const
     {
        ForwardCirculator after_p = p;
        after_p++;
        ForwardCirculator after_q = q;
        after_q++;

        if (p == q && after_p == after_q) return false;

        if (p == after_q) 
        {
          return larger_x_at_vertex_y(p, q);
        }
        else if (after_p == q) 
        {
          return !larger_x_at_vertex_y(q, p);
        }
        else if (p == q) 
        {
          return larger_x_at_vertex_y(p, after_q);
        }
        else if (after_p == after_q) 
        {
          return larger_x_at_vertex_y(p, q);
        }
        else // neither endpoint is shared
        {
          // construct supporting line
          Line_2  l_p = _construct_line_2(*p, *after_p);
          if (_is_horizontal_2(l_p)) 
          {
              Line_2  l_q = _construct_line_2(*q, *after_q);

              if (_is_horizontal_2(l_q))  
              {                         
                 Point_2 p_max;
                 Point_2 q_max;
                 if (_compare_x_2(*p, *after_p) == SMALLER)
                    p_max = *after_p;
                 else
                    p_max = *p;
                 if (_compare_x_2(*q, *after_q) == SMALLER)
                    q_max = *after_q;
                 else
                    q_max = *q;
                 return (_compare_x_2(p_max, q_max) == LARGER);
              }
              else  // p and after_p must both be on same side of l_q
              {
                 return (_compare_x_at_y_2(*p, l_q) == LARGER);
              }
          }
          else  
          {
             bool q_larger_x = _compare_x_at_y_2(*q, l_p) == SMALLER;
             bool after_q_larger_x = 
                              _compare_x_at_y_2(*after_q, l_p) == SMALLER;

             if (q_larger_x == after_q_larger_x)
                return q_larger_x;
             else   // one smaller and one larger
             {
                // construct the other line
                Line_2 l_q = _construct_line_2(*q, *after_q); 
                if (_is_horizontal_2(l_q))     // p is not horizontal
                {
                   return _compare_x_at_y_2((*q), l_p) == LARGER;
                }
                else 
                {
                  return _compare_x_at_y_2((*p), l_q) != SMALLER;
                }
             }
          }   
        }
     }

   private:
     Compare_y_2      _compare_y_2;
     Compare_x_2      _compare_x_2;
     Construct_line_2 _construct_line_2;
     Compare_x_at_y_2 _compare_x_at_y_2;
     Is_horizontal_2  _is_horizontal_2;
};

}



#endif // CGAL_INDIRECT_EDGE_COMPARE_H

