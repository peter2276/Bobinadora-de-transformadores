/*
 * File: Ventana.h
 *
 * Code generated for Simulink model 'Ventana'.
 *
 * Model version                  : 1.1
 * Simulink Coder version         : 9.3 (R2020a) 18-Nov-2019
 * C/C++ source code generated on : Wed Oct  5 16:39:16 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Microchip->PIC18
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Ventana_h_
#define RTW_HEADER_Ventana_h_
#ifndef Ventana_COMMON_INCLUDES_
# define Ventana_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* Ventana_COMMON_INCLUDES_ */

/* Model Code Variants */

/* Macros for accessing real-time model data structure */

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T Filter_states[10];            /* '<Root>/Filter' */
  real_T Filter_denStates;             /* '<Root>/Filter' */
} DW;

/* Constant parameters (default storage) */
typedef struct {
  /* Expression: [0.100000000000000006 0 0 0 0 0 0 0 0 0 -0.100000000000000006]
   * Referenced by: '<Root>/Filter'
   */
  real_T Filter_NumCoef[11];
} ConstP;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T Input;                        /* '<Root>/Input' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T Output;                       /* '<Root>/Output' */
} ExtY;

/* Block signals and states (default storage) */
extern DW rtDW;

/* External inputs (root inport signals with default storage) */
extern ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY rtY;

/* Constant parameters (default storage) */
extern const ConstP rtConstP;

/* Model entry point functions */
extern void Ventana_initialize(void);
extern void Ventana_step(void);

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Ventana'
 */
#endif                                 /* RTW_HEADER_Ventana_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
