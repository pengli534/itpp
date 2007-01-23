/*!
 * \file
 * \brief Machine dependent formats for binary storage
 * \author Tobias Ringstrom and Adam Piatyszek
 * 
 * $Date$
 * $Revision$
 *
 * -------------------------------------------------------------------------
 *
 * IT++ - C++ library of mathematical, signal processing, speech processing,
 *        and communications classes and functions
 *
 * Copyright (C) 1995-2007  (see AUTHORS file for a list of contributors)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 *
 * -------------------------------------------------------------------------
 */

#ifndef MACHDEP_H
#define MACHDEP_H


namespace itpp {

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#define REV_2(from, to)                                   \
              ((char *)(to))[0] = ((char *)(from))[1];    \
              ((char *)(to))[1] = ((char *)(from))[0];

#define REV_4(from, to)                                   \
              ((char *)(to))[0] = ((char *)(from))[3];    \
              ((char *)(to))[1] = ((char *)(from))[2];    \
              ((char *)(to))[2] = ((char *)(from))[1];    \
              ((char *)(to))[3] = ((char *)(from))[0];

#define REV_8(from, to)                                   \
              ((char *)(to))[0] = ((char *)(from))[7];    \
              ((char *)(to))[1] = ((char *)(from))[6];    \
              ((char *)(to))[2] = ((char *)(from))[5];    \
              ((char *)(to))[3] = ((char *)(from))[4];    \
              ((char *)(to))[4] = ((char *)(from))[3];    \
              ((char *)(to))[5] = ((char *)(from))[2];    \
              ((char *)(to))[6] = ((char *)(from))[1];    \
              ((char *)(to))[7] = ((char *)(from))[0];


  //Typedefs for 32 bit architechures (default)
  typedef signed char        it_s8;
  typedef unsigned char      it_u8;
  typedef signed short       it_s16;
  typedef unsigned short     it_u16;
  typedef signed int         it_s32;
  typedef unsigned int       it_u32;
  typedef float              it_f32;
  typedef double             it_f64;

  //One byte data types are independent of endianity:
  inline it_s8 big_endian(it_s8 x)              { return x; }
  inline it_u8 big_endian(it_u8 x)              { return x; }
  inline it_s8 little_endian(it_s8 x)           { return x; }
  inline it_u8 little_endian(it_u8 x)           { return x; }
  inline void  big_endian(it_s8 x, it_s8 &y)    { y = x; }
  inline void  big_endian(it_u8 x, it_u8 &y)    { y = x; }
  inline void  little_endian(it_s8 x, it_s8 &y) { y = x; }
  inline void  little_endian(it_u8 x, it_u8 &y) { y = x; }

  /*
   * Big endian: _AIX, AIX, sparc, __sparc__, __mc68000__, __m68k__, MIPSEB,
   * __MIPSEB__, __ARMEB, HPPA, __hppa__, PPC, __ppc_, __PPC__, __powerpc__.
   * 
   * Little endian: i386, __i386__, __x86_64__, __amd64__, __sh__, __vax__
   * (yes, really!), MIPSEL, __MIPSEL__, and __ARMEL__, __alpha, __alpha__,
   * __ia64__.
   *
   * It seems that ppc, hppa, ia64, alpha, sparc, mips, arm and superh have
   * both big and little endian modes.
   */
#if defined(_AIX) || defined(AIX)					\
  || defined(sparc) || defined(__sparc__)				\
  || defined(__mc68000__) || defined(__mk68k__)				\
  || defined(MIPSEB) || defined(__MIPSEB__)				\
  || defined(__ARMEB)							\
  || defined(HPPA) || defined(__hppa__)					\
  || defined(PPC) || defined(__ppc__) || defined(__PPC__)		\
  || defined(__powerpc__)						\
  || defined(__s390__) || defined(__s390x__)
#  define __BIG_ENDIAN__
#elif defined(i386) || defined(__i386__)       \
  || defined(__x86_64__) || defined(__amd64__) \
  || defined(MIPSEL) || defined(__MIPSEL__)    \
  || defined(__alpha) || defined(__alpha__)
#  define __LITTLE_ENDIAN__
#endif


#if defined(__BIG_ENDIAN__)

  //------------------------------------------------------
  // Big Endian
  //------------------------------------------------------

#define IT_ENDIANITY 4321

  inline it_s16 big_endian(it_s16 x) { return x; }
  inline it_u16 big_endian(it_u16 x) { return x; }
  inline it_s32 big_endian(it_s32 x) { return x; }
  inline it_u32 big_endian(it_u32 x) { return x; }
  inline it_f32 big_endian(it_f32 x) { return x; }
  inline it_f64 big_endian(it_f64 x) { return x; }

  inline it_s16 little_endian(it_s16 x) { it_s16 y; REV_2(&x,&y); return y; }
  inline it_u16 little_endian(it_u16 x) { it_u16 y; REV_2(&x,&y); return y; }
  inline it_s32 little_endian(it_s32 x) { it_s32 y; REV_4(&x,&y); return y; }
  inline it_u32 little_endian(it_u32 x) { it_u32 y; REV_4(&x,&y); return y; }
  inline it_f32 little_endian(it_f32 x) { it_f32 y; REV_4(&x,&y); return y; }
  inline it_f64 little_endian(it_f64 x) { it_f64 y; REV_8(&x,&y); return y; }

