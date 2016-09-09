
// ======================================================================
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
// file          : include/CGAL/Segment_2_Triangle_2_intersection.h
// package       : Intersections_2 (2.1.2)
// source        : intersection_2_2.fw
// author(s)     : Geert-Jan Giezeman
//
// coordinator   : Saarbruecken
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_SEGMENT_2_TRIANGLE_2_INTERSECTION_H
#define CGAL_SEGMENT_2_TRIANGLE_2_INTERSECTION_H

#ifndef CGAL_SEGMENT_2_H
#include <CGAL/Segment_2.h>
#endif // CGAL_SEGMENT_2_H
#ifndef CGAL_TRIANGLE_2_H
#include <CGAL/Triangle_2.h>
#endif // CGAL_TRIANGLE_2_H
#ifndef CGAL_POINT_2_H
#include <CGAL/Point_2.h>
#endif // CGAL_POINT_2_H

CGAL_BEGIN_NAMESPACE

template <class R>
class Segment_2_Triangle_2_pair {
public:
    enum Intersection_results {NO, POINT, SEGMENT};
    Segment_2_Triangle_2_pair() ;
    Segment_2_Triangle_2_pair(Segment_2<R> const *seg,
                            Triangle_2<R> const *trian);
    ~Segment_2_Triangle_2_pair() {}
#ifdef CGAL_CFG_RETURN_TYPE_BUG_2
    Intersection_results intersection_type() const
    {
        if (_known)
            return _result;
    // The non const this pointer is used to cast away const.
        Segment_2_Triangle_2_pair<R> *ncthis =
                    (Segment_2_Triangle_2_pair<R> *) this;
        ncthis->_known = true;
        _Straight_2<R> straight(*_seg);
    Line_2<R> l(_trian->vertex(0), _trian->vertex(1));
    if (l.oriented_side(_trian->vertex(2)) == ON_POSITIVE_SIDE) {
            straight.cut_right_off(
                Line_2<R>(_trian->vertex(0), _trian->vertex(1)));
            straight.cut_right_off(
                Line_2<R>(_trian->vertex(1), _trian->vertex(2)));
            straight.cut_right_off(
                Line_2<R>(_trian->vertex(2), _trian->vertex(0)));
        } else {
            straight.cut_right_off(
                Line_2<R>(_trian->vertex(2), _trian->vertex(1)));
            straight.cut_right_off(
                Line_2<R>(_trian->vertex(1), _trian->vertex(0)));
            straight.cut_right_off(
                Line_2<R>(_trian->vertex(0), _trian->vertex(2)));
        }
        switch (straight.current_state()) {
        case _Straight_2<R>::EMPTY:
            ncthis->_result = NO;
            return _result;
        case _Straight_2<R>::POINT: {
            straight.current(ncthis->_intersection_point);
            ncthis->_result = POINT;
            return _result;
            }
        case _Straight_2<R>::SEGMENT: {
            Segment_2<R> seg;
            straight.current(seg);
            ncthis->_intersection_point = seg.start();
            ncthis->_other_point = seg.end();
            ncthis->_result = SEGMENT;
            return _result;
            }
        default:  // should not happen.
            CGAL_kernel_assertion_msg(false, "Internal CGAL error.");
            ncthis->_result = NO;
            return _result;
        }
    }
    
#else
    Intersection_results intersection_type() const;
#endif // CGAL_CFG_RETURN_TYPE_BUG_2
    bool                intersection(Point_2<R> &result) const;
    bool                intersection(Segment_2<R> &result) const;
protected:
    Segment_2<R> const *  _seg;
    Triangle_2<R> const * _trian;
    bool                       _known;
    Intersection_results       _result;
    Point_2<R>            _intersection_point;
    Point_2<R>            _other_point;
};

template <class R>
inline bool do_intersect(
    const Segment_2<R> &p1,
    const Triangle_2<R> &p2)
{
    typedef Segment_2_Triangle_2_pair<R> pair_t;
    pair_t pair(&p1, &p2);
    return pair.intersection_type() != pair_t::NO;
}

CGAL_END_NAMESPACE



#ifndef CGAL_LINE_2_H
#include <CGAL/Line_2.h>
#endif // CGAL_LINE_2_H
#ifndef CGAL_UTILS_H
#include <CGAL/utils.h>
#endif // CGAL_UTILS_H
#ifndef CGAL_NUMBER_UTILS_H
#include <CGAL/number_utils.h>
#endif // CGAL_NUMBER_UTILS_H
#ifndef CGAL_STRAIGHT_2_H
#include <CGAL/Straight_2.h>
#endif // CGAL_STRAIGHT_2_H

CGAL_BEGIN_NAMESPACE

