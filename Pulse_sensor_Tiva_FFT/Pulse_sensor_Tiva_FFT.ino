#include "fix_fft.c"
 
#define log2N     7
#define N         128     //number of sample points
 
 
void setup()
{
  Serial.begin(115200);
  delay(1000);             //give time for serial monitor to start up in Energia
  
  
}
 
short real[N];
short imag[N];
short i;
 
void loop()
{
  
  for (i=0; i<N; i++) {            // read ADC pin 128 times at roughly 1KHz
    real[i] = analogRead(29);
    delay(1);
  }
  
  for( i=0; i<N; i++) imag[i] = 0;   // clear imag array
  
  fix_fft(real, imag, log2N, 0);   // perform fft on sampled points in real[i]
  
  for ( i = 0; i < N/2; i++)         //get the power magnitude in each bin
    {
      real[i] =sqrt((long)real[i] * (long)real[i] + (long)imag[i] * (long)imag[i]);    
    }
  
  Serial.print("*\n");      //send fft results over serial to PC
  for (i=0; i<N/2; i++) {
    Serial.print(real[i]);
    Serial.print("\n");
  }
  
  
}
