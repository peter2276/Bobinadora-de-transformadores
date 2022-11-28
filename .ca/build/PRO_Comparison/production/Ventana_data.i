# 1 "Ventana_data.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "/Applications/microchip/mplabx/v6.00/packs/Microchip/PIC18F-K_DFP/1.5.114/xc8/pic/include/language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "Ventana_data.c" 2
# 18 "Ventana_data.c"
# 1 "./Ventana.h" 1
# 22 "./Ventana.h"
# 1 "./rtwtypes.h" 1
# 49 "./rtwtypes.h"
typedef signed char int8_T;
typedef unsigned char uint8_T;
typedef int int16_T;
typedef unsigned int uint16_T;
typedef long int32_T;
typedef unsigned long uint32_T;
typedef long long int64_T;
typedef unsigned long long uint64_T;
typedef float real32_T;
typedef double real64_T;





typedef double real_T;
typedef double time_T;
typedef unsigned char boolean_T;
typedef int int_T;
typedef unsigned int uint_T;
typedef unsigned long ulong_T;
typedef unsigned long long ulonglong_T;
typedef char char_T;
typedef unsigned char uchar_T;
typedef char_T byte_T;
# 94 "./rtwtypes.h"
typedef void * pointer_T;
# 23 "./Ventana.h" 2







typedef struct {
  real_T Filter_states[10];
  real_T Filter_denStates;
} DW;


typedef struct {



  real_T Filter_NumCoef[11];
} ConstP;


typedef struct {
  real_T Input;
} ExtU;


typedef struct {
  real_T Output;
} ExtY;


extern DW rtDW;


extern ExtU rtU;


extern ExtY rtY;


extern const ConstP rtConstP;


extern void Ventana_initialize(void);
extern void Ventana_step(void);
# 19 "Ventana_data.c" 2


const ConstP rtConstP = {



  { 0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.1 }
};
