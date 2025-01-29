/*
 *  File name: std_types.h
 *  Description: standard data types for AVR
 *  Created on: Oct 1, 2024
 *  Author: Malak Waleed
 */

#ifndef STD_TYPES_H_
#define STD_TYPES_H_

/*Boolean data type*/
typedef unsigned char boolean;

/*Boolean values*/
#define TRUE (1u)
#define FALSE (0u)

#define LOGIC_HIGH (1u)
#define LOGIC_LOW (0u)

#define NULL_PTR ((void*)0)

/*Standard data types*/
typedef unsigned char uint8; /* 0 -> 255 */
typedef signed char sint8; /* -128 -> 127 */
typedef unsigned short uint16; /* 0 -> 65535 */
typedef signed short sint16; /* -32768 -> 32767 */
typedef unsigned long uint32; /* 0 -> 4294967296 */
typedef signed long sint32; /* -2147483648 -> 2147483647 */
typedef unsigned long long uint64;
typedef signed long long sint64;
typedef float float32;
typedef double float64;

#endif /* STD_TYPES_H_ */
