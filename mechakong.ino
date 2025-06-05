#define pinSensorD 13
#define pinSensorE 10

#define pinMotorE1 3 
#define pinMotorE2 5 
#define pinMotorD1 6
#define pinMotorD2 9

#define velocidade 70 
#define velocidadec 100 

void setup() {
  // put your setup code here, to run once:
  pinMode(pinSensorD, INPUT);
  pinMode(pinSensorE, INPUT);

  pinMode(pinMotorD1, OUTPUT);
  pinMode(pinMotorD2, OUTPUT);
  pinMode(pinMotorE1, OUTPUT);
  pinMode(pinMotorE2, OUTPUT);
}

void loop() {
 bool estadoD = !digitalRead(pinSensorD);
  bool estadoE = !digitalRead(pinSensorE);

  if (estadoD && estadoE) {
     analogWrite(pinMotorD2, LOW); 
     analogWrite(pinMotorD1, velocidade);
     analogWrite(pinMotorE1, LOW);
     analogWrite(pinMotorE2, velocidade);
  }

  if (!estadoD && !estadoE) {
    analogWrite(pinMotorD2, LOW); 
     analogWrite(pinMotorD1, velocidade);
     analogWrite(pinMotorE1, LOW);
     analogWrite(pinMotorE2, velocidade);
  }

  if (!estadoD && estadoE) {
     digitalWrite(pinMotorE1, LOW);
     analogWrite(pinMotorE2, velocidadec);
     digitalWrite(pinMotorD1, LOW);
     analogWrite(pinMotorD2, velocidadec);
  }

  if (estadoD && !estadoE) {
     digitalWrite(pinMotorD2, LOW);
     analogWrite(pinMotorD1, velocidadec);
     digitalWrite(pinMotorE2, LOW);
     analogWrite(pinMotorE1, velocidadec);
  }
  
}
