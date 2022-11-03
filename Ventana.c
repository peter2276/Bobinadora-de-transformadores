/*
 * File: Ventana.c
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

#include "Ventana.h"

/* Block signals and states (default storage) */
DW rtDW;

/* External inputs (root inport signals with default storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
ExtY rtY;

/* Model step function */
void Ventana_step(void)
{
  int16_T j;
  int32_T num;
  real_T rtb_Filter;

  /* DiscreteFilter: '<Root>/Filter' incorporates:
   *  Inport: '<Root>/Input'
   */
  num = 1L;
  rtb_Filter = 0.1 * rtU.Input;
  for (j = 0; j < 10; j++) {
    rtb_Filter += rtConstP.Filter_NumCoef[num] * rtDW.Filter_states[(int32_T)j];
    num++;
  }

  rtb_Filter -= -rtDW.Filter_denStates;
  for (j = 0; j < 9; j++) {
    rtDW.Filter_states[(int32_T)(9 - j)] = rtDW.Filter_states[(int32_T)(8 - j)];
  }

  rtDW.Filter_states[0L] = rtU.Input;
  rtDW.Filter_denStates = rtb_Filter;

  /* End of DiscreteFilter: '<Root>/Filter' */

  /* Outport: '<Root>/Output' */
  rtY.Output = rtb_Filter;
}

/* Model initialize function */
void Ventana_initialize(void)
{
  /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
