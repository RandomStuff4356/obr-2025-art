//Funcionalidade:
#include <Ultrasonic.h>

#define trig A1
#define echo A0

#define pinMotorE1 9
#define pinMotorE2 6
#define pinMotorD1 3
#define pinMotorD2 5

#define velocidadeR 255 //velocidade na reta
#define diferencialEsq 160//Diferencial pra roda esquerda
#define velocidadeC 150 //velocidade na curva

Ultrasonic ultra(trig, echo);
bool virou;
float distancia;
const int corte = 7;

void setup() 
{
    virou = false;

    pinMode(pinMotorD1, OUTPUT);
    pinMode(pinMotorD2, OUTPUT);
    pinMode(pinMotorE1, OUTPUT);
    pinMode(pinMotorE2, OUTPUT);

    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
}

void loop() 
{
  lerSensores();
  if(distancia <= corte && distancia > 1 && !virou)
  {
    virou = true;
    lopenEsq(1100);
    lopenFrente(3750);
    delay(1000);
    lopenDir(700);
    delay(500);
    lopenEsq(300);
    delay(800);
    lopenEsq(500);
    delay(500);
    lopenDir(700);
    delay(500);
    lopenDir(700);
  }
}

void lerSensores()
{
    distancia = ultra.read();
}

void lopenFrente(int time)
{
    // Frente
    analogWrite(pinMotorD2, velocidadeR); 
    analogWrite(pinMotorD1, LOW);
    analogWrite(pinMotorE1, velocidadeR - diferencialEsq);
    analogWrite(pinMotorE2, LOW);
    delay (time);
    parar();
}

void lopenTras(int time)
{ 
    // Trás
    analogWrite(pinMotorD2, LOW); 
    analogWrite(pinMotorD1, velocidadeR);
    analogWrite(pinMotorE1, LOW);
    analogWrite(pinMotorE2, velocidadeR - diferencialEsq);
    delay (time);
    parar();
}

void lopenDir(int time)
{
    // Direita
    analogWrite(pinMotorD2, LOW); 
    analogWrite(pinMotorD1, velocidadeC - 400);
    analogWrite(pinMotorE1, velocidadeC - diferencialEsq - 400);
    analogWrite(pinMotorE2, LOW);
    delay (time);
    parar();
}

void lopenEsq(int time)
{
    // Esquerda
    analogWrite(pinMotorD2, velocidadeC); 
    analogWrite(pinMotorD1, LOW);
    analogWrite(pinMotorE1, LOW);
    analogWrite(pinMotorE2, velocidadeC - diferencialEsq);
    delay(time);
    parar();
}
void parar()
{
  analogWrite(pinMotorE1, LOW);
  analogWrite(pinMotorE2, LOW);
  analogWrite(pinMotorD1, LOW);
  analogWrite(pinMotorD2, LOW);
}
