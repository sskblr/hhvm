/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010-2016 Facebook, Inc. (http://www.facebook.com)     |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
*/

#ifndef incl_HPHP_UTIL_UNWIND_ITANIUM_H_
#define incl_HPHP_UTIL_UNWIND_ITANIUM_H_

#include <cstdint>
#include <exception>
#include <typeinfo>

#ifndef _MSC_VER
#include <unwind.h>
#else
#include "hphp/util/unwind-itanium-msvc.h"
#endif

namespace HPHP {

///////////////////////////////////////////////////////////////////////////////
/*
 * Exception handling helpers for libsupc++ unwinding internals.
 *
 * These make use of data structures that do not appear to be defined in the
 * Itanium C++ exception handling ABI, but nonetheless seem to be shared
 * between at least g++ and clang across multiple platforms.
 *
 * See libstdc++-v3/libsupc++/unwind-cxx.h in libgcc.
 */

namespace detail {

/*
 * Mirrors __cxxabiv1::__is_dependent_exception().
 */
inline bool is_dependent_exception(uint64_t c) {
  return (c & 1);
}

}

/*
 * Like __cxxabiv1::__get_object_from_ue(), but with a specific return type.
 */
inline std::exception*
exceptionFromUE(_Unwind_Exception* eo) {
  constexpr size_t sizeOfDependentException = 112;

  if (detail::is_dependent_exception(eo->exception_class)) {
    return *reinterpret_cast<std::exception**>(
      reinterpret_cast<char*>(eo + 1) - sizeOfDependentException);
  }
  return reinterpret_cast<std::exception*>(eo + 1);
}

/*
 * Like __cxxabiv1::__get{_refcounted_,}_exception_header_from_{obj,ue}(), but
 * extracts the type_info* member.
 */
inline const std::type_info&
typeinfoFromUE(_Unwind_Exception* eo) {
  if (detail::is_dependent_exception(eo->exception_class)) {
    // like __cxxabiv1::__get_refcounted_exception_header_from_obj()
    constexpr size_t sizeOfRefcountedException = 128;
    auto obj = reinterpret_cast<char*>(exceptionFromUE(eo));
    auto header = obj - sizeOfRefcountedException;

    // Dereference the exc field; the type_info* is the first field inside that.
    constexpr size_t excOffset = 16;
    return *reinterpret_cast<std::type_info*>(header + excOffset);
  }

  // like __cxxabiv1::__get_exception_header_from_ue()
  constexpr size_t sizeOfCxaException = 112;
  return **reinterpret_cast<std::type_info**>(
    reinterpret_cast<char*>(eo + 1) - sizeOfCxaException);
}

///////////////////////////////////////////////////////////////////////////////

}

#endif
