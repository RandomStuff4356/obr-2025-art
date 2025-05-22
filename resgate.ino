// === PINOS DOS SENSORES ===
#define sensorDireitaCanto 52
#define sensorEsquerdaCanto 44
#define sensorDireitaMeio 50
#define sensorEsquerdaMeio 46
#define sensorMeio 48
 
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
 
// === SETUP: CONFIGURAÇÃO INICIAL ===
void setup() {
  // Configura os pinos dos motores como saída
  pinMode(motorEsqFrente, OUTPUT);
  pinMode(motorEsqTras, OUTPUT);
  pinMode(motorDirFrente, OUTPUT);
  pinMode(motorDirTras, OUTPUT);
 
  // Configura os pinos dos sensores como entrada
  pinMode(sensorDireitaCanto, INPUT);
  pinMode(sensorEsquerdaCanto, INPUT);
  pinMode(sensorDireitaMeio, INPUT);
  pinMode(sensorEsquerdaMeio, INPUT);
  pinMode(sensorMeio, INPUT);
 
  // Liga o monitor serial (para ver o que o robô vê)
  Serial.begin(9600);
  Serial.println("Robô iniciando...");
 
  // Começa a contar o tempo
  tempoAnterior = millis();
}
 
// === LOOP PRINCIPAL: O QUE O ROBÔ FAZ REPETIDAMENTE ===
void loop() {
  unsigned long tempoAgora = millis();
 
  // A cada 100 milissegundos, lê os sensores
  if (tempoAgora - tempoAnterior >= 100) {
   lerSensores();
    tempoAnterior = tempoAgora;
  }
   lerSensores();
  seguirLinha();   // Decide o que fazer
  executarAcao();  // Faz a ação escolhida
}
 
// === FUNÇÃO: LÊ OS SENSORES E MOSTRA NO MONITOR SERIAL ===
void  lerSensores(){
  valorSensorEsqCanto = !digitalRead(sensorEsquerdaCanto);
  valorSensorDirMeio = !digitalRead(sensorDireitaMeio);
  valorSensorEsqMeio = !digitalRead(sensorEsquerdaMeio);
  valorSensorDirCanto = !digitalRead(sensorDireitaCanto);
  valorSensorMeio = !digitalRead(sensorMeio);
 
  // Mostra o que os sensores viram
  Serial.print("Dir canto: ");
  Serial.print(valorSensorDirCanto);
  Serial.print(" | Dir meio: ");
  Serial.print(valorSensorDirMeio);
  Serial.print(" | Meio: ");
  Serial.print(valorSensorMeio);
  Serial.print(" | Esq meio: ");
  Serial.print(valorSensorEsqMeio);
  Serial.print(" | Esq canto: ");
  Serial.println(valorSensorEsqCanto);
}
 
// === FUNÇÃO: DECIDE O QUE FAZER COM BASE NOS SENSORES ===
void seguirLinha() {
  // Se todos os sensores veem preto, é um cruzamento
  if (valorSensorDirCanto && valorSensorEsqCanto && valorSensorDirMeio && valorSensorEsqMeio) {
    Serial.println("Cruzamento encontrado!");
    estado = PARADO;
    inicioAcao = millis();
 
  } else if ((valorSensorDirCanto &&!valorSensorEsqMeio) ||
             (valorSensorDirCanto && !valorSensorEsqCanto)) {
    Serial.println("Virando para direita...");
    estado = VIRANDO_DIREITA_90;
 
  } else if ((valorSensorEsqCanto &&!valorSensorDirMeio) ||
             (valorSensorEsqCanto && !valorSensorDirCanto)) {
    Serial.println("Virando para esquerda...");
    estado = VIRANDO_ESQUERDA_90;
 
  } else if (valorSensorDirMeio && !valorSensorEsqMeio) {
    estado = CORRIGINDO_DIREITA;
    inicioAcao = millis();
    Serial.println("Corrigindo para direita...");
 
  } else if (valorSensorEsqMeio && !valorSensorDirMeio) {
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
         lerSensores();
         break;
 
    case PARADO:
      mover('p', 0);  // Fica parado por 1 segundo
      if (tempoAtual - inicioAcao >= 1000) {
        mover('f', velocidadeNormal);
        estado = ANDANDO_FRENTE;
      }
         lerSensores();
      break;
 
    case VIRANDO_DIREITA_90:
             mover('p', 0);
        mover('f', 40);
        delay(500);
         mover('p', 0);
         do { lerSensores();
         mover('D', velocidadeCurvaLeve); } // Vira para direita
      while (valorSensorMeio || valorSensorEsqMeio); {               // Quando vê linha no meio, para
        mover('p', 0);
         mover('t', 150);
        estado = ANDANDO_FRENTE;
      }
         lerSensores();
      break;
 
    case VIRANDO_ESQUERDA_90:
       mover('p', 0);
        mover('f', 40);
                delay(500);
         mover('p', 0);
         do {
         lerSensores();
         mover('E', velocidadeCurvaLeve);  }// Vira para esquerda
        while (valorSensorMeio || valorSensorDirMeio); {               // Quando vê linha no meio, para
        mover('p', 0);
         mover('t', 150);
        estado = ANDANDO_FRENTE;
      }
         lerSensores();
      break;
 
    case CORRIGINDO_DIREITA:
      mover('d', velocidadeCurvaLeve);  // Corrige levemente para direita
      delay(500);
        estado = ANDANDO_FRENTE;  // Depois de 500ms, volta a andar
         lerSensores();
      break;
 
    case CORRIGINDO_ESQUERDA:
      mover('e', velocidadeCurvaLeve);  // Corrige levemente para esquerda
      delay(500);
        estado = ANDANDO_FRENTE;  // Depois de 500ms, volta a andar
         lerSensores();
      break;
  }
}
