/* 
 * CS:APP Data Lab 
 * 
 * <刘田田 25300120181>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  return 1 << 31;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
	return ~(x & y ) & ~(~x & ~y);
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  int a;
  a = x >> 31;
  return (~x + 1) & a;
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
  int a,b;
  a = ~(0xFF << (dst << 3)) & x;
  b = ( x >> (src << 3) & 0xFF ) << (dst << 3);
  return a | b;
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  int result = x >> n;
  int mask = ~(((1 << 31) >> n) << 1);
  return result & mask;
}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
  int a = 0x0f | (0x0f << 8);
  a = a | ( a << 16 );
  int b = a << 4;
  return ((x & a) << 4) | (((x & b) >> 4)& a);
} 

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
  int y = ~x;
  int y1 = y & (y + ~0);
  return y1 & (~y1 + 1);
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
  x=(x >> 16)^x;
  x=(x >> 8)^x;
  x=(x >> 4)^x;
  x=(x >> 2)^x;
  x=(x >> 1)^x;
  return (x&1) ^ 1;
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
  int k = 32 + ~n;
  int shift_left = k + 1;
  int mask = (~(~0 << k) << 1) + 1;
  return (x << shift_left) | ((x >> n) & mask);
}
// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
  int half = (1 << ( n + ~0)) + ~0;
  int lsb = (x >> n) & 1;
  return ((x + half + lsb) >> n ) << n;
}

// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
  int xor_xy = x ^ y;
    int floor_mid = (x & y) + (xor_xy >> 1);
    int odd = xor_xy & 1;
    int sign_xor = xor_xy >> 31;
    int not_x = ~x;
    int diff = y + (not_x + 1);
    int same_gt = (diff >> 31) & 1;
    int diff_gt = (not_x >> 31) & 1;
    int x_gt = (sign_xor & diff_gt) | (~sign_xor & same_gt);
    return floor_mid + (odd & x_gt);
}


// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
 int sx = (x >> 31) & 1;
    int sa = (a >> 31) & 1;
    int sb = (b >> 31) & 1;

    int same_a = !(sx ^ sa);
    int t_a = ((x + (~a + 1)) >> 31) & 1;
    int lt_a = (same_a & t_a) | (!same_a & sx);

    int same_b = !(sx ^ sb);
    int t_b = ((x + (~b + 1)) >> 31) & 1;
    int lt_b = (same_b & t_b) | (!same_b & sx);

    return (lt_a ^ lt_b) | !(x ^ a) | !(x ^ b);
}

// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
  int result;
  int x2 = x << 1;
  int x4 = x2 << 1;
  result = x4 + x;
  int x_sign = (x >> 31) & 1;
  int x2_sign = (x2 >> 31) & 1;
  int x4_sign = (x4 >> 31) & 1;
  int r_sign = (result >> 31) & 1;

  int overflow1 = x_sign ^ x2_sign;
  int overflow2 = !overflow1 & (x2_sign ^ x4_sign);
  int shift_overflow = overflow1 | overflow2;
  int add_overflow = !shift_overflow & (!(x_sign ^ x4_sign)) & (x_sign ^ r_sign);
  int total_overflow = shift_overflow | add_overflow;

  int pos_overflow = !x_sign & total_overflow;
  int neg_overflow = x_sign & total_overflow;

  int mask_pos = ~pos_overflow + 1;
  int mask_neg = ~neg_overflow + 1;
  int mask_normal = ~(mask_pos | mask_neg);

  int a = ~(1 << 31);
  int b = 1 << 31;

  return (mask_pos & a) | (mask_neg & b) | (mask_normal & result);
}

// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
  int temp = x+y;
  int sum = temp +z;
  int sign_x = (x >> 31) & 1;
  int sign_y = (y >> 31) & 1;
  int sign_temp = (temp >> 31) & 1;
  int sign_sum = (sum >> 31) & 1;
  int sign_z = (z >> 31) & 1;
  int overflow_1 = (~(sign_x^ sign_y)) & (sign_x ^ sign_temp);
  int overflow_2 = (~(sign_temp^ sign_z)) & (sign_sum ^ sign_temp);
  int p1 = overflow_1 & sign_temp;
  int n1 = overflow_1 & (~sign_temp);
  int p2 = overflow_2 & sign_sum;
  int n2 = overflow_2 & (~sign_sum);
  int final_p = (p1 & !n2) | (p2 & !n1);
  int final_n = (n1 & !p2) | (n2 & !p1);
  return (!!final_p) | ((!final_n) + (~0));
}

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {
  int sign = uf & 0x80000000;
    int exp = (uf >> 23) & 0xff;
    int frac = uf & 0x7fffff;
    int mantisa, new_exp = exp, new_frac;
    int P, rshift, low, high, half;

    if (exp == 0xff) {
        return uf;
    }

    if (exp == 0) {
        mantisa = frac;
    } else {
        mantisa = (1 << 23) | frac;
    }

    P = mantisa * 3;

    if (exp == 0) {
        rshift = 1;
        new_exp = 0;
    } else {
        if (P >= (1 << 25)) {
            rshift = 2;
            new_exp = exp + 1;
        } else {
            rshift = 1;
            new_exp = exp;
        }
    }

    low = P & ((1 << rshift) - 1);
    high = P >> rshift;
    half = 1 << (rshift - 1);

    if (low > half) {
        high += 1;
    } else if (low == half) {
        if (high & 1) {
            high += 1;
        }
    }

    if (exp == 0) {
        if (high >= (1 << 23)) {
            new_exp = 1;
            new_frac = high & 0x7fffff;
        } else {
            new_frac = high;
        }
    } else {
        if (high >= (1 << 24)) {
            new_exp += 1;
            new_frac = (high >> 1) & 0x7fffff;
        } else {
            new_frac = high & 0x7fffff;
        }
    }

    if (new_exp >= 0xff) {
        return sign | 0x7f800000;
    }

    return sign | (new_exp << 23) | new_frac;
}
 
// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
    int sign = uf & (1 << 31);
    int exp = (uf >> 23) & 0xff;
    int frac = uf & ((1 << 23) - 1);
    int E = exp - 127;

    if (exp == 0xff) return uf;
    if (E < -1) return sign;
    if (E == -1) {
        if (frac == 0) return sign;
        return sign | (0x7f << 23);
    }
    if (E >= 23) return uf;

    int mant = (1 << 23) | frac;
    int fbits = 23 - E;
    int num = mant >> fbits;
    int fpart = mant & ((1 << fbits) - 1);
    int half = 1 << (fbits - 1);

    if (fpart > half) {
        num++;
    } else if (fpart == half) {
        if (num & 1) num++;
    }

    int tmp = num, s = 0;
    while (tmp >>= 1) s++;
    return sign | ((s + 127) << 23) | ((num << (23 - s)) & ((1 << 23) - 1));
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
  if (x == 0){
    return 0;
  }
  int sign = ( x < 0 ) ? (1 << 31) : 0;
  int abs_x = ( x < 0 ) ? -x : x;
  int shift = 0;
  while ((abs_x & ( 1 << 31 )) == 0 ){
    abs_x <<= 1;
    shift++;
  }
  int exp = 158 - shift;
  int frac = (abs_x >> 8)& ((1 << 23) - 1);
  int round_bit = (abs_x >> 7) & 1;
  int sticky_bit = (abs_x & 0x7f) != 0;
  if(round_bit && (sticky_bit || (frac & 1))){
    frac++;
    if(frac == (1 << 23)){
      frac = 0;
      exp++;
    }
  }
return sign | (exp << 23) | frac;
}


// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
  int a = 0x55 | (0x55 << 8);
    a = a | (a << 16);
    int b = 0x33 | (0x33 << 8);
    b = b | (b << 16);
    int c = 0x0f | (0x0f << 8);
    c = c | (c << 16);
    int d = 0xff | (0xff << 16);
    
    x = (x & a) + ((x >> 1) & a);
    x = (x & b) + ((x >> 2) & b);
    x = (x & c) + ((x >> 4) & c);
    x = (x & d) + ((x >> 8) & d);
    x = x + (x >> 16);
    return x & 0x3f;
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x){
  int a = 0x55 | (0x55 << 8);
    a = a | (a << 16);
    int b = 0x33 | (0x33 << 8);
    b = b | (b << 16);
    int c = 0x0f | (0x0f << 8);
    c = c | (c << 16);
    int d = 0xff | (0xff << 16);
    int e = 0xff | (0xff << 8);
    
    x = ((x & a) << 1) | ((x >> 1) & a);
    x = ((x & b) << 2) | ((x >> 2) & b);
    x = ((x & c) << 4) | ((x >> 4) & c);
    x = ((x & d) << 8) | ((x >> 8) & d);
    x = (x << 16) | ((x >> 16) & e);
    return x;
}