template <class R>
Segment_2_Triangle_2_pair<R>::
Segment_2_Triangle_2_pair()
{
    _known = false;
    _seg = 0;
    _trian = 0;
}

template <class R>
Segment_2_Triangle_2_pair<R>::
Segment_2_Triangle_2_pair(Segment_2<R> const *seg,
                            Triangle_2<R> const *trian)
{
    _known = false;
    _seg = seg;
    _trian = trian;
}

#ifndef CGAL_CFG_RETURN_TYPE_BUG_2
template <class R>
Segment_2_Triangle_2_pair<R>::Intersection_results
Segment_2_Triangle_2_pair<R>::intersection_type() const
{
    if (_known)
        return _result;
// The non const this pointer is used to cast away const.
    Segment_2_Triangle_2_pair<R> *ncthis =
                (Segment_2_Triangle_2_pair<R> *) this;
    ncthis->_known = true;
    _Straight_2<R> straight(*_seg);
Line_2<R> l(_trian->vertex(0), _trian->vertex(1));
if (l.oriented_side(_trian->vertex(2)) == ON_POSITIVE_SIDE) {
        straight.cut_right_off(
            Line_2<R>(_trian->vertex(0), _trian->vertex(1)));
        straight.cut_right_off(
            Line_2<R>(_trian->vertex(1), _trian->vertex(2)));
        straight.cut_right_off(
            Line_2<R>(_trian->vertex(2), _trian->vertex(0)));
    } else {
        straight.cut_right_off(
            Line_2<R>(_trian->vertex(2), _trian->vertex(1)));
        straight.cut_right_off(
            Line_2<R>(_trian->vertex(1), _trian->vertex(0)));
        straight.cut_right_off(
            Line_2<R>(_trian->vertex(0), _trian->vertex(2)));
    }
    switch (straight.current_state()) {
    case _Straight_2<R>::EMPTY:
        ncthis->_result = NO;
        return _result;
    case _Straight_2<R>::POINT: {
        straight.current(ncthis->_intersection_point);
        ncthis->_result = POINT;
        return _result;
        }
    case _Straight_2<R>::SEGMENT: {
        Segment_2<R> seg;
        straight.current(seg);
        ncthis->_intersection_point = seg.start();
        ncthis->_other_point = seg.end();
        ncthis->_result = SEGMENT;
        return _result;
        }
    default:  // should not happen.
        CGAL_kernel_assertion_msg(false, "Internal CGAL error.");
        ncthis->_result = NO;
        return _result;
    }
}

#endif // CGAL_CFG_RETURN_TYPE_BUG_2

template <class R>
bool
Segment_2_Triangle_2_pair<R>::
intersection(Point_2<R> &result) const
{
    if (!_known)
        intersection_type();
    if (_result != POINT)
        return false;
    result = _intersection_point;
    return true;
}

template <class R>
bool
Segment_2_Triangle_2_pair<R>::
intersection(Segment_2<R> &result) const
{
    if (!_known)
        intersection_type();
    if (_result != SEGMENT)
        return false;
    result = Segment_2<R>(_intersection_point, _other_point);
    return true;
}

CGAL_END_NAMESPACE




#ifndef CGAL_OBJECT_H
#include <CGAL/Object.h>
#endif // CGAL_OBJECT_H

CGAL_BEGIN_NAMESPACE

template <class R>
Object
intersection(const Segment_2<R> &seg, const Triangle_2<R>&tr)
{
    typedef Segment_2_Triangle_2_pair<R> is_t;
    is_t ispair(&seg, &tr);
    switch (ispair.intersection_type()) {
    case is_t::NO:
    default:
        return Object();
    case is_t::POINT: {
        Point_2<R> pt;
        ispair.intersection(pt);
        return Object(new Wrapper< Point_2<R> >(pt));
    }
    case is_t::SEGMENT: {
        Segment_2<R> iseg;
        ispair.intersection(iseg);
        return Object(new Wrapper< Segment_2<R> >(iseg));
    }
    }
}

template <class R>
class Triangle_2_Segment_2_pair
: public Segment_2_Triangle_2_pair<R> {
public:
    Triangle_2_Segment_2_pair(
            Triangle_2<R> const *trian,
            Segment_2<R> const *seg) :
                        Segment_2_Triangle_2_pair<R>(seg, trian) {}
};

template <class R>
inline bool do_intersect(
    const Triangle_2<R> &p1,
    const Segment_2<R> &p2)
{
    typedef Triangle_2_Segment_2_pair<R> pair_t;
    pair_t pair(&p1, &p2);
    return pair.intersection_type() != pair_t::NO;
}

template <class R>
inline Object
intersection(const Triangle_2<R> &tr, const Segment_2<R> &seg)
{
    return intersection(seg, tr);
}

CGAL_END_NAMESPACE

#endif