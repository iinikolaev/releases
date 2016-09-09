// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

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
// file          : include/CGAL/point_generators_2.h
// package       : Generator (2.62)
// chapter       : $CGAL_Chapter: Geometric Object Generators $
// revision      : $Revision: 1.7 $
// revision_date : $Date: 2002/04/25 07:53:43 $
// author(s)     : Lutz Kettner
//
// coordinator   : INRIA, Sophia Antipolis
//
// 2D Point Generators
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_POINT_GENERATORS_2_H
#define CGAL_POINT_GENERATORS_2_H 1
#include <CGAL/generators.h>
#include <iterator>
#include <CGAL/number_type_basic.h>

CGAL_BEGIN_NAMESPACE

template < class P, class Creator = Creator_uniform_2<double,P> >
class Random_points_in_disc_2 : public Random_generator_base<P>{
    void generate_point();
public:
    typedef Random_points_in_disc_2<P,Creator> This;
    Random_points_in_disc_2( double r = 1, Random& rnd = default_random)
        // g is an input iterator creating points of type `P' uniformly
        // distributed in the open disc with radius r, i.e. |`*g'| < r .
        // Two random numbers are needed from `rnd' for each point.
    : Random_generator_base<P>(r, rnd) { generate_point(); }
    This& operator++() {
        generate_point();
        return *this;
    }
    This  operator++(int) {
        This tmp = *this;
        ++(*this);
        return tmp;
    }
};

template < class P, class Creator >
void
Random_points_in_disc_2<P,Creator>::
generate_point() {
    typedef typename Creator::argument_type T;
    double alpha = _rnd.get_double() * 2.0 * CGAL_PI;
    double r     = d_range * CGAL_CLIB_STD::sqrt( _rnd.get_double());
    Creator creator;
    d_item = creator( T(r * CGAL_CLIB_STD::cos(alpha)), 
                      T(r * CGAL_CLIB_STD::sin(alpha)));
}


template < class P, class Creator = Creator_uniform_2<double,P> >
class Random_points_on_circle_2 : public Random_generator_base<P> {
    void generate_point();
public:
    typedef Random_points_on_circle_2<P,Creator> This;
    Random_points_on_circle_2( double r = 1, Random& rnd = default_random)
        // g is an input iterator creating points of type `P' uniformly
        // distributed on the circle with radius r, i.e. |`*g'| == r . A
        // single random number is needed from `rnd' for each point.
    : Random_generator_base<P>(r, rnd) { generate_point(); }
    This& operator++()    {
        generate_point();
        return *this;
    }
    This  operator++(int) {
        This tmp = *this;
        ++(*this);
        return tmp;
    }
};

template < class P, class Creator >
void
Random_points_on_circle_2<P,Creator>::
generate_point() {
    typedef typename Creator::argument_type T;
    double a = _rnd.get_double() * 2.0 * CGAL_PI;
    Creator creator;
    d_item = creator( T(d_range * CGAL_CLIB_STD::cos(a)), 
                      T(d_range * CGAL_CLIB_STD::sin(a)));
}


template < class P, class Creator = Creator_uniform_2<double,P> >
class Random_points_in_square_2 : public Random_generator_base<P> {
    void generate_point();
public:
    typedef Random_points_in_square_2<P,Creator> This;
    Random_points_in_square_2( double a = 1, Random& rnd = default_random)
        // g is an input iterator creating points of type `P' uniformly
        // distributed in the half-open square with side length a,
        // centered around the origin, i.e. \forall p = `*g': -\frac{a}{2}
        // <= p.x() < \frac{a}{2} and -\frac{a}{2} <= p.y() < \frac{a}{2}
        // . Two random numbers are needed from `rnd' for each point.
    : Random_generator_base<P>( a, rnd) { generate_point(); }
    This& operator++()    {
        generate_point();
        return *this;
    }
    This  operator++(int) {
        This tmp = *this;
        ++(*this);
        return tmp;
    }
};

template < class P, class Creator >
void
Random_points_in_square_2<P,Creator>::
generate_point() {
    typedef typename Creator::argument_type  T;
    Creator creator;
    d_item = creator( T(d_range * (2 * _rnd.get_double() - 1.0)),
                      T(d_range * (2 * _rnd.get_double() - 1.0)));
}


template < class P, class Creator = Creator_uniform_2<double,P> >
class Random_points_on_square_2 : public Random_generator_base<P> {
    void generate_point();
public:
    typedef Random_points_on_square_2<P,Creator> This;
    Random_points_on_square_2( double a = 1, Random& rnd = default_random)
        // g is an input iterator creating points of type `P' uniformly
        // distributed on the boundary of the square with side length a,
        // centered around the origin, i.e. \forall p = `*g': one
        // coordinate is either \frac{a}{2} or -\frac{a}{2} and for the
        // other coordinate c holds -\frac{a}{2} <= c < \frac{a}{2} . A
        // single random number is needed from `rnd' for each point.
    : Random_generator_base<P>( a, rnd)  { generate_point(); }
    This& operator++()    {
        generate_point();
        return *this;
    }
    This  operator++(int) {
        This tmp = *this;
        ++(*this);
        return tmp;
    }
};

