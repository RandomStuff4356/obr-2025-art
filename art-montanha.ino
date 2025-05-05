#include <Servo.h>

String status;

Servo servo;
void setup()
{
    servo.attach(9, 500, 2500);
    servo.write(90); //Coloca o servo na posição inicial
    Serial.begin(9600);
}
void loop()
{
    status = Serial.read();
    if(status == "panic")
    {
        servo.write(0);        
    }
}
