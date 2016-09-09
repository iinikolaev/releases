// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
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
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.2
// release_date  : 2000, September 30
//
// file          : include/CGAL/Triangulation_cell_base_3.h
// package       : Triangulation3 (1.42)
// revision      : $Revision: 1.16 $
// author(s)     : Monique Teillaud
//
// coordinator   : INRIA Sophia Antipolis 
//                 (Mariette Yvinec)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
//
// cell of a triangulation of any dimension <=3
//
// ============================================================================

#ifndef CGAL_TRIANGULATION_CELL_BASE_3_H
#define CGAL_TRIANGULATION_CELL_BASE_3_H

#include <CGAL/triangulation_assertions.h>

#include <CGAL/Triangulation_short_names_3.h>

CGAL_BEGIN_NAMESPACE

template < class Gt > class Triangulation_cell_base_3;
template < class Gt > 
std::istream& operator >> (std::istream&, Triangulation_cell_base_3<Gt>&);

template < class Gt >
class Triangulation_cell_base_3
{
  friend std::istream& operator >> CGAL_NULL_TMPL_ARGS
  (std::istream&, Triangulation_cell_base_3<Gt>&);

public:

  // CONSTRUCTORS

  inline
  Triangulation_cell_base_3()
  {
    set_vertices();
    set_neighbors();
  }

  inline
  Triangulation_cell_base_3(void* v0, void* v1, void* v2, void* v3)
  {
    set_vertices(v0, v1, v2, v3);
    set_neighbors();
  }

  inline
  Triangulation_cell_base_3(void* v0, void* v1, void* v2, void* v3,
			    void* n0, void* n1, void* n2, void* n3)
  {
    set_vertices(v0, v1, v2, v3);
    set_neighbors(n0, n1, n2, n3);
  }

  // ACCESS FUNCTIONS

  inline 
  const void* vertex(int i) const
  {
    CGAL_triangulation_precondition( i == 0 || i == 1 || i == 2 || i==3 );
    return V[i];
  } 

  inline 
  bool has_vertex(const void* v) const
  {
    return (V[0] == v) || (V[1] == v) || (V[2]== v) || (V[3]== v);
  }
    
  inline 
  bool has_vertex(const void* v, int & i) const
    {
      if (v == V[0]) { i = 0; return true; }
      if (v == V[1]) { i = 1; return true; }
      if (v == V[2]) { i = 2; return true; }
      if (v == V[3]) { i = 3; return true; }
      return false;
    }
    
  inline 
  int vertex_index(const void* v) const
  {
    if (v == V[0]) { return 0; }
    if (v == V[1]) { return 1; }
    if (v == V[2]) { return 2; }
    if (v == V[3]) { return 3; }
    CGAL_triangulation_assertion(false); // we should not get here
    return -1;
  }

  inline 
  void* neighbor(int i) const
  {
    CGAL_triangulation_precondition( i == 0 || i == 1 || i == 2 || i == 3);
    return N[i];
  }
    
  inline 
  bool has_neighbor(const void* n) const
  {
    return (N[0] == n) || (N[1] == n) || (N[2] == n) || (N[3] == n);
  }
    
  inline 
  bool has_neighbor(const void* n, int & i) const
  {
    if(n == N[0]){ i = 0; return true; }
    if(n == N[1]){ i = 1; return true; }
    if(n == N[2]){ i = 2; return true; }
    if(n == N[3]){ i = 3; return true; }
    return false;
  }
    
  inline 
  int cell_index(const void* n) const
  {
    if (n == N[0]) return 0;
    if (n == N[1]) return 1;
    if (n == N[2]) return 2;
    CGAL_triangulation_assertion( n == N[3] );
    return 3;
  }
 
  // SETTING

  inline 
  void set_vertex(int i, void* v)
  {
    CGAL_triangulation_precondition( i == 0 || i == 1 || i == 2 || i == 3);
    V[i] = v;
  }
    
  inline 
  void set_neighbor(int i, void* n)
  {
    CGAL_triangulation_precondition( i == 0 || i == 1 || i == 2 || i == 3);
    N[i] = n;
  }

  inline 
  void set_vertices()
  {
    V[0] = V[1] = V[2] = V[3] = NULL;
  }
    
  inline 
  void set_vertices(void* v0, void* v1, void* v2, void* v3)
  {
    V[0] = v0;
    V[1] = v1;
    V[2] = v2;
    V[3] = v3;
  }
    
  inline 
  void set_neighbors()
  {
    N[0] = NULL;
    N[1] = NULL;
    N[2] = NULL;
    N[3] = NULL;
  }
    
  inline
  void set_neighbors(void* n0, void* n1, void* n2, void* n3)
  {
    N[0] = n0;
    N[1] = n1;
    N[2] = n2;
    N[3] = n3;
  }

  // CHECKING

  // the following trivial is_valid allows
  // the user of derived cell base classes 
  // to add their own purpose checking
  bool is_valid(bool , int ) const
    {return true;}


private:
  void* V[4];
  void* N[4];
};

template < class GT >
std::istream& operator >>
(std::istream& is, Triangulation_cell_base_3<GT> & )
  // non combinatorial information. Default = nothing
{
  return is;
}

template < class GT >
std::ostream& operator<<
(std::ostream& os, const Triangulation_cell_base_3<GT> & )
  // non combinatorial information. Default = nothing
{
  // ADD THE FOLLOWING WHEN ADDING INFORMATION : 
//   if(is_ascii(os)) {
//     os << endl;
//   }
  return os;
}

CGAL_END_NAMESPACE

#endif // CGAL_TRIANGULATION_CELL_BASE_3_H