template < class P, class Creator >
void
Random_points_on_square_2<P,Creator>::
generate_point() {
    typedef typename Creator::argument_type  T;
    double d = _rnd.get_double() * 4.0;
    int    k = int(d);
    d = d_range * (2 * (d - k) - 1.0);
    CGAL_assertion( - d_range <= d && d < d_range);
    Creator creator;
    switch (k) {
    case 0:
        d_item = creator(        T(d), T(-d_range));
        break;
    case 1:
        d_item = creator(        T(d),  T(d_range));
        break;
    case 2:
        d_item = creator( T(-d_range),        T(d));
        break;
    case 3:
        d_item = creator( T( d_range),        T(d));
        break;
    }
}


template < class P, class Creator = Creator_uniform_2<double,P> >
class Random_points_on_segment_2 : public Random_generator_base<P> {
    P _p;
    P _q;
    void generate_point();
public:
    typedef Random_points_on_segment_2<P,Creator> This;
    Random_points_on_segment_2( const P& p = P( -1, 0),
                                const P& q = P(  1, 0),
                                Random& rnd = default_random)
        // g is an input iterator creating points of type `P' uniformly
        // distributed on the segment from p to q except q, i.e. `*g' ==
        // \lambda p + (1-\lambda)\, q where 0 <= \lambda < 1 . A single
        // random number is needed from `rnd' for each point.
    : Random_generator_base<P>( max( max( to_double(p.x()), to_double(q.x())),
                                          max( to_double(p.y()),
                                               to_double(q.y()))),
                                 rnd) , _p(p), _q(q) {
        generate_point();
    }
    const P&  source() const { return _p; }
    const P&  target() const { return _q; }
    This& operator++()    {
        generate_point();
        return *this;
    }
    This  operator++(int) {
        This tmp = *this;
        ++(*this);
        return tmp;
    }
};

template < class P, class Creator >
void
Random_points_on_segment_2<P,Creator>::
generate_point() {
    typedef typename Creator::argument_type  T;
    double la = _rnd.get_double();
    double mu = 1.0 - la;
    Creator creator;
    d_item = creator( T(mu * to_double(_p.x()) + la * to_double(_q.x())),
                      T(mu * to_double(_p.y()) + la * to_double(_q.y())));
}

template < class P >
class Points_on_segment_2 : public Generator_base<P> {
    P _p;
    P _q;
    std::size_t  d_i;
    std::size_t  d_mx;
    void generate_point();
public:
    typedef Points_on_segment_2<P> This;
    Points_on_segment_2() {}
    Points_on_segment_2( const P& p, const P& q,
                         std::size_t mx, std::size_t i = 0)
    : Generator_base<P>( max( max( to_double(p.x()), to_double(q.x())),
                                   max( to_double(p.y()), to_double(q.y())))),
                          _p(p), _q(q), d_i(i), d_mx(mx) {
        generate_point();
    }
    const P&  source() const { return _p; }
    const P&  target() const { return _q; }
    // Sufficient equality test.
    bool operator==( const This& base) const { return ( d_i == base.d_i); }
    bool operator!=( const This& base) const { return ! operator==(base); }
    This& operator++()    {
        d_i++;
        generate_point();
        return *this;
    }
    This  operator++(int) {
        This tmp = *this;
        ++(*this);
        return tmp;
    }
};

template < class P >
void
Points_on_segment_2<P>::
generate_point() { d_item = _p + (_q-_p) * d_i / (d_mx-1); }

template <class OutputIterator, class Creator>
OutputIterator
points_on_square_grid_2( double a, std::size_t n, OutputIterator o,
                         Creator creator)
{
    typedef typename Creator::argument_type T;
    if  (n == 0)
        return o;
    int m = int(CGAL_CLIB_STD::ceil(std::sqrt(static_cast<double>(n))));
    double base = -a;  // Left and bottom boundary.
    double step = (2*a)/(m - 1);
    int j = 0;
    double px = base;
    double py = base;
    *o++ = creator( T(px), T(py));
    for (std::size_t i = 1; i < n; i++) {
        j++;
        if ( j == m) {
            px = base;
            py = py + step;
            j = 0;
        } else {
            px = px + step;
        }
        *o++ = creator( T(px), T(py));
    }
    return o;
}

template <class OutputIterator>
OutputIterator
points_on_square_grid_2( double a, std::size_t n, OutputIterator o)
{
    typedef std::iterator_traits<OutputIterator> ITraits;
    typedef typename ITraits::value_type         P;
    return points_on_square_grid_2(a, n, o, Creator_uniform_2<double,P>());
}

