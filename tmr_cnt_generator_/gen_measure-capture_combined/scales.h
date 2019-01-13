#ifndef SCALES_H_
#define SCALES_H_

#ifdef PRESCALER_0
#define PRE_BIT_0 0
#define PRE_BIT_0 0
#define PRE_BIT_0 0
#endif

#ifdef PRESCALER_1
#define PRE_BIT_0 1
#define PRE_BIT_1 0
#define PRE_BIT_2 0
#endif

#ifdef PRESCALER_8
#define PRE_BIT_0 0
#define PRE_BIT_1 1
#define PRE_BIT_2 0
#endif


#ifdef PRESCALER_32
#define PRE_BIT_0 1
#define PRE_BIT_1 1
#define PRE_BIT_2 0
#endif

#ifdef PRESCALER_64
#define PRE_BIT_0 0
#define PRE_BIT_1 0
#define PRE_BIT_2 1
#endif

#ifdef PRESCALER_128
#define PRE_BIT_0 1
#define PRE_BIT_1 0
#define PRE_BIT_2 1
#endif

#ifdef PRESCALER_256
#define PRE_BIT_0 0
#define PRE_BIT_1 1
#define PRE_BIT_2 1
#endif

#ifdef PRESCALER_1024
#define PRE_BIT_0 1
#define PRE_BIT_1 1
#define PRE_BIT_2 1
#endif



#endif /* SCALES_H_ */