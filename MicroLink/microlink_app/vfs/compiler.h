/**
 * @file    compiler.h
 * @brief   Special asserts and macros
 *
 * DAPLink Interface Firmware
 * Copyright (c) 2009-2016, ARM Limited, All Rights Reserved
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef COMPILER_H
#define COMPILER_H


#ifdef __cplusplus
extern "C" {
#endif

#define COMPILER_CONCAT_(a, b) a##b
#define COMPILER_CONCAT(a, b) COMPILER_CONCAT_(a, b)

// Divide by zero if the the expression is false.  This
// causes an error at compile time.
//
// The special value '__COUNTER__' is used to create a unique value to
// append to 'compiler_assert_' to create a unique token.  This prevents
// conflicts resulting from the same enum being declared multiple times.
#define COMPILER_ASSERT(e) 

// Macros to disable optimisation of a function.
#if (defined(__ICCARM__))
#define NO_OPTIMIZE_PRE _Pragma("optimize = none")
#define NO_OPTIMIZE_INLINE
#define NO_OPTIMIZE_POST
#elif (defined(__CC_ARM)) /* ARMCC */
#define NO_OPTIMIZE_PRE _Pragma("push") \
                        _Pragma("O0")
#define NO_OPTIMIZE_INLINE
#define NO_OPTIMIZE_POST _Pragma("pop")
#define RAM_FUNCTION __attribute__((section("ram_func")))
#elif (defined(__ARMCC_VERSION)) /* ARMCLANG */
#define NO_OPTIMIZE_PRE
#define NO_OPTIMIZE_INLINE
#define NO_OPTIMIZE_POST
#define RAM_FUNCTION __attribute__((section("ram_func")))
#elif (defined(__GNUC__))
#define NO_OPTIMIZE_PRE
#define NO_OPTIMIZE_INLINE __attribute__((optimize("O0")))
#define NO_OPTIMIZE_POST
#define RAM_FUNCTION __attribute__((long_call, section(".ram_func")))
#define __WEAK       __attribute__((weak))
#else
#error "Unknown compiler"
#endif

#ifdef __cplusplus
}
#endif

#endif
