#include <Servo.h> 
#define sensorLumen A0

#define r 6 
#define g 5
#define b 3
//IMPORTANTE:
//PARA COR DO LED RGB, USAR analogWrite AO INVÉS DE digitalWrite

bool isChecking = false;

int valorDeCorte = 200;

String status = "stable";
  
void setup() 
{
  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(sensorLumen, INPUT);

  Serial.begin(9600);
}//Fim do setup

void loop() 
{
  if(!isChecking)//Se a variável isChecking for falsa
  {  
    if(analogRead(sensorLumen) <= valorDeCorte && status == "stable")
    {
      delay(5000);
      status = "panic";
    }

    else if(analogRead(sensorLumen) <= valorDeCorte && status == "panic")
    {
      status = "impact";
    }
      
    isChecking = true;
  }//Final do if do check

  else  //Se isChecking for verdadeira
  {
    isChecking = false;
    //Serial.println(analogRead(sensorLumen));
    if(status=="stable") 
    {
      lighthouseStable();
    }

    else if(status == "panic")
    {
  	  lighthousePanic();
    }

    else if(status == "impact")
    {
      lighthouseImpact();
    }

  }   //Final do else

}//Fim do loop

void lighthouseStable() 
{
  analogWrite(b, 0);

  for(int i=100; i <= 200; i++) //Gradualmente deixa o amarelo mais claro 
  { 
    analogWrite(r, i); 
    analogWrite(g, i); 
    Serial.println(i);
    Serial.println(analogRead(sensorLumen));
    Serial.println(status);
    Serial.println(isChecking);
  isChecking = false;
  }//Fim do for
  
  for(int i=200; i>=100; i--) //Gradualmente deixa o amarelo mais escuro
  {
    analogWrite(r, i); 
    analogWrite(g, i);
    Serial.println(i);
    Serial.println(analogRead(sensorLumen));
    Serial.println(status);
  isChecking = false;
  }//Fim do for

}//Fim da função

void lighthousePanic() 
{
  analogWrite(g, 0);
  analogWrite(b, 0);

  for(int i=255; i <=53; i++) //Gradualmente deixa o vermelho mais claro 
  { 
    analogWrite(r, i);
    Serial.println(i); 
  isChecking = false;
  }//Fim do for
    
  for(int i=53; i>=255; i--) //Gradualmente deixa o vermelho mais escuro
  {
    analogWrite(r, i);
    Serial.println(i);
  isChecking = false;
  }//Fim do for

}//Fim da função

void lighthouseImpact()
{
  for(int i = 8; i != 0; i--)
  {
    if(random(0, 5) == 1)
    {
      for(int i = 4; i != 0; i--)
      {
      analogWrite(r, 255);
      analogWrite(g, 255);
      analogWrite(b, 255);
      delay(80);
      analogWrite(r, 0);
      analogWrite(g, 0);
      analogWrite(b, 0);
      delay(80);
      }
    }
    analogWrite(r, 255);
    analogWrite(g, 255);
    analogWrite(b, 255);
    //LED branco
    delay(random(100, 1000));//Delay aleatório de 0,1s a 1s
    analogWrite(r, 0);
    analogWrite(g, 0);
    analogWrite(b, 0);
    //LED desligado
    delay(random(100, 1000));//Delay aleatório de 0,1s a 1s
  }//Fim do for

}//Fim da função
