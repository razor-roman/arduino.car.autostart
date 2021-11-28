#include <math.h> // библиотека для выполнения простых математических операций
const int potPin = PA0;
/* USER CODE BEGIN PV */
/* adc vars */
uint16_t ADC_Raw[1];
/* ntc vars */
float Ntc_Tmp = 0;
uint16_t Ntc_R;
/* sheduler vars */
uint8_t Sch_100ms = 255;

/* R1 resistance */
#define NTC_UP_R 10000.0f
/* constants of Steinhart-Hart equation */
#define A 0.001111f
#define B 0.000237987f
#define C 0.000000065f
/* USER CODE END PV */
#define SERIESRESISTOR 10000 
double Thermister() 
{
  float Temp;
  Ntc_R = ((NTC_UP_R)/((4095.0/analogRead(potPin)) - 1));
  /* temp */
  float Ntc_Ln = log(Ntc_R);
  /* calc. temperature */
  Ntc_Tmp = (1.0/(A + B*Ntc_Ln + C*Ntc_Ln*Ntc_Ln*Ntc_Ln)) - 273.15;
  return Ntc_Tmp;
}
