#include <Servo.h> 
#define sensorLumen A0

#define r 6 
#define g 5
#define b 3 
//IMPORTANTE:
//PARA COR DO LED RGB, USAR analogWrite AO INVÉS DE digitalWrite

bool isChecking = false;

String status = "stable";
  
Servo servo;

void setup() 
{
  servo.attach(9);
  servo.write(90); //Coloca o servo na posição inicial

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
    if(analogRead(sensorLumen) <= 200 && status == "stable")
    {
      delay(5000);
      status = "panic";
      delay(5000);
    }

    else if(analogRead(sensorLumen) <= 200 && status == "panic")
    {
      status = "impact";
    }
      
    isChecking = true;
  }//Final do if do check

  else  //Se isChecking for verdadeira
  {
    //Serial.println(analogRead(sensorLumen));
    if(status=="stable") 
    {
      isChecking = false;
      lighthouseStable();
    }

    else if(status == "panic")
    {
      isChecking = false;
  	  lighthousePanic();
      servo.write(0);//Libera o meteoro
    }

    else if(status == "impact")
    {
      isChecking = false;
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
  }//Fim do for
  
  for(int i=200; i>=100; i--) //Gradualmente deixa o amarelo mais escuro
  {
    analogWrite(r, i); 
    analogWrite(g, i);
    Serial.println(i);
    Serial.println(analogRead(sensorLumen));
    Serial.println(status);
  }//Fim do for

  isChecking = false;
}//Fim da função

void lighthousePanic() 
{
  analogWrite(g, 0);
  analogWrite(b, 0);

  for(int i=255; i <=53; i++) //Gradualmente deixa o vermelho mais claro 
  { 
    analogWrite(r, i);
    Serial.println(i); 
  }//Fim do for
    
  for(int i=53; i>=255; i--) //Gradualmente deixa o vermelho mais escuro
  {
    analogWrite(r, i);
    Serial.println(i);
  }//Fim do for

  isChecking = false;
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
