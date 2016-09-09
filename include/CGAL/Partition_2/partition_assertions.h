// Copyright (c) 1997  Max-Planck-Institute Saarbruecken (Germany).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Partition_2/include/CGAL/Partition_2/partition_assertions.h $
// $Id: partition_assertions.h 44139 2008-07-14 11:16:41Z spion $
// 
//
// Author(s)     : script by Geert-Jan Giezeman and Sven Schoenherr 



// macro definitions
// =================
// assertions
// ----------


#if defined(CGAL_PARTITION_NO_ASSERTIONS) || defined(CGAL_NO_ASSERTIONS) \
  || defined(NDEBUG)
#  define CGAL_partition_assertion(EX) ((void)0)
#  define CGAL_partition_assertion_msg(EX,MSG) ((void)0)
#  define CGAL_partition_assertion_code(CODE)
#else
#  define CGAL_partition_assertion(EX) \
   (CGAL::possibly(EX)?((void)0): ::CGAL::assertion_fail( # EX , __FILE__, __LINE__))
#  define CGAL_partition_assertion_msg(EX,MSG) \
   (CGAL::possibly(EX)?((void)0): ::CGAL::assertion_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_partition_assertion_code(CODE) CODE
#endif // CGAL_PARTITION_NO_ASSERTIONS

#if defined(CGAL_PARTITION_NO_ASSERTIONS) || defined(CGAL_NO_ASSERTIONS) \
  || (!defined(CGAL_PARTITION_CHECK_EXACTNESS) && !defined(CGAL_CHECK_EXACTNESS))\
  || defined(NDEBUG)
#  define CGAL_partition_exactness_assertion(EX) ((void)0)
#  define CGAL_partition_exactness_assertion_msg(EX,MSG) ((void)0)
#  define CGAL_partition_exactness_assertion_code(CODE)
#else
#  define CGAL_partition_exactness_assertion(EX) \
   (CGAL::possibly(EX)?((void)0): ::CGAL::assertion_fail( # EX , __FILE__, __LINE__))
#  define CGAL_partition_exactness_assertion_msg(EX,MSG) \
   (CGAL::possibly(EX)?((void)0): ::CGAL::assertion_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_partition_exactness_assertion_code(CODE) CODE
#endif // CGAL_PARTITION_NO_ASSERTIONS

#if defined(CGAL_PARTITION_NO_ASSERTIONS) \
  || defined(CGAL_NO_ASSERTIONS) \
  || (!defined(CGAL_PARTITION_CHECK_EXPENSIVE) && !defined(CGAL_CHECK_EXPENSIVE)) \
  || defined(NDEBUG)
#  define CGAL_partition_expensive_assertion(EX) ((void)0)
#  define CGAL_partition_expensive_assertion_msg(EX,MSG) ((void)0)
#  define CGAL_partition_expensive_assertion_code(CODE)
#else
#  define CGAL_partition_expensive_assertion(EX) \
   (CGAL::possibly(EX)?((void)0): ::CGAL::assertion_fail( # EX , __FILE__, __LINE__))
#  define CGAL_partition_expensive_assertion_msg(EX,MSG) \
   (CGAL::possibly(EX)?((void)0): ::CGAL::assertion_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_partition_expensive_assertion_code(CODE) CODE
#endif // CGAL_PARTITION_NO_ASSERTIONS

#if defined(CGAL_PARTITION_NO_ASSERTIONS) || defined(CGAL_NO_ASSERTIONS) \
  || (!defined(CGAL_PARTITION_CHECK_EXACTNESS) && !defined(CGAL_CHECK_EXACTNESS))\
  || (!defined(CGAL_PARTITION_CHECK_EXPENSIVE) && !defined(CGAL_CHECK_EXPENSIVE)) \
  || defined(NDEBUG)
#  define CGAL_partition_expensive_exactness_assertion(EX) ((void)0)
#  define CGAL_partition_expensive_exactness_assertion_msg(EX,MSG) ((void)0)
#  define CGAL_partition_expensive_exactness_assertion_code(CODE)
#else
#  define CGAL_partition_expensive_exactness_assertion(EX) \
   (CGAL::possibly(EX)?((void)0): ::CGAL::assertion_fail( # EX , __FILE__, __LINE__))
#  define CGAL_partition_expensive_exactness_assertion_msg(EX,MSG) \
   (CGAL::possibly(EX)?((void)0): ::CGAL::assertion_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_partition_expensive_exactness_assertion_code(CODE) CODE
#endif // CGAL_PARTITION_NO_ASSERTIONS


// preconditions
// -------------

#if defined(CGAL_PARTITION_NO_PRECONDITIONS) || defined(CGAL_NO_PRECONDITIONS) \
  || defined(NDEBUG)
#  define CGAL_partition_precondition(EX) ((void)0)
#  define CGAL_partition_precondition_msg(EX,MSG) ((void)0)
#  define CGAL_partition_precondition_code(CODE)
#else
#  define CGAL_partition_precondition(EX) \
   (CGAL::possibly(EX)?((void)0): ::CGAL::precondition_fail( # EX , __FILE__, __LINE__))
#  define CGAL_partition_precondition_msg(EX,MSG) \
   (CGAL::possibly(EX)?((void)0): ::CGAL::precondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_partition_precondition_code(CODE) CODE
#endif // CGAL_PARTITION_NO_PRECONDITIONS

#if defined(CGAL_PARTITION_NO_PRECONDITIONS) || defined(CGAL_NO_PRECONDITIONS) \
  || (!defined(CGAL_PARTITION_CHECK_EXACTNESS) && !defined(CGAL_CHECK_EXACTNESS))\
  || defined(NDEBUG)
#  define CGAL_partition_exactness_precondition(EX) ((void)0)
#  define CGAL_partition_exactness_precondition_msg(EX,MSG) ((void)0)
#  define CGAL_partition_exactness_precondition_code(CODE)
#else
#  define CGAL_partition_exactness_precondition(EX) \
   (CGAL::possibly(EX)?((void)0): ::CGAL::precondition_fail( # EX , __FILE__, __LINE__))
#  define CGAL_partition_exactness_precondition_msg(EX,MSG) \
   (CGAL::possibly(EX)?((void)0): ::CGAL::precondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_partition_exactness_precondition_code(CODE) CODE
#endif // CGAL_PARTITION_NO_PRECONDITIONS

#if defined(CGAL_PARTITION_NO_PRECONDITIONS) || defined(CGAL_NO_PRECONDITIONS) \
  || (!defined(CGAL_PARTITION_CHECK_EXPENSIVE) && !defined(CGAL_CHECK_EXPENSIVE)) \
  || defined(NDEBUG)
#  define CGAL_partition_expensive_precondition(EX) ((void)0)
#  define CGAL_partition_expensive_precondition_msg(EX,MSG) ((void)0)
#  define CGAL_partition_expensive_precondition_code(CODE)
#else
#  define CGAL_partition_expensive_precondition(EX) \
   (CGAL::possibly(EX)?((void)0): ::CGAL::precondition_fail( # EX , __FILE__, __LINE__))
#  define CGAL_partition_expensive_precondition_msg(EX,MSG) \
   (CGAL::possibly(EX)?((void)0): ::CGAL::precondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_partition_expensive_precondition_code(CODE) CODE
#endif // CGAL_PARTITION_NO_PRECONDITIONS

#if defined(CGAL_PARTITION_NO_PRECONDITIONS) || defined(CGAL_NO_PRECONDITIONS) \
  || (!defined(CGAL_PARTITION_CHECK_EXACTNESS) && !defined(CGAL_CHECK_EXACTNESS))\
  || (!defined(CGAL_PARTITION_CHECK_EXPENSIVE) && !defined(CGAL_CHECK_EXPENSIVE)) \
  || defined(NDEBUG)
#  define CGAL_partition_expensive_exactness_precondition(EX) ((void)0)
#  define CGAL_partition_expensive_exactness_precondition_msg(EX,MSG) ((void)0)
#  define CGAL_partition_expensive_exactness_precondition_code(CODE)
#else
#  define CGAL_partition_expensive_exactness_precondition(EX) \
   (CGAL::possibly(EX)?((void)0): ::CGAL::precondition_fail( # EX , __FILE__, __LINE__))
#  define CGAL_partition_expensive_exactness_precondition_msg(EX,MSG) \
   (CGAL::possibly(EX)?((void)0): ::CGAL::precondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_partition_expensive_exactness_precondition_code(CODE) CODE
#endif // CGAL_PARTITION_NO_PRECONDITIONS


// postconditions
// --------------

#if defined(CGAL_PARTITION_NO_POSTCONDITIONS) || defined(CGAL_NO_POSTCONDITIONS) \
  || defined(NDEBUG)
#  define CGAL_partition_postcondition(EX) ((void)0)
#  define CGAL_partition_postcondition_msg(EX,MSG) ((void)0)
#  define CGAL_partition_postcondition_code(CODE)
#else
#  define CGAL_partition_postcondition(EX) \
   (CGAL::possibly(EX)?((void)0): ::CGAL::postcondition_fail( # EX , __FILE__, __LINE__))
#  define CGAL_partition_postcondition_msg(EX,MSG) \
   (CGAL::possibly(EX)?((void)0): ::CGAL::postcondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_partition_postcondition_code(CODE) CODE
#endif // CGAL_PARTITION_NO_POSTCONDITIONS

#if defined(CGAL_PARTITION_NO_POSTCONDITIONS) || defined(CGAL_NO_POSTCONDITIONS) \
  || (!defined(CGAL_PARTITION_CHECK_EXACTNESS) && !defined(CGAL_CHECK_EXACTNESS))\
  || defined(NDEBUG)
#  define CGAL_partition_exactness_postcondition(EX) ((void)0)
#  define CGAL_partition_exactness_postcondition_msg(EX,MSG) ((void)0)
#  define CGAL_partition_exactness_postcondition_code(CODE)
#else
#  define CGAL_partition_exactness_postcondition(EX) \
   (CGAL::possibly(EX)?((void)0): ::CGAL::postcondition_fail( # EX , __FILE__, __LINE__))
#  define CGAL_partition_exactness_postcondition_msg(EX,MSG) \
   (CGAL::possibly(EX)?((void)0): ::CGAL::postcondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_partition_exactness_postcondition_code(CODE) CODE
#endif // CGAL_PARTITION_NO_POSTCONDITIONS

#if defined(CGAL_PARTITION_NO_POSTCONDITIONS) || defined(CGAL_NO_POSTCONDITIONS) \
  || (!defined(CGAL_PARTITION_CHECK_EXPENSIVE) && !defined(CGAL_CHECK_EXPENSIVE)) \
  || defined(NDEBUG)
#  define CGAL_partition_expensive_postcondition(EX) ((void)0)
#  define CGAL_partition_expensive_postcondition_msg(EX,MSG) ((void)0)
#  define CGAL_partition_expensive_postcondition_code(CODE)
#else
#  define CGAL_partition_expensive_postcondition(EX) \
   (CGAL::possibly(EX)?((void)0): ::CGAL::postcondition_fail( # EX , __FILE__, __LINE__))
#  define CGAL_partition_expensive_postcondition_msg(EX,MSG) \
   (CGAL::possibly(EX)?((void)0): ::CGAL::postcondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_partition_expensive_postcondition_code(CODE) CODE
#endif // CGAL_PARTITION_NO_POSTCONDITIONS

#if defined(CGAL_PARTITION_NO_POSTCONDITIONS) || defined(CGAL_NO_POSTCONDITIONS) \
  || (!defined(CGAL_PARTITION_CHECK_EXACTNESS) && !defined(CGAL_CHECK_EXACTNESS))\
  || (!defined(CGAL_PARTITION_CHECK_EXPENSIVE) && !defined(CGAL_CHECK_EXPENSIVE)) \
  || defined(NDEBUG)
#  define CGAL_partition_expensive_exactness_postcondition(EX) ((void)0)
#  define CGAL_partition_expensive_exactness_postcondition_msg(EX,MSG) ((void)0)
#  define CGAL_partition_expensive_exactness_postcondition_code(CODE)
#else
#  define CGAL_partition_expensive_exactness_postcondition(EX) \
   (CGAL::possibly(EX)?((void)0): ::CGAL::postcondition_fail( # EX , __FILE__, __LINE__))
#  define CGAL_partition_expensive_exactness_postcondition_msg(EX,MSG) \
   (CGAL::possibly(EX)?((void)0): ::CGAL::postcondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_partition_expensive_exactness_postcondition_code(CODE) CODE
#endif // CGAL_PARTITION_NO_POSTCONDITIONS


// warnings
// --------

#if defined(CGAL_PARTITION_NO_WARNINGS) || defined(CGAL_NO_WARNINGS) \
  || defined(NDEBUG)
#  define CGAL_partition_warning(EX) ((void)0)
#  define CGAL_partition_warning_msg(EX,MSG) ((void)0)
#  define CGAL_partition_warning_code(CODE)
#else
#  define CGAL_partition_warning(EX) \
   (CGAL::possibly(EX)?((void)0): ::CGAL::warning_fail( # EX , __FILE__, __LINE__))
#  define CGAL_partition_warning_msg(EX,MSG) \
   (CGAL::possibly(EX)?((void)0): ::CGAL::warning_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_partition_warning_code(CODE) CODE
#endif // CGAL_PARTITION_NO_WARNINGS

#if defined(CGAL_PARTITION_NO_WARNINGS) || defined(CGAL_NO_WARNINGS) \
  || (!defined(CGAL_PARTITION_CHECK_EXACTNESS) && !defined(CGAL_CHECK_EXACTNESS))\
  || defined(NDEBUG)
#  define CGAL_partition_exactness_warning(EX) ((void)0)
#  define CGAL_partition_exactness_warning_msg(EX,MSG) ((void)0)
#  define CGAL_partition_exactness_warning_code(CODE)
#else
#  define CGAL_partition_exactness_warning(EX) \
   (CGAL::possibly(EX)?((void)0): ::CGAL::warning_fail( # EX , __FILE__, __LINE__))
#  define CGAL_partition_exactness_warning_msg(EX,MSG) \
   (CGAL::possibly(EX)?((void)0): ::CGAL::warning_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_partition_exactness_warning_code(CODE) CODE
#endif // CGAL_PARTITION_NO_WARNINGS

#if defined(CGAL_PARTITION_NO_WARNINGS) || defined(CGAL_NO_WARNINGS) \
  || (!defined(CGAL_PARTITION_CHECK_EXPENSIVE) && !defined(CGAL_CHECK_EXPENSIVE)) \
  || defined(NDEBUG)
#  define CGAL_partition_expensive_warning(EX) ((void)0)
#  define CGAL_partition_expensive_warning_msg(EX,MSG) ((void)0)
#  define CGAL_partition_expensive_warning_code(CODE)
#else
#  define CGAL_partition_expensive_warning(EX) \
   (CGAL::possibly(EX)?((void)0): ::CGAL::warning_fail( # EX , __FILE__, __LINE__))
#  define CGAL_partition_expensive_warning_msg(EX,MSG) \
   (CGAL::possibly(EX)?((void)0): ::CGAL::warning_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_partition_expensive_warning_code(CODE) CODE
#endif // CGAL_PARTITION_NO_WARNINGS

#if defined(CGAL_PARTITION_NO_WARNINGS) || defined(CGAL_NO_WARNINGS) \
  || (!defined(CGAL_PARTITION_CHECK_EXACTNESS) && !defined(CGAL_CHECK_EXACTNESS))\
  || (!defined(CGAL_PARTITION_CHECK_EXPENSIVE) && !defined(CGAL_CHECK_EXPENSIVE)) \
  || defined(NDEBUG)
#  define CGAL_partition_expensive_exactness_warning(EX) ((void)0)
#  define CGAL_partition_expensive_exactness_warning_msg(EX,MSG) ((void)0)
#  define CGAL_partition_expensive_exactness_warning_code(CODE)
#else
#  define CGAL_partition_expensive_exactness_warning(EX) \
   (CGAL::possibly(EX)?((void)0): ::CGAL::warning_fail( # EX , __FILE__, __LINE__))
#  define CGAL_partition_expensive_exactness_warning_msg(EX,MSG) \
   (CGAL::possibly(EX)?((void)0): ::CGAL::warning_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_partition_expensive_exactness_warning_code(CODE) CODE
#endif // CGAL_PARTITION_NO_WARNINGS


