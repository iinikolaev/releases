// Copyright (c) 2005,2006,2008  INRIA Sophia-Antipolis (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.4-branch/Profiling_tools/include/CGAL/Profile_counter.h $
// $Id: Profile_counter.h 47261 2008-12-07 14:58:18Z spion $
//
//
// Author(s)     : Sylvain Pion

#ifndef CGAL_PROFILE_COUNTER_H
#define CGAL_PROFILE_COUNTER_H

// This file contains several classes to help in profiling, together with macros
// triggered by CGAL_PROFILE to enable them:
//
// - Profile_counter which is able to keep track of a number, and prints a
//   message in the destructor.  Typically, it can be used as a profile counter
//   in a static variable.
//
// - Profile_histogram_counter which is similar, but the counter is indexed by
//   a value (unsigned int), and the final dump is the histogram of the non-zero
//   counters.
//
// - Profile_branch_counter which keeps track of 2 counters, aiming at measuring
//   the ratio corresponding to the number of times a branch is taken.
//
// See also CGAL/Profile_timer.h

// TODO :
// - Really complete the documentation!
// - Probably at some point we will need ways to selectively enable/disable profilers?
//   (kind-wise and/or place-wise)
// - Ideas for new kinds of profilers:
//   - lock counters in parallel mode
//     (e.g. time spent spinning, and/or number of locks taken or forbidden...)

#include <CGAL/config.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <map>

CGAL_BEGIN_NAMESPACE

struct Profile_counter
{
    Profile_counter(const std::string & ss)
      : i(0), s(ss) {}

    void operator++() { ++i; }

    ~Profile_counter()
    {
        std::cerr << "[CGAL::Profile_counter] "
                  << std::setw(10) << i << " " << s << std::endl;
    }

private:
    unsigned int i;
    const std::string s;
};



struct Profile_histogram_counter
{
    Profile_histogram_counter(const std::string & ss)
      : s(ss) {}

    void operator()(unsigned i) { ++counters[i]; }

    ~Profile_histogram_counter()
    {
        unsigned total=0;
        for (Counters::const_iterator it=counters.begin(), end=counters.end();
             it != end; ++it) {
            std::cerr << "[CGAL::Profile_histogram_counter] " << s;
            std::cerr << " [ " << std::setw(10) << it->first << " : "
                               << std::setw(10) << it->second << " ]"
                               << std::endl;
            total += it->second;
        }
        std::cerr << "[CGAL::Profile_histogram_counter] " << s;
        std::cerr << " [ " << std::setw(10) << "Total" << " : "
                           << std::setw(10) << total << " ]" << std::endl;
    }

private:
    typedef std::map<unsigned, unsigned>  Counters;
    Counters  counters;
    const std::string s;
};


struct Profile_branch_counter
{
    Profile_branch_counter(const std::string & ss)
      : i(0), j(0), s(ss) {}

    void operator++() { ++i; }

    void increment_branch() { ++j; }

    ~Profile_branch_counter()
    {
        std::cerr << "[CGAL::Profile_branch_counter] "
                  << std::setw(10) << j << " / "
                  << std::setw(10) << i << " " << s << std::endl;
    }

private:
    unsigned int i, j;
    const std::string s;
};


#ifdef CGAL_PROFILE
#  define CGAL_PROFILER(Y) \
          { static CGAL::Profile_counter tmp(Y); ++tmp; }
#  define CGAL_HISTOGRAM_PROFILER(Y, Z) \
          { static CGAL::Profile_histogram_counter tmp(Y); tmp(Z); }
#  define CGAL_BRANCH_PROFILER(Y, NAME) \
          static CGAL::Profile_branch_counter NAME(Y); ++NAME;
#  define CGAL_BRANCH_PROFILER_BRANCH(NAME) \
          NAME.increment_branch();
#else
#  define CGAL_PROFILER(Y)
#  define CGAL_HISTOGRAM_PROFILER(Y, Z)
#  define CGAL_BRANCH_PROFILER(Y, NAME)
#  define CGAL_BRANCH_PROFILER_BRANCH(NAME)
#endif

CGAL_END_NAMESPACE

#endif // CGAL_PROFILE_COUNTER_H
