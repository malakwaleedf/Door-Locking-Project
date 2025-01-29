/*
 *  File name: common_macros.h
 *  Description: common used macros
 *  Created on: Oct 1, 2024
 *  Author: Malak Waleed
 */

#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

#define REG_SIZE 8
/*sets a certain bit in a register*/
#define SET_BIT(REG,BIT) (REG |= (1<<BIT))

/*clears a certain bit in a register*/
#define CLEAR_BIT(REG,BIT) (REG &= ~(1<<BIT))

/*toggles a certain bit in a register*/
#define TOGGLE_BIT(REG,BIT) (REG ^= (1<<BIT))

/*checks if a bit is set in a register*/
#define BIT_IS_SET(REG,BIT) (REG & (1<<BIT))

/*checks if a bit is clear in a register*/
#define BIT_IS_CLEAR(REG,BIT) (!(REG & (1<<BIT)))

/*rotates a register a number of bits to the right*/
#define ROR(REG,BIT) (REG = (REG >> BIT) | (REG << (REG_SIZE - BIT)))

/*rotates a register a number of bits to the left*/
#define ROL(REG,BIT) (REG = (REG << BIT) | (REG >> (REG_SIZE - BIT)))

/*gets the value of a certain bit*/
#define GET_BIT(REG,BIT) ((REG & (1<<BIT)) >> BIT)


#endif /* COMMON_MACROS_H_ */
