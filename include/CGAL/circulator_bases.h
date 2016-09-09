// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium
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
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// file          : include/CGAL/circulator_bases.h
// package       : Circulator (1.15)
// chapter       : $CGAL_Chapter: Circulators $
// source        : circulator.fw
// revision      : $Revision: 1.19 $
// revision_date : $Date: 1998/03/24 14:04:32 $
// author(s)     : Lutz Kettner
//
// coordinator   : INRIA, Sophia Antipolis
//
// Base classes and tags to build own circulators.
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_CIRCULATOR_BASES_H
#define CGAL_CIRCULATOR_BASES_H 1

#ifndef CGAL_PROTECT_ITERATOR_H
#include <iterator.h>
#define CGAL_PROTECT_ITERATOR_H
#endif // CGAL_PROTECT_ITERATOR_H

struct CGAL_Circulator_tag {};                   // any circulator.
struct CGAL_Iterator_tag {};                     // any iterator.

struct CGAL_Forward_circulator_tag
    : public forward_iterator_tag {};
struct CGAL_Bidirectional_circulator_tag
    : public bidirectional_iterator_tag {};
struct CGAL_Random_access_circulator_tag
    : public random_access_iterator_tag {};
template <class T, class Dist, class Size>
struct CGAL_Forward_circulator_base : public forward_iterator<T,Dist> {
    typedef T                           value_type;
    typedef Dist                        difference_type;
    typedef Size                        size_type;
    typedef T*                          pointer;
    typedef const T*                    const_pointer;
    typedef T&                          reference;
    typedef const T&                    const_reference;
    typedef CGAL_Forward_circulator_tag  iterator_category;
};
template <class T, class Dist, class Size>
struct CGAL_Bidirectional_circulator_base
: public bidirectional_iterator<T,Dist> {
    typedef T                           value_type;
    typedef Dist                        difference_type;
    typedef Size                        size_type;
    typedef T*                          pointer;
    typedef const T*                    const_pointer;
    typedef T&                          reference;
    typedef const T&                    const_reference;
    typedef CGAL_Bidirectional_circulator_tag iterator_category;
};
template <class T, class Dist, class Size>
struct CGAL_Random_access_circulator_base
: public random_access_iterator<T,Dist> {
    typedef T                           value_type;
    typedef Dist                        difference_type;
    typedef Size                        size_type;
    typedef T*                          pointer;
    typedef const T*                    const_pointer;
    typedef T&                          reference;
    typedef const T&                    const_reference;
    typedef CGAL_Random_access_circulator_tag iterator_category;
};

// variant base classes
// ---------------------
template <class T, class Dist, class Size>
class CGAL_Forward_circulator_ptrbase         // forward circulator.
{
    protected:
        void* _ptr;
    public:
        typedef CGAL_Forward_circulator_tag  iterator_category;
        typedef T                           value_type;
        typedef Dist                        difference_type;
        typedef Size                        size_type;
        typedef T*                          pointer;
        typedef const T*                    const_pointer;
        typedef T&                          reference;
        typedef const T&                    const_reference;
        CGAL_Forward_circulator_ptrbase()        : _ptr(NULL) {}
        CGAL_Forward_circulator_ptrbase(void* p) : _ptr(p) {}
};
template <class T, class Dist, class Size>
class CGAL_Bidirectional_circulator_ptrbase   // bidirectional circulator.
{
    protected:
        void* _ptr;
    public:
        typedef CGAL_Bidirectional_circulator_tag  iterator_category;
        typedef T                           value_type;
        typedef Dist                        difference_type;
        typedef Size                        size_type;
        typedef T*                          pointer;
        typedef const T*                    const_pointer;
        typedef T&                          reference;
        typedef const T&                    const_reference;
        CGAL_Bidirectional_circulator_ptrbase()        : _ptr(NULL) {}
        CGAL_Bidirectional_circulator_ptrbase(void* p) : _ptr(p) {}
};
template <class T, class Dist, class Size>
class CGAL_Random_access_circulator_ptrbase   // random access circulator.
{
    protected:
        void* _ptr;
    public:
        typedef CGAL_Random_access_circulator_tag iterator_category;
        typedef T                           value_type;
        typedef Dist                        difference_type;
        typedef Size                        size_type;
        typedef T*                          pointer;
        typedef const T*                    const_pointer;
        typedef T&                          reference;
        typedef const T&                    const_reference;
        CGAL_Random_access_circulator_ptrbase()        : _ptr(NULL) {}
        CGAL_Random_access_circulator_ptrbase(void* p) : _ptr(p) {}
};

#endif // CGAL_CIRCULATOR_BASES_H //
// EOF //
