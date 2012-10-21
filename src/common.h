/*******************************************************************************
# Copyright (c) 2011 Christopher James Huff
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#******************************************************************************/

#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_conf.h"
#include "compiler_support.h"


// Place variable in one of the RAM blocks accessible via the AHB bus
#define SRAM_112K  __attribute__ ((section(".sram112k")))
#define SRAM_16K  __attribute__ ((section(".sram16k")))

#define CORE_M0  (0)
#define CORE_M3  (30)
#define CORE_M4  (40)


#define MIN(x, y) (((x) < (y))? (x) : (y))
#define MAX(x, y) (((x) > (y))? (x) : (y))

static inline int32_t imin(int32_t x, int32_t y) {return MIN(x, y);}
static inline int32_t imax(int32_t x, int32_t y) {return MAX(x, y);}
static inline int32_t imins(int16_t x, int16_t y) {return MIN(x, y);}
static inline int32_t imaxs(int16_t x, int16_t y) {return MAX(x, y);}


#ifndef WEAK
#define WEAK __attribute__ ((weak))
#endif

#ifndef ALIAS
#define ALIAS(nm) __attribute__ ((weak, alias (#nm)))
#endif

#ifndef PACKED
#define PACKED  __attribute__((packed))
#endif

#define __ALIGN_4 __attribute__ ((aligned (4)))


#endif // COMMON_H
