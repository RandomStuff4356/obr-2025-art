#include <Ultrasonic.h>
#include <Servo.h>

#define pinMotorE1 3 
#define pinMotorE2 5 
#define pinMotorD1 6
#define pinMotorD2 9

#define velocidadeE 195 //forte
#define velocidadeD 220 
#define velocidadee 125//fraco
#define velocidaded 132 
// Pinos TRIG e ECHO
#define TRIG_PIN A1
#define ECHO_PIN A0

Ultrasonic ultrasonic(TRIG_PIN, ECHO_PIN);
Servo servo;

void setup() {
    servo.attach(10);
    servo.write(90); // Coloca o servo na posição inicial
  Serial.begin(9600);
  pinMode(pinMotorD1, OUTPUT);
  pinMode(pinMotorD2, OUTPUT);
  pinMode(pinMotorE1, OUTPUT);
  pinMode(pinMotorE2, OUTPUT);

}

void loop() {
  long distancia = ultrasonic.read();



if (distancia >= 3 || distancia < 1){

    analogWrite(pinMotorD2, LOW); 
    analogWrite(pinMotorD1, LOW);
    analogWrite(pinMotorE1, LOW);
    analogWrite(pinMotorE2, LOW);
    delay (10);
}
else {
  delay (2000);
analogWrite(pinMotorD1, velocidaded); 
     analogWrite(pinMotorD2, LOW);
     analogWrite(pinMotorE2, LOW);
     analogWrite(pinMotorE1, LOW);
    delay (1380);
    analogWrite(pinMotorD2, LOW); 
     analogWrite(pinMotorD1, LOW);
     analogWrite(pinMotorE1, LOW);
     analogWrite(pinMotorE2, LOW);
    delay (700);
    analogWrite(pinMotorD2, LOW); 
    analogWrite(pinMotorD1, 110);
    analogWrite(pinMotorE1, velocidadee);
    analogWrite(pinMotorE2, LOW);
    delay (500);
    analogWrite(pinMotorD2, LOW); 
    analogWrite(pinMotorD1, LOW);
    analogWrite(pinMotorE1, LOW);
    analogWrite(pinMotorE2, LOW);
    delay (10);
    servo.write(0); // Gira o servo para a esquerda
    delay(400);
    
    analogWrite(pinMotorD2, LOW); 
    analogWrite(pinMotorD1, velocidaded);
    analogWrite(pinMotorE1, velocidadee);
    analogWrite(pinMotorE2, LOW);
    delay (300);
    analogWrite(pinMotorD2, LOW); 
    analogWrite(pinMotorD1, LOW);
    analogWrite(pinMotorE1, LOW);
    analogWrite(pinMotorE2, LOW);
  delay(300);

  for(int i = 0; i != 4; i++)
  {
    servo.write(260);
    delay(350);
    
    servo.write(90); 
    delay(450);
    
    analogWrite(pinMotorD2, LOW); 
    analogWrite(pinMotorD1, 110);
    analogWrite(pinMotorE1, velocidadee);
    analogWrite(pinMotorE2, LOW);
    delay (120);
    analogWrite(pinMotorD2, LOW); 
    analogWrite(pinMotorD1, LOW);
    analogWrite(pinMotorE1, LOW);
    analogWrite(pinMotorE2, LOW);
    delay(120);
  }
      
    analogWrite(pinMotorD1, LOW); 
    analogWrite(pinMotorD2, 110);
    analogWrite(pinMotorE2, velocidadee);
    analogWrite(pinMotorE1, LOW);
    delay (80);
    analogWrite(pinMotorD2, LOW); 
    analogWrite(pinMotorD1, LOW);
    analogWrite(pinMotorE1, LOW);
    analogWrite(pinMotorE2, LOW);
    delay(80);
    servo.write(260); 
    delay(500);
    
    // analogWrite(pinMotorD2, velocidaded); 
    //  analogWrite(pinMotorD1, LOW);
    //  analogWrite(pinMotorE1, velocidadee);
    //  analogWrite(pinMotorE2, LOW);
    // delay (200);

    servo.write(90);
    delay(500);

    analogWrite(pinMotorD2, LOW); 
    analogWrite(pinMotorD1, 80);
    analogWrite(pinMotorE1, velocidadee);
    analogWrite(pinMotorE2, LOW);
    delay (1200);
    analogWrite(pinMotorD2, LOW); 
    analogWrite(pinMotorD1, LOW);
    analogWrite(pinMotorE1, LOW);
    analogWrite(pinMotorE2, LOW);

    delay (1111111700);
}
}
