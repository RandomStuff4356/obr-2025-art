#include <Servo.h> 
#define sensorLumen A0

#define r 6 
#define g 5
#define b 3 
//IMPORTANTE:
//PARA COR DO LED RGB, USAR analogWrite AO INVÉS DE digitalWrite

int leitura=0;
bool isChecking = true;

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
  if(analogRead(sensorLumen) > 250){ leitura = 1;}
  else{ leitura = 0;}

  if(leitura == 0 && status == "stable")
 {
    servo.write(0);//Libera o meteoro
    status = "panic";
    isChecking = true;
 }
 else
 {
    //Serial.println(analogRead(sensorLumen));
    if(status=="stable" && isChecking) 
    {
      isChecking = false;
     lighthouseStable();
    }
    else if(status == "panic" && isChecking)
    {
      isChecking = false;
  	  lighthousePanic();
    }
  }

 }

void lighthouseStable() {
  analogWrite(b, 0);

  for(int i=100; i <= 200; i++) //Gradualmente deixa o amarelo mais claro 
  { 
    analogWrite(r, i); 
    analogWrite(g, i); 
    Serial.println(i);
    Serial.println(analogRead(sensorLumen));
    Serial.println(leitura);
    Serial.println(status);
    delay(400);//Desacelera a gradiente
  }
  
    for(int i=200; i>=100; i--) //Gradualmente deixa o amarelo mais escuro
  {
    analogWrite(r, i); 
    analogWrite(g, i);
    Serial.println(i);
    Serial.println(analogRead(sensorLumen));
    Serial.println(leitura);
    Serial.println(status);
    delay(400);//Desacelera a gradiente
  }
  isChecking = true;
}

void lighthousePanic() 
{
  analogWrite(g, 0);
  analogWrite(b, 0);

  for(int i=255; i <=53; i++) //Gradualmente deixa o vermelho mais claro 
  { 
    analogWrite(r, i);
    Serial.println(i); 
    delay(400);//Desacelera a gradiente
  }
    
  for(int i=53; i>=255; i--) //Gradualmente deixa o vermelho mais escuro
  {
    analogWrite(r, i);
    Serial.println(i);
    delay(400);//Desacelera a gradiente
  }
  isChecking = true;
}
