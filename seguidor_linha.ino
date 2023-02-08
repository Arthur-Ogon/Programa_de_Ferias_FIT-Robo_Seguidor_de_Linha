#include <Easyuino.h>  // Include the library in order to the compiler know you want Easyuino library

using Easyuino::DistanceMeter;  // Necessary in order to use DistanceMeter API

int triggerPin = 13;  // Arduino pin that connects to Ultrasonic Module trigger pin
int echoPin = 2;


#define M1 6  // Pino_Velocidade 1º Motor ( 0 a 255)_ Porta IN2 ponte H;
#define dir1 5 // Pino_Direção do 1º Motor: Para frente / Para trás (HIGH ou LOW)_ porta IN1 ponte H;
#define enable1 3

#define M2 9   // Pino_Velocidade 2º Motor ( 0 a 255) _ Porta IN4 ponte H;
#define dir2 10  // Pino_Direção do 2º Motor: Para frente / Para trás (HIGH ou LOW)_ porta IN3 ponte H;
#define enable2 11


float dist;
int direita, esquerda;
int vel = 0;
//UltraSonicDistanceSensor distanceSensor(13,2);
DistanceMeter distanceMeter(triggerPin, echoPin);

// Sensores
#define pinS1 A5
#define pinS2 A3



void setup() {
  

  pinMode(enable1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(dir2, OUTPUT);
  digitalWrite(M2, LOW);
  digitalWrite(dir2, LOW);
  pinMode(M1, OUTPUT);
  pinMode(dir1, OUTPUT);
  digitalWrite(M1, LOW);
  digitalWrite(dir1, LOW);
  analogWrite(enable2, vel);
  analogWrite(enable1, vel);

 // while (!Serial);  // Necessary for Arduino Leonardo serial monitor use

  distanceMeter.begin();

  Serial.begin(9600);
}
void moveFrente(int vel) {
  digitalWrite(dir1, LOW);    
  digitalWrite(dir2, LOW);   
  analogWrite(enable1, 81);  //roda 1 velocidade

  digitalWrite(M1, HIGH);     // 
  digitalWrite(M2, HIGH);    
  analogWrite(enable2, vel);  // roda 2 velocidade
}

void ligarRodinha1 (int vel) {

  digitalWrite(dir1, LOW);     // rodinha 1 liga e vai para frente e a rodinha 2 liga e vai para trás 
  digitalWrite(dir2, HIGH);    
  analogWrite(enable1, 90);  

  digitalWrite(M1, HIGH);     
  digitalWrite(M2, LOW);  
  analogWrite(enable2, vel); 
}

void ligarRodinha2(int vel) {
  digitalWrite(dir1, HIGH);  // rodinha 2 liga e vai para frente e a rodinha 1 liga e vai para trás 
  digitalWrite(dir2, LOW);
  analogWrite(enable1, 90);

  digitalWrite(M1, LOW);    
  digitalWrite(M2, HIGH);
  analogWrite(enable2, vel);

}

void paraCarro(int vel) {
  digitalWrite(dir1, HIGH);
  digitalWrite(dir2, HIGH);
  analogWrite(enable1, 0);

  digitalWrite(M1, HIGH);
  digitalWrite(M2, HIGH);
  analogWrite(enable2, 0);
}



void loop() {

   direita = analogRead(pinS1);
  esquerda = analogRead(pinS2);
  int preto = 60; 
  int branco =  40;
  
  if(direita <= branco && esquerda <= branco){
    moveFrente(70);
     delay(1);   
  }
  if(direita >= preto && esquerda <= branco){ // SENSOR 1 (o sensor 1 encosta na linha preta, fazendo a rodinha 2 ligar)
    ligarRodinha1(85);
    delay(20);
  }  
  if( direita <= preto && esquerda >= branco){ // SENSOR 2 ( o sensor 2 encosta na linha preta, fazendo a rodinha 1 ligar)
    ligarRodinha2(90);
    delay(20);
  }
   if ( direita >= preto && esquerda >= preto){
    ligarsomenteRoda2(83);
    delay(975);
  } else if ( direita == preto && esquerda == preto){
    paraCarro(0);
  
  }
  
}
