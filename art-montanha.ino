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
  servo.attach(9);
  servo.write(90); //Coloca o servo na posição inicial

  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(b, OUTPUT);

  Serial.begin(9600);
}//Fim do setup

void loop() 
{
  leitura = analogRead(sensorLumen); //Leitura do sensor de luz

  if(!isChecking)//Se a variável isChecking for falsa
  {  
    if(analogRead(sensorLumen) <= 200 && status == "stable")
    {
      servo.write(0);//Libera o meteoro
      status = "panic";
    }

    else if(analogRead(sensorLumen) >= 200 && status == "panic")
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
    Serial.println(leitura);
    Serial.println(status);
    delay(400);//Desacelera a gradiente
  }//Fim do for
  
  for(int i=200; i>=100; i--) //Gradualmente deixa o amarelo mais escuro
  {
    analogWrite(r, i); 
    analogWrite(g, i);
    Serial.println(i);
    Serial.println(analogRead(sensorLumen));
    Serial.println(leitura);
    Serial.println(status);
    delay(400);//Desacelera a gradiente
  }//Fim do for

  isChecking = true;
}//Fim da função

void lighthousePanic() 
{
  analogWrite(g, 0);
  analogWrite(b, 0);

  for(int i=255; i <=53; i++) //Gradualmente deixa o vermelho mais claro 
  { 
    analogWrite(r, i);
    Serial.println(i); 
    delay(400);//Desacelera a gradiente
  }//Fim do for
    
  for(int i=53; i>=255; i--) //Gradualmente deixa o vermelho mais escuro
  {
    analogWrite(r, i);
    Serial.println(i);
    delay(400);//Desacelera a gradiente
  }//Fim do for

  isChecking = true;
}//Fim da função

void lighthouseImpact()
{
  for(int i = 8; i != 0; i--)
  {
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
