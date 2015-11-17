#ifndef TYPES_H
#define TYPES_H

#if defined __x86_64__ && !defined __ILP32__
# define __WORDSIZE     64
#else
# define __WORDSIZE     32
#endif

typedef signed char             int8_t;
typedef short int               int16_t;
typedef int                     int32_t;

typedef unsigned char           uint8_t;
typedef unsigned short int      uint16_t;
typedef unsigned int            uint32_t;

# if __WORDSIZE == 64
typedef long int                int64_t;
# else
__extension__
typedef long long int           int64_t;
# endif

#if __WORDSIZE == 64
typedef unsigned long int       uint64_t;
#else
__extension__
typedef unsigned long long int  uint64_t;
#endif

typedef enum
{
    false = ( 1 == 0 ),
    true = (!false)
} bool;


#endif 
