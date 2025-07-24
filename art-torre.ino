#include <Ultrasonic.h>

#define TRIG_PIN 13
#define ECHO_PIN 12
Ultrasonic ultrasonic(TRIG_PIN, ECHO_PIN);

#define r 6 
#define g 5
#define b 3

int valorDeCorte = 5;
String status = "stable";

// Variáveis para controle de tempo sem delay
unsigned long previousMillis = 0;
int brightness = 100;
bool increasing = true;

// Variáveis para controle do modo impact
unsigned long impactPreviousMillis = 0;
int impactPattern = 0;
int patternStep = 0;
unsigned long patternInterval = 0;

// Sistema de bloqueio de transição
unsigned long lastStateChange = 0;
unsigned long stateChangeLockout = 2000; // 2 segundos sem mudanças após detecção

void setup() 
{
  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(b, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
  long distancia = ultrasonic.read();
  
  unsigned long currentTime = millis();
  
  // Só permite mudança de estado se não estiver em período de bloqueio
  if(currentTime - lastStateChange > stateChangeLockout) 
  {
    // Atualiza status baseado na distância
    if(distancia <= valorDeCorte && status == "stable")
    {
      Serial.println("Mudando para PANIC");
      status = "panic";
      lastStateChange = currentTime; // Registra o momento da mudança
    }
    else if(distancia <= valorDeCorte && status == "panic")
    {
      Serial.println("Mudando para IMPACT");
      status = "impact";
      lastStateChange = currentTime; // Registra o momento da mudança
    }
  }

  // Executa a função apropriada
  if(status == "stable") 
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

  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.print(" Status: ");
  Serial.println(status);
  
  delay(50); // Pequeno delay para estabilidade do sensor
}


void lighthouseStable() 
{
  // Pisca amarelo suavemente
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= 30) 
  {
    previousMillis = currentMillis;
    
    if(increasing) 
    {
      brightness++;
      if(brightness >= 200) increasing = false;
    } 
    else 
    {
      brightness--;
      if(brightness <= 100) increasing = true;
    }
    
    analogWrite(r, brightness);
    analogWrite(g, brightness);
    analogWrite(b, 0);
  }
}

void lighthousePanic() 
{
  // Pisca vermelho mais lento
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= 300) 
  {
    previousMillis = currentMillis;
    
    static bool ledState = false;
    ledState = !ledState;
    
    if(ledState) 
    {
      analogWrite(r, 255);
      analogWrite(g, 0);
      analogWrite(b, 0);
    } 
    else 
    {
      analogWrite(r, 50);  // Vermelho mais fraco quando "desligado"
      analogWrite(g, 0);
      analogWrite(b, 0);
    }
  }
}

void lighthouseImpact()
{
  // Controle de padrões sem delay
  unsigned long currentMillis = millis();
  
  if(currentMillis - impactPreviousMillis >= patternInterval) 
  {
    impactPreviousMillis = currentMillis;
    
    switch(impactPattern) {
      case 0: // Pisca rápido
        if(patternStep == 0) {
          analogWrite(r, 255);
          analogWrite(g, 255);
          analogWrite(b, 255);
          patternInterval = 50;
          patternStep = 1;
        } else {
          analogWrite(r, 0);
          analogWrite(g, 0);
          analogWrite(b, 0);
          patternInterval = 100;
          patternStep = 0;
          impactPattern = random(0, 3); // Muda padrão
        }
        break;
        
      case 1: // Pisca duplo
        if(patternStep == 0) {
          analogWrite(r, 255);
          analogWrite(g, 255);
          analogWrite(b, 255);
          patternInterval = 80;
          patternStep = 1;
        } else if(patternStep == 1) {
          analogWrite(r, 0);
          analogWrite(g, 0);
          analogWrite(b, 0);
          patternInterval = 80;
          patternStep = 2;
        } else if(patternStep == 2) {
          analogWrite(r, 255);
          analogWrite(g, 255);
          analogWrite(b, 255);
          patternInterval = 80;
          patternStep = 3;
        } else {
          analogWrite(r, 0);
          analogWrite(g, 0);
          analogWrite(b, 0);
          patternInterval = random(500, 1500);
          patternStep = 0;
          impactPattern = random(0, 3);
        }
        break;
        
      case 2: // Pisca longo
        if(patternStep == 0) {
          analogWrite(r, 255);
          analogWrite(g, 255);
          analogWrite(b, 255);
          patternInterval = random(200, 800);
          patternStep = 1;
        } else {
          analogWrite(r, 0);
          analogWrite(g, 0);
          analogWrite(b, 0);
          patternInterval = random(200, 1000);
          patternStep = 0;
          impactPattern = random(0, 3);
        }
        break;
    }
  }
}
