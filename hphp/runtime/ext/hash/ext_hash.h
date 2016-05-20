/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010-2016 Facebook, Inc. (http://www.facebook.com)     |
   | Copyright (c) 1997-2010 The PHP Group                                |
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

#ifndef incl_HPHP_EXT_HASH_H_
#define incl_HPHP_EXT_HASH_H_

#include "hphp/runtime/ext/extension.h"

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

constexpr int64_t k_HASH_HMAC = 1;

Variant HHVM_FUNCTION(hash, const String& algo, const String& data,
                            bool raw_output = false);
Array HHVM_FUNCTION(hash_algos);
Variant HHVM_FUNCTION(hash_init, const String& algo, int64_t options = 0,
                                 const String& key = null_string);
Variant HHVM_FUNCTION(hash_file, const String& algo, const String& filename,
                                 bool raw_output = false);
Variant HHVM_FUNCTION(hash_final, const Resource& context,
                                  bool raw_output = false);
bool HHVM_FUNCTION(hash_update, const Resource& context, const String& data);
Variant HHVM_FUNCTION(hash_copy, const Resource& context);
bool HHVM_FUNCTION(hash_equals, const Variant& known, const Variant& user);
int64_t HHVM_FUNCTION(furchash_hphp_ext, const String& key,
                                         int64_t len, int64_t nPart);
int64_t HHVM_FUNCTION(hphp_murmurhash, const String& key,
                                       int64_t len, int64_t seed);

///////////////////////////////////////////////////////////////////////////////
}

#endif // incl_HPHP_EXT_HASH_H_
