/*-------------------------------------------------------------------------- TRABALHO ROBO SUMO-------------------------------------------------------------------------------------------
INTEGRANTES: CAMILA SALVAN, CARLOS JUNIOR, VINICIUS RICARDO E YASMIM BARDINI



*/
 //--------------------------------------------------------------------------- SETANDO AS VARIAVEIS ---------------------------------------------------------------------------------------------------------

#include <NewPing.h> // inclusão da biblioteca dos sensores ultrassonicos
#include <Arduino.h> // Não sei??
#include <Servo.h> // inclusão da biblioteca que controla os servos


Servo servoD; // Servo da direita 
Servo servoE; // Servo da esquerda 
#define SensorLinhaFrente 2 // Sensor seguidor de linha da frente
#define SensorLinhaTras 3 // Sensor seguidor de linha de trás
#define MaxDistancia 300 // Setar Valor maximo lido pelos sensores ultrassonicos

#define pino_triggerF 14 //Definição do pino A0
#define pino_echoF 15 //Definição do pino A1
NewPing SensorFrente(pino_triggerF, pino_echoF, MaxDistancia);// Definição do Sensor ultrasonico da Frente;

#define pino_triggerD 16 //Definição do pino A2
#define pino_echoD 17 //Definição do pino A3
NewPing SensorDireita(pino_triggerD, pino_echoD, MaxDistancia);// Definição do Sensor ultrasonico da Direita;

#define pino_triggerE 18 //Definição do pino A4
#define pino_echoE 19 //Definição do pino A5
NewPing SensorEsquerda(pino_triggerE, pino_echoE, MaxDistancia);// Definição do Sensor ultrasonico da Esquerda;

#define pino_triggerT 6 //Definição do pino A6
#define pino_echoT 7 //Definição do pino A7
NewPing SensorTras(pino_triggerT, pino_echoT, MaxDistancia);// Definição do Sensor ultrasonico de Tras;

// --------------------------------------------------------------------------- VOID SETUP ---------------------------------------------------------------------------------------------------------
void setup() {
   servoD.attach(10);  //Definição do pino 11 como Servo da direita
   servoE.attach(11); //Definição do pino 11 como Servo da Esquerda
   pinMode(SensorLinhaFrente, INPUT); // Definição dos SensorLinhaFrente como entrada
   pinMode(SensorLinhaTras, INPUT); // Definição dos SensorLinhaTras como entrada
   Serial.begin(9600); // setando a porta Serial




}
// --------------------------------------------------------------------------- VOID LOOP ---------------------------------------------------------------------------------------------------------

void loop() {

  if (SensorFrente.ping_cm() <= 40 && SensorFrente.ping_cm() > 0 && digitalRead(SensorLinhaFrente) == 0 && digitalRead(SensorLinhaTras) == 0) { // Caso encontre o robo adversario em uma distancia de 30cm
    while (digitalRead(SensorLinhaFrente) == 0) { //Prende na condição até o sensor encotrar a borda da arena
      Serial.println("achei o oponente"); // Manda para serial que encontrou o oponente
      frente();//Movimenta para frente
    }
   }
 
if (SensorDireita.ping_cm() < 40 && SensorFrente.ping_cm() > 15 && digitalRead(SensorLinhaFrente) == 0 && digitalRead(SensorLinhaFrente) == 0) { // Caso encontre o robo adversario a direita em uma distancia de 30cm
    Serial.println("oponente a direita"); // Manda para serial que o oponente esta a direita
    GiroDireita(); // Gira um pouco para a direita
    delay(2000); // por 2 segundos
}

if (SensorEsquerda.ping_cm() < 40 && SensorFrente.ping_cm() > 15 && digitalRead(SensorLinhaFrente) == 0 && digitalRead(SensorLinhaFrente) == 0) { // Caso encontre o robo adversario a esquerda em uma distancia de 30cm
    Serial.println("oponente a Esquerda"); // Manda para serial que o oponente esta a esquerda
    GiroEsquerda(); // Gira um pouco para a esquerda
    delay(2000); // por 2 segundos
}

if (SensorTras.ping_cm() <= 40 && SensorTras.ping_cm() > 0 && digitalRead(SensorLinhaFrente) == 0 && digitalRead(SensorLinhaFrente) == 0) { // Caso encontre o robo adversario a atras em uma distancia de 30cm
    Serial.println("oponente atras"); // Manda para serial que o oponente esta atras
    frente(); // Vai para frente
    delay(2000); // por 2 segundos
    GiroCompleto(); // e dá um giro 180°
}

   if (digitalRead(SensorLinhaFrente) == 1 && digitalRead(SensorLinhaTras) == 0) { // Caso encontre a borda pelo sensor da frente
    Serial.println("Sensor da frente achou borda"); // Manda para serial que encontrou a borda
    tras(); // anda para tras por 500 milisegundos
    delay(500); // por 0,5 segundos
    GiroCompleto(); // e dá um giro 180°]
    delay(10000); // por 10 segundos
  }
  
    if (digitalRead(SensorLinhaFrente) == 0 && digitalRead(SensorLinhaTras) == 1) { // Caso encontre a borda pelo sensor de tras
    Serial.println("Sensor de tras achou borda"); // Manda para serial que encontrou a borda
    frente(); // anda para frente por 500 milisegundos
    delay(500);
        
    }

    if (SensorFrente.ping_cm() > 30 && digitalRead(SensorLinhaFrente) == 0 && digitalRead(SensorLinhaFrente) == 0) { // Caso não encontre o robo adversario em uma distancia de 30cm
    Serial.println("procurando oponente"); // Manda para serial que esta procurando oponente
    Varredura(); // Faz a varredura
  }

}
// --------------------------------------------------------------------------- FUNÇÕES ESPECIFICAS ---------------------------------------------------------------------------------------------------------


void frente(){ // Função que faz o robo ir para frente
  servoD.write(65);
  servoE.write(115);
}
  

void tras(){ // Função que faz o robo ir para tras
  servoD.write(115);
  servoE.write(65);
}
  
void GiroDireita(){ // função que o robo gira 90° a direita 
  servoD.write(115);
  servoE.write(115);

}

void GiroEsquerda(){ // função que o robo gira 90° a Esquerda
  servoD.write(65);
  servoE.write(65);
 
}

void GiroCompleto(){ // Função que o robo gira 180° 
  servoD.write(115);
  servoE.write(115);
  delay(10000);

}

void  Varredura(){ // Função que o robo faz a varredura
  servoD.write(65);
  servoE.write(115);
  delay(1000);
  servoD.write(115);
  servoE.write(115);
  delay(1000);
  servoD.write(65);
  servoE.write(65);
  delay(2000);

}





