
#ifndef MACROS_H_
#define MACROS_H_

#define bitset(reg,bit)   ((reg) |=  (1<<(bit)))
#define bitclear(reg,bit) ((reg) &= ~(1<<(bit)))
#define bitflip(reg,bit)  ((reg) ^=  (1<<(bit)))
#define Git_bit(reg,bit) ((reg) &   (1<<(bit))) >> bit

#endif /* MACROS_H_ */