template <class P, class OutputIterator>
OutputIterator
points_on_segment_2( const P& p, const P& q, std::size_t n,
                     OutputIterator o)
    // creates n points regular spaced on the segment from p to q, i.e.
    // \forall i: 0 <= i < n: o[i] := \frac{n-i-1}{n-1} p + \frac{i}{n-1
    // } q.
{
    for (std::size_t i = 0; i < n; i++) {
        *o++ = p + (q-p) * i / (n-1);
    }
    return o;
}

template <class ForwardIterator, class Creator>
void perturb_points_2( ForwardIterator first,
                       ForwardIterator last,
                       double xeps,
                       double yeps,
                       Random& rnd,
                       Creator creator)
    // perturbs the points in the range [`first',`last') by replacing
    // each point with a random point from the rectangle `xeps' \times
    // `yeps' centered around the original point. Two random numbers are
    // needed from `rnd' for each point. Precondition:
    // The expression `to_double((*first).x())' and `to_double((
    // *begin).y())' must be legal.
{
    typedef typename Creator::argument_type T;
    xeps *= 2.0;
    yeps *= 2.0;
    for ( ; first != last; ++first) {
        double x = to_double( (*first).x());
        double y = to_double( (*first).y());
        x += xeps * (rnd.get_double() - 0.5);
        y += yeps * (rnd.get_double() - 0.5);
        *first = creator( T(x), T(y));
    }
}

template <class ForwardIterator>
void perturb_points_2( ForwardIterator first,
                       ForwardIterator last,
                       double xeps,
                       double yeps,
                       Random& rnd)
{
    typedef std::iterator_traits<ForwardIterator> ITraits;
    typedef typename ITraits::value_type          P;
    perturb_points_2( first, last, xeps, yeps, rnd,
                      Creator_uniform_2<double,P>());
}

template <class ForwardIterator>
inline
void perturb_points_2( ForwardIterator first,
                       ForwardIterator last,
                       double xeps,
                       Random& rnd)
{
    perturb_points_2( first, last, xeps, xeps, rnd);
}

template <class ForwardIterator>
void perturb_points_2( ForwardIterator first,
                       ForwardIterator last,
                       double xeps,
                       double yeps)
{
    perturb_points_2( first, last, xeps, yeps, default_random);
}

template <class ForwardIterator>
void perturb_points_2( ForwardIterator first,
                       ForwardIterator last,
                       double xeps)
{
    perturb_points_2( first, last, xeps, xeps, default_random);
}
template <class RandomAccessIterator, class OutputIterator, class Creator>
OutputIterator random_collinear_points_2(
                       RandomAccessIterator first,
                       RandomAccessIterator last,
                       std::size_t n,
                       OutputIterator first2,
                       Random& rnd,
                       Creator creator)
{
    typedef typename Creator::result_type   Point;
    typedef typename Creator::argument_type T;

    int m = last - first;
    for ( std::size_t i = 0; i < n; i++) {
        const Point& p = first[ rnd.get_int( 0, m-1)];
        const Point& q = first[ rnd.get_int( 0, m-1)];
        double la = rnd.get_double();
        double mu = 1.0 - la;
        *first2++ = creator(T(mu * to_double(p.x()) +
                              la * to_double(q.x())),
                            T(mu * to_double(p.y()) +
                              la * to_double(q.y())));
    }
    return first2;
}

template <class RandomAccessIterator, class OutputIterator>
OutputIterator random_collinear_points_2(
                       RandomAccessIterator first,
                       RandomAccessIterator last,
                       std::size_t n,
                       OutputIterator first2,
                       Random& rnd)
    // choose two random points from the range [`first',`last'), create a
    // random third point on the segment connecting this two points, and
    // write it to `first2'. Repeat this n times, thus writing n points to
    // `first2' that are collinear with points in the range [`first',
    // `last'). Three random numbers are needed from `rnd' for each point.
    // Returns the value of `first2' after inserting the n points.
    // Precondition: The expression `to_double((*first).x()
    // )' and `to_double((*first).y())' must be legal.
{
    typedef std::iterator_traits<RandomAccessIterator> ITraits;
    typedef typename ITraits::value_type               P;
    return random_collinear_points_2( first, last, n, first2, rnd,
                                      Creator_uniform_2<double,P>());
}

template <class RandomAccessIterator, class OutputIterator>
OutputIterator random_collinear_points_2(
                       RandomAccessIterator first,
                       RandomAccessIterator last,
                       std::size_t n,
                       OutputIterator first2)
{
    return  random_collinear_points_2( first, last, n, first2,
                                       default_random);
}



CGAL_END_NAMESPACE
#endif // CGAL_POINT_GENERATORS_2_H //
// EOF //
