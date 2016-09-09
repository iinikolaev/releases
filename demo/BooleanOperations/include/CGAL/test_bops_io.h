//  -*- Mode: c++ -*-
// ============================================================================
//
// Copyright (c) 1999 The GALIA Consortium
//
// This software and related documentation is part of the
// Computational Geometry Algorithms Library (CGAL).
//
// Every use of CGAL requires a license. Licenses come in three kinds:
//
// - For academic research and teaching purposes, permission to use and
//   copy the software and its documentation is hereby granted free of  
//   charge, provided that
//   (1) it is not a component of a commercial product, and
//   (2) this notice appears in all copies of the software and
//       related documentation.
// - Development licenses grant access to the source code of the library 
//   to develop programs. These programs may be sold to other parties as 
//   executable code. To obtain a development license, please contact
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.0
// release_date  : 1999, June 03
//
// file          : demo/BooleanOperations/include/CGAL/test_bops_io.h
// source        : demo/BooleanOperations/include/CGAL/test_bops_io.h
// revision      : $Revision: 1.1.2 $
// revision_date : $Date: Wed Dec  9 13:29:00 MET 1998  $
// author(s)     :                        Wolfgang Freiseisen
//
// coordinator   : RISC Linz
//  (Wolfgang Freiseisen)
//
// 
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef EXAMPLE_IO_H
#define EXAMPLE_IO_H

ostream& operator<<(ostream& o, Orientation orient) {
  if(orient == CLOCKWISE )
      o << "CLW";
  else if(orient == COUNTERCLOCKWISE )
      o << "CCW";
  else /* COLLINEAR */
      o << "COL";
  return o;
}

ostream& operator<<(ostream& o, Polygon_2 p) {
  Polygon_2::Vertex_const_iterator it;
  if( p.is_convex() )      o << "convex,";
  /* else if( p.is_simple() ) o << "simple,";
  else                     o << "NOT simple,"; */
  else o << "simple,";
  o << " n=" << p.size() << ", " << p.orientation();
  for( it= p.vertices_begin(); it != p.vertices_end(); it++) 
    o  << ", " << *it;
  return o;
}

void test_input(vector<Point_2>& vA, vector<Point_2>& vB) {
  vA[0]= Point_2(2,4);
  vA[1]= Point_2(0,3);
  vA[2]= Point_2(1,1);
  vA[3]= Point_2(2,3);
  vA[4]= Point_2(3,1);
  vA[5]= Point_2(4,3);
  vB[0]= Point_2(0,2);
  vB[1]= Point_2(0,0);
  vB[2]= Point_2(5,0);
  vB[3]= Point_2(5,2);
}

void test_result_output( const list<Object>& result ) {
  Point_2 pt;
  Segment_2 seg;
  Polygon_2 pgon;
  Iso_rectangle_2 irect;

  list<Object>::const_iterator it;
  cout << endl << "RESULT: (size=" << result.size() << ")" << endl;

  for( it= result.begin(); it != result.end(); it++) {
    if( assign( pgon, *it) ) { /* polygon */
      //cout << "POLYGON" << endl;
      cout << "pgon " << pgon << endl;
    }
    else if( assign( seg, *it) ) { /* segment */
      cout << "seg  " << seg << endl;
    }
    else if( assign( pt, *it) )  { /* point */
      cout << "pt   " << pt << endl;
    }
    else if( assign( irect, *it) )  { /* point */
      cout << "irect   " << irect << endl;
    }
    else { /* nothing */
      cout << "undefined object " << endl;
    }
  }
  cout << endl << endl << endl;
  
  return;
}

#ifdef  TEST_FLOAT_BOPS_H
bool read_point(Float_Point_2 &pt)
{
    Float x, y, w;
    cin >> x >> y >> w;
    if (!cin.good())
	return false;
    pt = Point_2(TestNum(x), TestNum(y));
    return true;
}
#endif

bool read_point(Point_2 &pt)
{
    long x, y, w;
    cin >> x >> y >> w;
    if (!cin.good())
	return false;
    pt = Point_2(TestNum(x), TestNum(y), TestNum(w));
    return true;
}

bool read_pgn(Polygon_2 &pgn)
{
    int n, i;
    cin >> n;
    if (!cin.good())
	return false;
    if (n < 3) {
	cin.clear(ios::failbit);
	return false;
    }
    vector<Point_2> points(n);
    for (i=0; i<n; i++) {
	if (!read_point(points[i]))
	    return false;
    }
    pgn = Polygon_2(points.begin(), points.end());
    return true;
}

#endif // EXAMPLE_IO_H