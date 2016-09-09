// Copyright (c) 2005-2007  Tel-Aviv University (Israel).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.4-branch/Arrangement_on_surface_2/include/CGAL/IO/Arr_with_history_2_writer.h $
// $Id: Arr_with_history_2_writer.h 40209 2007-09-05 14:41:48Z efif $
// 
//
// Author(s)     : Ron Wein           <wein@post.tau.ac.il>

#ifndef CGAL_ARR_WITH_HISTORY_2_WRITER_H
#define CGAL_ARR_WITH_HISTORY_2_WRITER_H

/*! \file
 * The header file for the Arr_with_history_2_writer<Arrangement> class.
 */

#include <CGAL/IO/Arrangement_2_writer.h>

CGAL_BEGIN_NAMESPACE

/*! \class
 * An auxiliary class for writing an arrangement with history to an
 * output stream.
 */
template <class ArrWithHistory_>
class Arr_with_history_2_writer : private Arrangement_2_writer<ArrWithHistory_>
{
public:

  typedef ArrWithHistory_                                 Arr_with_history_2;
  typedef Arr_with_history_2_writer<Arr_with_history_2>   Self;

protected:

  typedef Arrangement_2_writer<Arr_with_history_2>        Base;
  typedef typename Arr_with_history_2::Size               Size;
  
  typedef typename Arr_with_history_2::Curve_const_iterator
                                                     Curve_const_iterator;
  typedef typename Arr_with_history_2::Curve_const_handle
                                                     Curve_const_handle;
  typedef typename Arr_with_history_2::Induced_edge_iterator
                                                     Induced_edge_iterator;

private:

  // Copy constructor and assignment operator - not supported.
  Arr_with_history_2_writer (const Self& );
  Self& operator= (const Self& );

public:

  /*! Constructor. */
  Arr_with_history_2_writer (const Arr_with_history_2& arr) :
    Base (arr)
  {}

  /*! Write the arrangement. */
  template <class Formatter>
  void operator() (Formatter& formatter)
  {
    // Write the arrangement (without history).
    Base::operator() (formatter);

    // Write the inducing curves.
    formatter.write_curves_begin();

    formatter.write_size ("number_of_curves", this->m_arr.number_of_curves());

    Curve_const_iterator  cvit;
    for (cvit = this->m_arr.curves_begin();
         cvit != this->m_arr.curves_end(); ++cvit)
    {
      _write_curve (formatter, cvit);
    }
    formatter.write_curves_end();

    return;
  }

protected:

  /*! Write a curve with its induced edges. */
  template <class Formatter>
  void _write_curve (Formatter& formatter, Curve_const_iterator cvit) const
  {
    Curve_const_handle  cv = cvit;
    formatter.write_curve_begin();

    // Write the curve.
    formatter.write_curve (*cv);

    // Write the induced edges.
    formatter.write_induced_edges_begin();
    formatter.write_size ("induced_edges",
                          this->m_arr.number_of_induced_edges(cv));
    
    Induced_edge_iterator   ieit;
    for (ieit = this->m_arr.induced_edges_begin(cv);
         ieit != this->m_arr.induced_edges_end(cv); ++ieit)
    {
      formatter.write_halfedge_index (this->_index (&(**ieit)));
    }
    formatter.write_induced_edges_end();
    
    formatter.write_curve_end();
    return;
  }

};

CGAL_END_NAMESPACE

#endif
