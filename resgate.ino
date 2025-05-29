//=== Definições do Sensores === 
#include <QTRSensors.h>
QTRSensors qtr;
const uint8_t SensorCount = 6;
uint16_t sensorValues[SensorCount];
#define Corte 900

// === PINOS DOS SENSORES ===
#define sensorDireitaCanto sensorValues[1]
#define sensorEsquerdaCanto sensorValues[4]
#define sensorDireitaMeio sensorValues[2]
#define sensorEsquerdaMeio sensorValues[3]
#define sensorDireitaExtremo sensorValues[0]
#define sensorEsquerdaExtremo sensorValues[5]

// === PINOS DOS MOTORES ===
#define motorEsqFrente 3
#define motorEsqTras 5
#define motorDirFrente 6
#define motorDirTras 9

// === VELOCIDADES DO ROBÔ ===
#define velocidadeNormal 40
#define velocidadeCurvaLeve 120
#define velocidadeCurvaFechada 150
 
// === VARIÁVEIS PARA CONTROLE DE TEMPO ===
unsigned long tempoAnterior = 0;
unsigned long inicioAcao = 0;
 
// === ESTADOS DO ROBÔ (o que ele vai fazer agora) ===
enum {
  ESPERANDO,
  ANDANDO_FRENTE,
  PARADO,
  VIRANDO_DIREITA_90,
  VIRANDO_ESQUERDA_90,
  CORRIGINDO_DIREITA,
  CORRIGINDO_ESQUERDA
} estado = ESPERANDO;

// === VALORES DOS SENSORES ===
bool valorSensorMeio = false;
bool valorSensorDirCanto = false;
bool valorSensorDirMeio = false;
bool valorSensorEsqMeio = false;
bool valorSensorEsqCanto = false;

void setup()
{
// === SETUP: CONFIGURAÇÃO INICIAL ===
  // Configura os pinos dos motores como saída
  pinMode(motorEsqFrente, OUTPUT);
  pinMode(motorEsqTras, OUTPUT);
  pinMode(motorDirFrente, OUTPUT);
  pinMode(motorDirTras, OUTPUT);
 
  // configura os sensores
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3, A4, A5}, SensorCount);
  qtr.setEmitterPin(A7);

//Calibra os sensores
  delay(500);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); // turn on Arduino's LED to indicate we are in calibration mode
  for (uint16_t i = 0; i < 400; i++)
  {
    qtr.calibrate();
  }
  digitalWrite(LED_BUILTIN, LOW); // turn off Arduino's LED to indicate we are through with calibration
  Serial.begin(9600);
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(qtr.calibrationOn.minimum[i]);
    Serial.print(' ');
  }
  Serial.println();
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(qtr.calibrationOn.maximum[i]);
    Serial.print(' ');
  }
  Serial.println();
  Serial.println();
  delay(2000);

  // Começa a contar o tempo
  tempoAnterior = millis();

}


void loop()
{

  //Passa as informações para o monitor serial
uint16_t position = qtr.readLineBlack(sensorValues);
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  Serial.println(position);

  unsigned long tempoAgora = millis();
 
  // A cada 100 milissegundos, lê os sensores
  if (tempoAgora - tempoAnterior >= 100) {
    tempoAnterior = tempoAgora;
  }
  seguirLinha();   // Decide o que fazer
  executarAcao();  // Faz a ação escolhida
}
 
// === FUNÇÃO: DECIDE O QUE FAZER COM BASE NOS SENSORES ===
void seguirLinha() {
  // Se todos os sensores veem preto, é um cruzamento
  if (sensorDireitaCanto >= Corte && sensorEsquerdaCanto >= Corte && sensorDireitaExtremo >= Corte && sensorEsquerdaExtremo >= Corte) {
    Serial.println("Cruzamento encontrado!");
    estado = PARADO;
    inicioAcao = millis();
 
  } else if ((sensorDireitaExtremo >= Corte && sensorEsquerdaMeio < Corte) || (sensorDireitaCanto >= Corte && sensorEsquerdaMeio < Corte )) {
    Serial.println("Virando para direita...");
    estado = VIRANDO_DIREITA_90;
 
  } else if ((sensorEsquerdaExtremo >= Corte && sensorDireitaMeio < Corte) || (sensorEsquerdaExtremo >= Corte && sensorDireitaMeio < Corte)) {
    Serial.println("Virando para esquerda...");
    estado = VIRANDO_ESQUERDA_90;
 
  } else if (sensorDireitaCanto >= Corte && sensorEsquerdaCanto < Corte) {
    estado = CORRIGINDO_DIREITA;
    inicioAcao = millis();
    Serial.println("Corrigindo para direita...");
 
  } else if (sensorEsquerdaCanto >= Corte && sensorDireitaCanto < Corte) {
    estado = CORRIGINDO_ESQUERDA;
    inicioAcao = millis();
    Serial.println("Corrigindo para esquerda...");
 
  } else {
    estado = ANDANDO_FRENTE;
    Serial.println("Seguindo em frente...");
  }
}
 
