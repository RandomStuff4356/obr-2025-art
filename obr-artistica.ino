#include <Servo.h> 
#define sensorLumen 8

#define r 6 
#define g 5
#define b 3 
//IMPORTANTE:
//PARA COR DO LED RGB, USAR analogWrite AO INVÉS DE digitalWrite

int leitura=0;
String status = "stable";
  
Servo servo;


void setup() 
{
  servo.attach(9, 500, 2500);
  servo.write(90); //Coloca o servo na posição inicial

  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(b, OUTPUT);

  Serial.begin(9600);
}

void loop() 
{
  // Serial.println(leitura);
  leitura = !digitalRead(sensorLumen);
  Serial.println(leitura);
  if(status=="stable") 
  {
    lighthouseStable();
  }
  else if(status == "panic")
  {
  	lighthousePanic();
  }

  if(leitura == 0 && status == "stable")
 {
    servo.write(0);//Libera o meteoro
    status = "panic";
 }
}

void lighthouseStable() {
  analogWrite(r, 255);
  analogWrite(g, 255);

  for(int i=0; i <= 255; i++) //Gradualmente deixa o amarelo mais claro 
  { 
    analogWrite(b, i); 
    //Serial.println(i); 
  }
  
    for(int i=255; i>=0; i--) //Gradualmente deixa o amarelo mais escuro
  {
    analogWrite(b, i);
    //Serial.println(i);
  }
}

void lighthousePanic() 
{
  analogWrite(g, 0);
  analogWrite(b, 0);

  for(int i=255; i <=53; i++) //Gradualmente deixa o vermelho mais claro 
  { 
    analogWrite(r, i); 
    //Serial.println(i); 
  }
    
  for(int i=53; i>=255; i--) //Gradualmente deixa o vermelho mais escuro
  {
    analogWrite(r, i);
    //Serial.println(i);
  }
}