  inline void big_endian(it_s16 x, it_s16 &y) { y = x; }
  inline void big_endian(it_u16 x, it_u16 &y) { y = x; }
  inline void big_endian(it_s32 x, it_s32 &y) { y = x; }
  inline void big_endian(it_u32 x, it_u32 &y) { y = x; }
  inline void big_endian(it_f32 x, it_f32 &y) { y = x; }
  inline void big_endian(it_f64 x, it_f64 &y) { y = x; }

  inline void little_endian(it_s16 x, it_s16 &y) { REV_2(&x,&y); }
  inline void little_endian(it_u16 x, it_u16 &y) { REV_2(&x,&y); }
  inline void little_endian(it_s32 x, it_s32 &y) { REV_4(&x,&y); }
  inline void little_endian(it_u32 x, it_u32 &y) { REV_4(&x,&y); }
  inline void little_endian(it_f32 x, it_f32 &y) { REV_4(&x,&y); }
  inline void little_endian(it_f64 x, it_f64 &y) { REV_8(&x,&y); }

  //Additions for some 64 bit architechtures
// #if defined(sparc)
//   typedef signed long        it_s64;
//   typedef unsigned long      it_u64;
//   inline it_s64 big_endian(it_s64 x) { return x; }
//   inline it_u64 big_endian(it_u64 x) { return x; }
//   inline it_s64 little_endian(it_s64 x) { it_s64 y; REV_4(&x,&y); return y; }
//   inline it_u64 little_endian(it_u64 x) { it_u64 y; REV_4(&x,&y); return y; }
//   inline void big_endian(it_s64 x, it_s64 &y) { y = x; }
//   inline void big_endian(it_u64 x, it_u64 &y) { y = x; }
//   inline void little_endian(it_s64 x, it_s64 &y) { REV_4(&x,&y); }
//   inline void little_endian(it_u64 x, it_u64 &y) { REV_4(&x,&y); }
// #endif

#elif defined(__LITTLE_ENDIAN__)

  //------------------------------------------------------
  // Little Endian
  //------------------------------------------------------

#define IT_ENDIANITY 1234

  //32 bit architechures (default)
  inline it_s16 big_endian(it_s16 x) { it_s16 y; REV_2(&x,&y); return y; }
  inline it_u16 big_endian(it_u16 x) { it_u16 y; REV_2(&x,&y); return y; }
  inline it_s32 big_endian(it_s32 x) { it_s32 y; REV_4(&x,&y); return y; }
  inline it_u32 big_endian(it_u32 x) { it_u32 y; REV_4(&x,&y); return y; }
  inline it_f32 big_endian(it_f32 x) { it_f32 y; REV_4(&x,&y); return y; }
  inline it_f64 big_endian(it_f64 x) { it_f64 y; REV_8(&x,&y); return y; }

  inline it_s16 little_endian(it_s16 x) { return x; }
  inline it_u16 little_endian(it_u16 x) { return x; }
  inline it_s32 little_endian(it_s32 x) { return x; }
  inline it_u32 little_endian(it_u32 x) { return x; }
  inline it_f32 little_endian(it_f32 x) { return x; }
  inline it_f64 little_endian(it_f64 x) { return x; }

  inline void big_endian(it_s16 x, it_s16 &y) { REV_2(&x,&y); }
  inline void big_endian(it_u16 x, it_u16 &y) { REV_2(&x,&y); }
  inline void big_endian(it_s32 x, it_s32 &y) { REV_4(&x,&y); }
  inline void big_endian(it_u32 x, it_u32 &y) { REV_4(&x,&y); }
  inline void big_endian(it_f32 x, it_f32 &y) { REV_4(&x,&y); }
  inline void big_endian(it_f64 x, it_f64 &y) { REV_8(&x,&y); }

  inline void little_endian(it_s16 x, it_s16 &y) { y = x; }
  inline void little_endian(it_u16 x, it_u16 &y) { y = x; }
  inline void little_endian(it_s32 x, it_s32 &y) { y = x; }
  inline void little_endian(it_u32 x, it_u32 &y) { y = x; }
  inline void little_endian(it_f32 x, it_f32 &y) { y = x; }
  inline void little_endian(it_f64 x, it_f64 &y) { y = x; }

  //Additions for some 64 bit architechtures
// #if defined(alpha) || defined(__x86_64__) || defined(__s390x__)
//   typedef signed long        it_s64;
//   typedef unsigned long      it_u64;
//   inline it_s64 big_endian(it_s64 x) { it_s64 y; REV_4(&x,&y); return y; }
//   inline it_u64 big_endian(it_u64 x) { it_u64 y; REV_4(&x,&y); return y; }
//   inline it_s64 little_endian(it_s64 x) { return x; }
//   inline it_u64 little_endian(it_u64 x) { return x; }
//   inline void big_endian(it_s64 x, it_s64 &y) { REV_4(&x,&y); }
//   inline void big_endian(it_u64 x, it_u64 &y) { REV_4(&x,&y); }
//   inline void little_endian(it_s64 x, it_s64 &y) { y = x; }
//   inline void little_endian(it_u64 x, it_u64 &y) { y = x; }
// #endif

#else

#error "Could not determine endianity!!!"

#endif 

#undef REV_2
#undef REV_4
#undef REV_8

#endif //DOXYGEN_SHOULD_SKIP_THIS

} // namespace itpp

#endif // #ifndef MACHDEP_H

