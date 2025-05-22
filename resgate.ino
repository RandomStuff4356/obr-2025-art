#include <QTRSensors.h>
int valorBranco = 500;
QTRSensors qtr;
 
const uint8_t SensorCount = 8;
uint16_t sensorValues[SensorCount];
void setup()
{
  // configure the sensors
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3, A4, A5, A6, A7}, SensorCount);
  qtr.setEmitterPin(2);
  delay(500);
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH); // turn on Arduino's LED to indicate we are in calibration mode
  // analogRead() takes about 0.1 ms on an AVR.
  // 0.1 ms per sensor * 4 samples per sensor read (default) * 6 sensors
  // * 10 reads per calibrate() call = ~24 ms per calibrate() call.
  // Call calibrate() 400 times to make calibration take about 10 seconds.
  for (uint16_t i = 0; i < 300; i++)
  {
    qtr.calibrate();
  }
  digitalWrite(7, LOW); // turn off Arduino's LED to indicate we are through with calibration
  // print the calibration minimum values measured when emitters were on
  Serial.begin(9600);
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(qtr.calibrationOn.minimum[i]);
    Serial.print(' ');
  }
  Serial.println();
  // print the calibration maximum values measured when emitters were on
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(qtr.calibrationOn.maximum[i]);
    Serial.print(' ');
  }
  Serial.println();
  Serial.println();
  delay(1000);
}
void loop()
{
  uint16_t position = qtr.readLineBlack(sensorValues);
  for (uint8_t i = 0; i < SensorCount; i++)
    {
      Serial.print(sensorValues[i]);
      Serial.print('\t');
    }
  Serial.println(position);
// D1 = A7, D2 é A6 e assim por diante...
}
