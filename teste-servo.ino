#include <Servo.h>
#define sensorLumen 8

int leitura = 0;
int current = 0;

Servo servo;

void setup()
{
  servo.attach(9, 500, 2500);
  servo.write(90); //Coloca o servo na posição inicial
  Serial.begin(9600);
}
void loop()
{
  Serial.println(leitura);
  leitura = !digitalRead(sensorLumen);
  if(leitura == 1 && current == 0)
  {
    servo.write(0);
    current = 1;
    delay(1500);
  }
  else if(leitura == 0 && current == 1)
  {
    servo.write(90);
    current = 0;
    delay(1500);
  }
}