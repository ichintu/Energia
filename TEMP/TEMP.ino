/* Read internal temperature sensor of LM4F120 
 Stellaris Launchpad
 Example from TI LM4F120 workbook
 A la mode Energia
 */

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/sysctl.h"
#include "driverlib/adc.h"
#include "Energia.h"

unsigned long ulADC0Value[4];
volatile unsigned long ulTempAvg;
volatile unsigned long ulTempValueC;
volatile unsigned long ulTempValueF;

void  setup()
{
  Serial.begin(9600);

  SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
  SysCtlADCSpeedSet(SYSCTL_ADCSPEED_125KSPS); // 250
  ADCSequenceDisable(ADC0_BASE, 1);
  ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR, 0);
  ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_TS);
  ADCSequenceStepConfigure(ADC0_BASE, 1, 1, ADC_CTL_TS);
  ADCSequenceStepConfigure(ADC0_BASE, 1, 2, ADC_CTL_TS);
  ADCSequenceStepConfigure(ADC0_BASE, 1, 3, ADC_CTL_TS | ADC_CTL_IE | ADC_CTL_END);
  ADCSequenceEnable(ADC0_BASE, 1);
}
void loop()
{  
  ADCIntClear(ADC0_BASE, 1);
  ADCProcessorTrigger(ADC0_BASE, 1);
  
  while(!ADCIntStatus(ADC0_BASE, 1, false))
  {    
  }

  ADCSequenceDataGet(ADC0_BASE, 1, ulADC0Value);
  ulTempAvg = (ulADC0Value[0] + ulADC0Value[1] + ulADC0Value[2] + ulADC0Value[3] + 2)/4;
  ulTempValueC = (1475 - ((2475 * ulTempAvg)) / 4096)/10;
  ulTempValueF = ((ulTempValueC * 9) + 160) / 5;
  Serial.println(ulTempValueC);
  delay(300);
}
