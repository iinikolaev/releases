// ======================================================================
//
// Copyright (c) 1997-2001 The CGAL Consortium

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
// file          : include/CGAL/Random.h
// package       : Random_numbers (2.3.5)
// chapter       : Random Numbers Generator
//
// source        : web/Random.aw
// revision      : $Revision: 1.4 $
// revision_date : $Date: 2002/01/10 10:10:49 $
//
// author(s)     : Sven Sch�nherr
// coordinator   : INRIA Sophia-Antipolis
//
// implementation: Random Numbers Generator
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_RANDOM_H
#define CGAL_RANDOM_H

// includes
// --------
#  include <CGAL/basic.h>

CGAL_BEGIN_NAMESPACE

// Class declaration
// =================
class Random;

// Class interface
// ===============
class Random {
  public:
    // creation
    Random( );
    Random( unsigned int  seed);
    
    // operations
    bool    get_bool  ( );
    int     get_int   ( int lower, int upper);
    double  get_double( double lower = 0.0, double upper = 1.0);
    
    int     operator () ( int upper);
  private:
    // data members
    const double  rand_max_plus_1;
};

// Global variables
// ================
extern  Random  default_random;

CGAL_END_NAMESPACE

// ============================================================================

// Class implementation (inline functions)
// =======================================
// includes
#  include <cstdlib>

CGAL_BEGIN_NAMESPACE

// operations
inline
bool
Random::
get_bool( )
{
    return( static_cast< bool>( CGAL_CLIB_STD::rand() & 1));
}

inline
int
Random::
get_int( int lower, int upper)
{
    return( lower + static_cast< int>(
      ( static_cast< double>( upper) - lower) * 
      CGAL_CLIB_STD::rand() / rand_max_plus_1));
}

inline
double
Random::
get_double( double lower, double upper)
{
    return( lower + ( ( upper-lower) * 
		      CGAL_CLIB_STD::rand() / rand_max_plus_1));
}

inline
int
Random::
operator () ( int upper)
{
    return( get_int( 0, upper));
}

CGAL_END_NAMESPACE

#endif // CGAL_RANDOM_H

// ===== EOF ==================================================================
