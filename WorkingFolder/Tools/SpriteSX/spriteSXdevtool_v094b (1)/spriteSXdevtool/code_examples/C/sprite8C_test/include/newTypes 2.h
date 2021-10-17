#ifndef  __NEWTYPES_H__
#define  __NEWTYPES_H__


#ifndef  NULL
#define  NULL  ((void *) 0)
#endif

// boolean
#ifndef boolean
typedef enum {false = 0, true = 1} boolean;
#endif

// unsigned integer
#ifndef uint
typedef unsigned int uint;
#endif

// unsigned char
#ifndef byte
typedef unsigned char byte;
#endif


#endif