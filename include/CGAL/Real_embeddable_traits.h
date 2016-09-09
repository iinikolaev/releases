// Copyright (c) 2006-2007 Max-Planck-Institute Saarbruecken (Germany).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.4-branch/Algebraic_foundations/include/CGAL/Real_embeddable_traits.h $
// $Id: Real_embeddable_traits.h 45636 2008-09-18 15:35:55Z hemmer $
//
//
// Author(s)     : Michael Hemmer    <hemmer@mpi-inf.mpg.de>
//
// =============================================================================


#ifndef CGAL_REAL_EMBEDDABLE_TRAITS_H
#define CGAL_REAL_EMBEDDABLE_TRAITS_H

#include <CGAL/number_type_basic.h>

CGAL_BEGIN_NAMESPACE

namespace INTERN_RET {

template< class T, class AST_is_zero >
struct  Is_zero_selector{ typedef AST_is_zero Type; };

template< class T >
struct Is_zero_selector< T, Null_functor >
{
  struct Type : public std::unary_function< T, bool >{
    bool operator()( const T& x ) const {
      return x == T(0);
    }
  }; 
};

template < class Type_ , class Is_real_embeddable_  > 
class Real_embeddable_traits_base{
public:
  typedef Type_                 Type;
  typedef Is_real_embeddable_   Is_real_embeddable;
  typedef Null_tag              Boolean;
  typedef Null_tag              Sign; 
  typedef Null_tag              Comparison_result; 

  typedef Null_functor Abs;
  typedef Null_functor Sgn;
  typedef Null_functor Is_finite;
  typedef Null_functor Is_positive;
  typedef Null_functor Is_negative;
  typedef Null_functor Is_zero;
  typedef Null_functor Compare;
  typedef Null_functor To_double;
  typedef Null_functor To_interval;
};
  
template< class Type_ >
class Real_embeddable_traits_base<Type_, CGAL::Tag_true> {
public:
  typedef Type_                    Type;
  typedef Tag_true                 Is_real_embeddable; 
  typedef bool                     Boolean;
  typedef CGAL::Sign               Sign; 
  typedef CGAL::Comparison_result  Comparison_result; 
  
private:
  typedef typename Algebraic_structure_traits< Type >::Is_zero AST_Is_zero; 
public:
  //! The generic \c Is_zero functor implementation uses one comparison
  typedef typename INTERN_RET::Is_zero_selector< Type, AST_Is_zero >::Type 
  Is_zero;
  
  //! The generic \c Is_finite functor returns true
  class Is_finite : public std::unary_function< Type, Boolean > {
  public:
    Boolean operator()( const Type& ) const {
      return true;
    }
  };
    
  //! The generic \c Abs functor implementation
  //! uses one comparisons and the unary minus if necessary.
  class Abs
    : public std::unary_function< Type, Type > {
  public:
    //! the function call.
    Type  operator()( const Type& x ) const {
      return( x < Type(0) ) ? -x : x;
    }
  };
    
  //! The generic \c Sgn functor implementation uses two comparisons.
  class Sgn 
    : public std::unary_function< Type, ::CGAL::Sign > {
  public:
    //! the function call.
    ::CGAL::Sign operator()( const Type& x ) const {
      if ( x < Type(0))
        return NEGATIVE;
      if ( x > Type(0))
        return POSITIVE;
      return ZERO;
    }
  };
    
  //! The generic \c Is_positive functor implementation uses one comparison.
  class Is_positive 
    : public std::unary_function< Type, Boolean > {
  public:        
    //! the function call.
    Boolean operator()( const Type& x ) const {
      return x > Type(0);
    }
  };
    
  //! The generic \c Is_negative functor implementation uses one comparison.
  class Is_negative 
    : public std::unary_function< Type, Boolean > {
  public:        
    //! the function call.
    Boolean operator()( const Type& x ) const {
      return x < Type(0);
    }
  };
        
  //! The generic \c Compare functor implementation uses two comparisons.
  class Compare 
    : public std::binary_function< Type, Type, 
                                Comparison_result > {
  public:
    //! the function call.
    Comparison_result operator()( const Type& x, 
        const Type& y) const {
      if( x < y )
        return SMALLER;
      if( x > y )
        return LARGER;
      return EQUAL;
    }
        
    CGAL_IMPLICIT_INTEROPERABLE_BINARY_OPERATOR_WITH_RT( Type,
        Comparison_result )
      };
  
  class To_double : public std::unary_function< Type, double > {     
  public:
    double operator()( const Type& x ) const {
      return static_cast<double>(x);
    }
  };
  
  class To_interval 
    : public std::unary_function< Type, std::pair<double,double> > {     
  public:
    std::pair<double,double> operator()( const Type& x ) const {
      double dx(static_cast<double>(x));
      return std::make_pair(dx,dx);
    }
  };
};
    
} // INTERN_RET


template< class Type_ > 
class Real_embeddable_traits 
  : public INTERN_RET::Real_embeddable_traits_base<Type_,CGAL::Tag_false> {};

CGAL_END_NAMESPACE

#endif  // CGAL_REAL_EMBEDDABLE_TRAITS_H