// === FUNÇÃO: CONTROLA OS MOTORES SEM USAR DELAY ===
void mover(char direcao, byte velocidade) {
  switch (direcao) {
    case 'f':  // Frente
      analogWrite(motorEsqFrente, velocidade);
      analogWrite(motorEsqTras, LOW);
      analogWrite(motorDirFrente, velocidade);
      analogWrite(motorDirTras, LOW);
      break;
 
    case 't':  // Gira para trás um pouco
      analogWrite(motorEsqFrente, LOW);
      analogWrite(motorEsqTras, velocidadeCurvaFechada);
      analogWrite(motorDirFrente, velocidadeCurvaFechada);
      analogWrite(motorDirTras, LOW);
      break;
 
    case 'd':  // Curva leve para Direita
      analogWrite(motorEsqFrente, velocidadeCurvaLeve);
      analogWrite(motorEsqTras, LOW);
      analogWrite(motorDirFrente, LOW);
      analogWrite(motorDirTras, velocidadeCurvaLeve);
      break;
 
    case 'D':  // Curva forte para Direita
      analogWrite(motorEsqFrente, velocidadeCurvaFechada);
      analogWrite(motorEsqTras, LOW);
      analogWrite(motorDirFrente, LOW);
      analogWrite(motorDirTras, velocidadeCurvaFechada);
      break;
 
    case 'e':  // Curva leve para Esquerda
      analogWrite(motorEsqFrente, LOW);
      analogWrite(motorEsqTras, velocidadeCurvaLeve);
      analogWrite(motorDirFrente, velocidadeCurvaLeve);
      analogWrite(motorDirTras, LOW);
      break;
 
    case 'E':  // Curva forte para Esquerda
      analogWrite(motorEsqFrente, LOW);
      analogWrite(motorEsqTras, velocidadeCurvaFechada);
      analogWrite(motorDirFrente, velocidadeCurvaFechada);
      analogWrite(motorDirTras, LOW);
      break;
 
    case 'p':  // Parado
      analogWrite(motorEsqFrente, LOW);
      analogWrite(motorEsqTras, LOW);
      analogWrite(motorDirFrente, LOW);
      analogWrite(motorDirTras, LOW);
      break;
  }
}
 
// === FUNÇÃO: EXECUTA A AÇÃO ESCOLHIDA PELO ROBÔ ===
void executarAcao() {
  unsigned long tempoAtual = millis();
 
  switch (estado) {
    case ESPERANDO:
      mover('p', 0);  // Parado
      break;
 
    case ANDANDO_FRENTE:
      mover('f', velocidadeNormal);  // Anda pra frente
      break;
 
    case PARADO:
      mover('p', 0);  // Fica parado por 1 segundo
      if (tempoAtual - inicioAcao >= 1000) {
        mover('f', velocidadeNormal);
        estado = ANDANDO_FRENTE;
      }
      break;
 
    case VIRANDO_DIREITA_90:
      mover('p', 0);
      mover('f', 80);
      delay(1000);
      mover('p', 0);
      do {
        mover('D', velocidadeCurvaFechada);
        delay(10);
      } while (sensorDireitaMeio >= Corte || sensorEsquerdaMeio >= Corte);
      // Quando vê linha no meio, para
      mover('p', 0);
      mover('t', 150);
      delay(500);
      estado = ANDANDO_FRENTE;
      break;
 
    case VIRANDO_ESQUERDA_90:
      mover('p', 0);
      mover('f', 40);
      delay(500);
      mover('p', 0);
      do {
        mover('E', velocidadeCurvaLeve);
      }  // Vira para esquerda
      while (sensorEsquerdaMeio >= Corte || sensorDireitaMeio >= Corte);
      {  // Quando vê linha no meio, para
        mover('p', 0);
        mover('t', 150);
        estado = ANDANDO_FRENTE;
      }
      break;
 
    case CORRIGINDO_DIREITA:
      mover('d', velocidadeCurvaLeve);  // Corrige levemente para direita
      delay(500);
      estado = ANDANDO_FRENTE;  // Depois de 500ms, volta a andar
      break;
 
    case CORRIGINDO_ESQUERDA:
      mover('e', velocidadeCurvaLeve);  // Corrige levemente para esquerda
      delay(500);
      estado = ANDANDO_FRENTE;  // Depois de 500ms, volta a andar
      break;
  }
}

