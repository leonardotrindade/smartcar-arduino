#include <MeetAndroid.h>
#include <Servo.h>

// ------------------ Direção ---------------------
#define PARADO 0
#define FRENTE 1
#define TRAS 2
#define DIREITA 3
#define ESQUERDA 4
// ------------------ Direção ---------------------

// ------------------ Motores ---------------------
#define E1 10  // Enable Pin for motor 1
#define E2 11  // Enable Pin for motor 2
#define E3 6  // Enable Pin for motor 3
#define E4 5  // Enable Pin for motor 4

#define I1 8  // Control pin 1 for motor 1
#define I2 9  // Control pin 2 for motor 1
#define I3 12  // Control pin 1 for motor 2
#define I4 13  // Control pin 2 for motor 2
#define I5 2  // Control pin 1 for motor 3
#define I6 3  // Control pin 2 for motor 3
#define I7 7  // Control pin 1 for motor 4
#define I8 4  // Control pin 2 for motor 4
// ------------------ Motores ---------------------

#define SENSOR_TRIG A1
#define SENSOR_ECHO A2
#define LED_F A3
#define LED_T A4
#define BUZ A5

#define DISTANCIA_LIMITE 20 // Limite de 20 cm de distância para parar os motores

MeetAndroid meetAndroid;
Servo servo;

int velocidade = 0;
int frequencia = 0;
int direcao = PARADO;
int servo_pos = 80;
bool led_f = false;
bool led_t = false;
bool buz = false;
bool dist = false;
long duracao;
long distanciaAtual = 0;
long distanciaAnterior = 0;

void setup() {
  pinMode(E1, OUTPUT);
  pinMode(E2, OUTPUT);
  pinMode(E3, OUTPUT);
  pinMode(E4, OUTPUT);

  pinMode(I1, OUTPUT);
  pinMode(I2, OUTPUT);
  pinMode(I3, OUTPUT);
  pinMode(I4, OUTPUT);
  pinMode(I5, OUTPUT);
  pinMode(I6, OUTPUT);
  pinMode(I7, OUTPUT);
  pinMode(I8, OUTPUT);
  
  pinMode(LED_F, OUTPUT);
  pinMode(LED_T, OUTPUT);
  pinMode(SENSOR_TRIG, OUTPUT);
  pinMode(SENSOR_ECHO, INPUT);
  pinMode(BUZ, OUTPUT);

  servo.attach(14);
  servo.write(servo_pos);

  Serial.begin(9600);
  meetAndroid.registerFunction(frente, 'A');
  meetAndroid.registerFunction(tras, 'B');
  meetAndroid.registerFunction(direita, 'C');
  meetAndroid.registerFunction(esquerda, 'D');
  meetAndroid.registerFunction(parar, 'E');
  meetAndroid.registerFunction(toggleLedF, 'F');
  meetAndroid.registerFunction(toggleLedT, 'G');
  meetAndroid.registerFunction(servoPos, 'H');
  meetAndroid.registerFunction(toggleBuz, 'I');
  meetAndroid.registerFunction(toggleDist, 'J');
}

void loop() {
  meetAndroid.receive();
  checarDirecao();
  checarBuzzer();
  calcularDistancia();
}

void calcularDistancia() {
  if (dist) {
    digitalWrite(SENSOR_TRIG, LOW); //não envia som
    delayMicroseconds(2);
    digitalWrite(SENSOR_TRIG, HIGH); //envia som 
    delayMicroseconds(10);
    digitalWrite(SENSOR_TRIG, LOW); //não envia o som e espera o retorno do som enviado
    duracao = pulseIn(SENSOR_ECHO, HIGH); //Captura a duração em tempo do retorno do som.
    distanciaAnterior = distanciaAtual;
    distanciaAtual = duracao / 56; //Calcula a distância
    if (distanciaAtual != distanciaAnterior) {
      meetAndroid.send(distanciaAtual);
    }
    if (distanciaAtual <= DISTANCIA_LIMITE && distanciaAnterior <= DISTANCIA_LIMITE) {
      parar();
    }
    delay(500);
  }
}

void checarBuzzer() {
  if (buz) {
    tone(BUZ, 1000);
  } else {
    noTone(BUZ);
  }
}

void checarDirecao() {
  switch(direcao) {
    case FRENTE:
      analogWrite(E1, velocidade);
      analogWrite(E2, velocidade);
      analogWrite(E3, velocidade);
      analogWrite(E4, velocidade);
    
      digitalWrite(I1, LOW);
      digitalWrite(I2, HIGH);
      digitalWrite(I3, LOW);
      digitalWrite(I4, HIGH);
      digitalWrite(I5, HIGH);
      digitalWrite(I6, LOW);
      digitalWrite(I7, HIGH);
      digitalWrite(I8, LOW);
      break;
    case TRAS:
      analogWrite(E1, velocidade);
      analogWrite(E2, velocidade);
      analogWrite(E3, velocidade);
      analogWrite(E4, velocidade);
    
      digitalWrite(I1, HIGH);
      digitalWrite(I2, LOW);
      digitalWrite(I3, HIGH);
      digitalWrite(I4, LOW);
      digitalWrite(I5, LOW);
      digitalWrite(I6, HIGH);
      digitalWrite(I7, LOW);
      digitalWrite(I8, HIGH);
      break;
    case DIREITA:
      analogWrite(E1, velocidade);
      analogWrite(E2, velocidade);
      analogWrite(E3, velocidade);
      analogWrite(E4, velocidade);
    
      digitalWrite(I1, LOW);
      digitalWrite(I2, HIGH);
      digitalWrite(I3, LOW);
      digitalWrite(I4, HIGH);
      digitalWrite(I5, LOW);
      digitalWrite(I6, HIGH);
      digitalWrite(I7, LOW);
      digitalWrite(I8, HIGH);
      break;
    case ESQUERDA:
      analogWrite(E1, velocidade);
      analogWrite(E2, velocidade);
      analogWrite(E3, velocidade);
      analogWrite(E4, velocidade);
    
      digitalWrite(I1, HIGH);
      digitalWrite(I2, LOW);
      digitalWrite(I3, HIGH);
      digitalWrite(I4, LOW);
      digitalWrite(I5, HIGH);
      digitalWrite(I6, LOW);
      digitalWrite(I7, HIGH);
      digitalWrite(I8, LOW);
      break;
  }
}

void parar() {
  direcao = PARADO;
  velocidade = 0;
  digitalWrite(E1, LOW);
  digitalWrite(E2, LOW);
  digitalWrite(E3, LOW);
  digitalWrite(E4, LOW);
}

void frente() {
  velocidade = meetAndroid.getInt();
  direcao = FRENTE;
}

void tras() {
  velocidade = meetAndroid.getInt();
  direcao = TRAS;
}

void direita() {
  velocidade = meetAndroid.getInt();
  direcao = DIREITA;
}

void esquerda() {
  velocidade = meetAndroid.getInt();
  direcao = ESQUERDA;
}

void toggleLedF() {
  led_f = !led_f;
  if (led_f) {
    analogWrite(LED_F, 255);
  } else {
    analogWrite(LED_F, 0);
  }
}

void toggleLedT() {
  led_t = !led_t;
  if (led_t) {
    analogWrite(LED_T, 255);
  } else {
    analogWrite(LED_T, 0);
  }
}

void toggleBuz() {
  buz = !buz;
}

void toggleDist() {
  dist = !dist;
}

void servoPos() {
  servo_pos = meetAndroid.getInt();
  servo.write(servo_pos);
}

