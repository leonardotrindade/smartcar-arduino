#include <MeetAndroid.h>

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

MeetAndroid meetAndroid;
int velocidade = 255;

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

  Serial.begin(9600);
  meetAndroid.registerFunction(frente, 'A');
  meetAndroid.registerFunction(tras, 'B');
  meetAndroid.registerFunction(direita, 'C');
  meetAndroid.registerFunction(esquerda, 'D');
}

void loop() {
  meetAndroid.receive();
}

void parar()
{
  digitalWrite(E1, LOW);
  digitalWrite(E2, LOW);
  digitalWrite(E3, LOW);
  digitalWrite(E4, LOW);
}

void frente()
{
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

  delay(2000);
  parar();
}

void tras()
{
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

  delay(2000);
  parar();
}

void direita()
{
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

  delay(2000);
  parar();
}

void esquerda()
{
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

  delay(2000);
  parar();
}
