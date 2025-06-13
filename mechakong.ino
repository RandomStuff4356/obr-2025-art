#define pinSensorD 13
#define pinSensorE 10
 
#define pinMotorE2 3
#define pinMotorE1 5
#define pinMotorD2 6
#define pinMotorD1 9
 
#define velocidade 70       // Velocidade normal de andar reto
#define velocidadegiro 100  // Velocidade para girar
#define velocidadec 100     // Velocidade para o movimento de correção
 
#define trigPin A0
#define echoPin A1
bool estadoD = 0;
bool estadoE = 0;
 
float distancia = 0;
void setup() {
  pinMode(pinSensorD, INPUT);
  pinMode(pinSensorE, INPUT);
 
  pinMode(pinMotorD1, OUTPUT);
  pinMode(pinMotorD2, OUTPUT);
  pinMode(pinMotorE1, OUTPUT);
  pinMode(pinMotorE2, OUTPUT);
 
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
 
void loop() {
  ler();
  segueLinha();
  delay(10);
}
 
void segueLinha() {
  // Verifica se há obstáculo
  if (distancia <= 8.0 && distancia >= 2) {
    // Para os motores
    analogWrite(pinMotorD1, LOW);
    analogWrite(pinMotorD2, LOW);
    analogWrite(pinMotorE1, LOW);
    analogWrite(pinMotorE2, LOW);
    delay(500);  // Espera meio segundo parado
    analogWrite(pinMotorD1, velocidade);
    analogWrite(pinMotorD2, LOW);
    analogWrite(pinMotorE1, LOW);
    analogWrite(pinMotorE2, velocidade);
    delay(200);
    // Gira à esquerda (motor direito para frente, esquerdo para trás)
    analogWrite(pinMotorD1, velocidadegiro);
    analogWrite(pinMotorD2, LOW);
    analogWrite(pinMotorE1, velocidadegiro);
    analogWrite(pinMotorE2, LOW);
    delay(400);  // Ajuste esse tempo para controlar o ângulo da curva
    // Anda reto novamente após giro
    analogWrite(pinMotorD1, LOW);
    analogWrite(pinMotorD2, velocidade);
    analogWrite(pinMotorE1, velocidade);
    analogWrite(pinMotorE2, LOW);
    delay(900);
    // Gira à direita (motor esquerdo para frente, direito para trás)
    analogWrite(pinMotorD1, LOW);
    analogWrite(pinMotorD2, velocidadegiro);
    analogWrite(pinMotorE1, LOW);
    analogWrite(pinMotorE2, velocidadegiro);
    delay(425);  // Ajuste esse tempo para controlar o ângulo da curva
    // Para novamente
    analogWrite(pinMotorD1, LOW);
    analogWrite(pinMotorD2, LOW);
    analogWrite(pinMotorE1, LOW);
    analogWrite(pinMotorE2, LOW);
    delay(300);
    analogWrite(pinMotorD1, LOW);
    analogWrite(pinMotorD2, velocidade);
    analogWrite(pinMotorE1, velocidade);
    analogWrite(pinMotorE2, LOW);
    delay(1750);
        // Gira à direita (motor esquerdo para frente, direito para trás)
    analogWrite(pinMotorD1, LOW);
    analogWrite(pinMotorD2, velocidadegiro);
    analogWrite(pinMotorE1, LOW);
    analogWrite(pinMotorE2, velocidadegiro);
    delay(400);
  } else if (!estadoD && !estadoE) {
    // Nenhum sensor sobre a linha, anda reto
    analogWrite(pinMotorD1, LOW);
    analogWrite(pinMotorD2, velocidade);
    analogWrite(pinMotorE2, LOW);
    analogWrite(pinMotorE1, velocidade);
  } else if (!estadoD && estadoE) {
    // Sensor da esquerda sobre a linha, gira à direita
    analogWrite(pinMotorE1, velocidadec);
    analogWrite(pinMotorE2, LOW);
    analogWrite(pinMotorD1, velocidadec);
    analogWrite(pinMotorD2, LOW);
  } else if (estadoD && !estadoE) {
    // Sensor da direita sobre a linha, gira à esquerda
    analogWrite(pinMotorD2, velocidadec);
    analogWrite(pinMotorD1, LOW);
    analogWrite(pinMotorE2, velocidadec);
    analogWrite(pinMotorE1, LOW);
  } else {
    analogWrite(pinMotorD1, LOW);
    analogWrite(pinMotorD2, velocidade);
    analogWrite(pinMotorE2, LOW);
    analogWrite(pinMotorE1, velocidade);
  }
}
 
void ler() {
  // Envia pulso ao sensor ultrassônico
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  long duracao = pulseIn(echoPin, HIGH);
  distancia = duracao * 0.034 / 2;
 
  // Segue linha: lê os sensores de linha
  estadoD = !digitalRead(pinSensorD);
  estadoE = !digitalRead(pinSensorE);
  Serial.print("Esq: ");
  Serial.print(estadoD);
  Serial.print(" Dir: ");
  Serial.println(estadoE);
}
 
