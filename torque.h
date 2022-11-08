/* 
 * File:   torque.h
 * Author: pedro
 *
 * Created on November 8, 2022, 10:25 AM
 */

#ifndef TORQUE_H
#define	TORQUE_H

#ifdef	__cplusplus
extern "C" {
#endif

uint16_t current=0;

/**
  @Summary
    Returns true when the conversion is completed otherwise false.

  @Description
    This routine is used to measure th ADC and save the result in "current"

  @Preconditions
    ADC_Initialize()
    function should have been called before calling this function.

  @Returns
    true  - If conversion is complete
    false - If conversion is not completed

  @Param
    None

  @Example
    <code>
    uint16_t convertedValue;

    ADC_Initialize();
    ADC_StartConversion();

    while(!ADC_IsConversionDone());
    convertedValue = ADC_GetConversionResult();
    </code>
 */
void medir_corriente(void);


#ifdef	__cplusplus
}
#endif

#endif	/* TORQUE_H */

