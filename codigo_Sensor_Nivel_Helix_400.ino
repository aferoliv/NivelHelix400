/********************************************************************************
 * Sensor de nível capacitivo XKC-Y25-NPN
 * 06jun22 - Andre Fernando de Oliveira  andrefernando23@gmail.com
 * LEliana- Laboratório de Eletronica para Instrumentação Analítica /LaQuA
 * Universidade Federal de Viçosa
 * ------------------------------------------------------------------------------
 * 
 * 
 ********************************************************************************/
int teclado=0;
int Pino_Alto=A4;
int Pino_Baixo=A6;
int LED_Baixo=5;
int LED_Alto=7;
int Pino_LED=8;
int Pino_Output=10;
int read_Alto=0;
int read_Baixo=0;
int status_NC=0;
int nivel_Alto=0;
int nivel_Baixo=0;
void setup() {
  /* inicializa a serial */
  Serial.begin(9600);
 
  /* aguarda a serial estar disponível */
  while (!Serial);
 
  /* imprime o nome do arquivo com data e hora */
 // Serial.println(F("\r\n"__FILE__"\t"__DATE__" "__TIME__));
 
  pinMode(Pino_Alto,INPUT);
  pinMode(Pino_Baixo,INPUT);
  pinMode(Pino_LED, OUTPUT);
  pinMode(LED_Alto, OUTPUT);
  pinMode(LED_Baixo, OUTPUT);
  digitalWrite(Pino_LED,LOW);
  digitalWrite(LED_Alto,LOW);
  digitalWrite(Pino_Output,LOW);
}

void loop() {
 while(teclado<1){
    /* lê entrada do teclado */
    teclado=Serial.read();
    read_Alto=analogRead(Pino_Alto);
    read_Baixo=analogRead(Pino_Baixo);

    //Serial.print(read_Alto);
    //Serial.print(read_Baixo);
    Serial.println();
    if (read_Baixo <150) {
       nivel_Baixo=0;
       //Serial.print("nivel_Baixo=0");
       digitalWrite(LED_Baixo, LOW);
    }
     if (read_Baixo >150) {
       nivel_Baixo=1;
       digitalWrite(LED_Baixo, HIGH);
       //Serial.print("nivel_Baixo=1");
    }
    if (read_Alto<200) {
      nivel_Alto=0;
       digitalWrite(LED_Alto, LOW);
      //Serial.print("nivel_Alto=0");
    }
     if (read_Alto>200) {
       nivel_Alto=1;
       digitalWrite(LED_Alto, HIGH);
       Serial.print("nivel_Alto=1");
    }
     //Serial.println();
    if(status_NC==0&&nivel_Baixo==0){
        status_NC=1;
        digitalWrite(Pino_LED, HIGH);
        digitalWrite(Pino_Output, HIGH);
        Serial.print("status_NC=1 - Enchendo");
        Serial.println(read_Alto);
    }
    if(status_NC==1&&nivel_Baixo==1){
      Serial.print("status_NC=1 - Baixo=1");
    }
     if(status_NC==0&&nivel_Alto==1){
      Serial.print("status_NC=0 - Alto=1");
    }
     if(status_NC==1&&nivel_Alto==1){
        status_NC=0;
        digitalWrite(Pino_LED, LOW);
        digitalWrite(Pino_Output, LOW);
        Serial.print("status_NC=0 - Esvaziando");
        /*delay(120000);*/
        Serial.println();
    }
    /*digitalWrite(Pino_LED, LOW);
    Serial.print(read_Baixo, 4);
    Serial.println();*/
  }  
 }

