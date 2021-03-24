/*
  Example of use of the FFT libray
        Copyright (C) 2014 Enrique Condes
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
  In this example, the Arduino simulates the sampling of a sinusoidal 1000 Hz
  signal with an amplitude of 100, sampled at 5000 Hz. Samples are stored
  inside the vReal array. The samples are windowed according to Hamming
  function. The FFT is computed using the windowed samples. Then the magnitudes
  of each of the frequencies that compose the signal are calculated. Finally,
  the frequency with the highest peak is obtained, being that the main frequency
  present in the signal.
*/

#include "arduinoFFT.h"

arduinoFFT FFT = arduinoFFT(); /* Create FFT object */
/*
These values can be changed in order to evaluate the functions
*/
const uint16_t samples = 2048; //This value MUST ALWAYS be a power of 2
double samplingFrequency = 40000;
uint32_t targetMicrosDelay = 1000000 / samplingFrequency;
/*
These are the input and output vectors
Input vectors receive computed results from FFT
*/
double vReal[samples];
double vImag[samples];

uint8_t dc_offset;
double max_t = 0;

#define SCL_INDEX 0x00
#define SCL_TIME 0x01
#define SCL_FREQUENCY 0x02
#define SCL_PLOT 0x03

void setup()
{
  Serial.begin(2000000);
  while(!Serial);
  Serial.println("Ready");
  analogReadResolution(8);
  delay(50);
  dc_offset = analogRead(0);
  
}

void loop()
{
  /* Build raw data */
  uint32_t x = micros();
  //unsigned long last = micros();
  for (uint16_t i = 0; i < samples; i++)
  {
    //while((micros() - last) < targetMicrosDelay);
    vReal[i] = (analogRead(0) - dc_offset) / 2;
    //last = micros();
    vImag[i] = 0.0;
  }
  uint32_t elapsed_t = micros() - x;
  samplingFrequency = samples / ((micros() - x) / 1000000.0);

  FFT.Windowing(vReal, samples, FFT_WIN_TYP_HAMMING, FFT_FORWARD);  /* Weigh data */
  FFT.Compute(vReal, vImag, samples, FFT_FORWARD); /* Compute FFT */
  FFT.ComplexToMagnitude(vReal, vImag, samples); /* Compute magnitudes */

  for (int i = 0; i < samples / 2; i++) vReal[i] = constrain(vReal[i], 0, 400);
  for (int i = 0; i < samples / 2; i++) if (vReal[i] > max_t) max_t = vReal[i];
  for (int i = 0; i < samples / 2; i++) vReal[i] /= (max_t / 5);
  

  Serial.println(samplingFrequency);
  //Serial.println(max_t);
  //Serial.println("Computed magnitudes:");
  //PrintVector(vReal, (samples >> 3));
  //Serial.println(millis());
  //double y = FFT.MajorPeak(vReal, samples, samplingFrequency);
  //Serial.println(y, 6);
}

void PrintVector(double *vData, uint16_t bufferSize)
{
  for (uint16_t i = 1; i < bufferSize; i++)
  {
    //double abscissa = ((i * 1.0 * samplingFrequency) / samples);
    //Serial.print(abscissa, 6);
    //Serial.print("Hz");
    //Serial.print(" ");
    Serial.println(vData[i], 4);
  }
  Serial.println();
}
