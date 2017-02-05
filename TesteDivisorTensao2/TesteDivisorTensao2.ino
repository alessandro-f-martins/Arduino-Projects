
#define BOTAO_VERM_INF 750
#define BOTAO_VERM_SUP 850
#define BOTAO_AZUL_INF 510
#define BOTAO_AZUL_SUP 681
#define BOTAO_PRET_INF 320
#define BOTAO_PRET_SUP 435
#define BOTAO_AMAR_INF 190
#define BOTAO_AMAR_SUP 250
#define SEM_BOTAO_INF 0
#define SEM_BOTAO_SUP 150 // Estou exagerando aqui!!

// Definindo as saidas dos botoes
#define SEM_BOT 0
#define BOTAO_1 1
#define BOTAO_2 2
#define BOTAO_3 3
#define BOTAO_4 4
#define BOTAO_ERR 255

/*
Resistores Usados no Divisor: 3k9 (pode trocar para valores maiores para baixar a corrente)
Resistor usado para pull-down: 100k (mais estavel que o anterior de 1M)

 		Média			Min	Max
 Botao Vermelho	795	                738     802
 Botao Azul	588  	                580	596
 Botao preto	390			363	425
 Botao amarelo	196	                190	204
 Sem botao	22,0412844036697	62	0
 
 
 Medicao:
 Analog Input: Azul
 
 Alimentacao:
 Fio Gnd: Preto
 Fio 5+: Vermelho
 
 */


int sensorPin = A0;    // select the input pin for the potentiometer
//int sensorValue = 0;  // variable to store the value coming from the sensor
byte  estadoLeituraAtual = 0;
byte estadoLeituraAnterior = 0;

String valorLido;

byte leBotoes(int sPin) {

  int sensorValue = analogRead(sPin);
  delay(20);
  Serial.println("LEitura: " + String(sensorValue));

  if ((sensorValue >= SEM_BOTAO_INF) && (sensorValue <= SEM_BOTAO_SUP)) {
    return SEM_BOT;
  }
  else if ((sensorValue >= BOTAO_VERM_INF) && (sensorValue <= BOTAO_VERM_SUP)) {
    return BOTAO_1;
  }
  else if ((sensorValue >= BOTAO_AZUL_INF) && (sensorValue <= BOTAO_AZUL_SUP)) {
    return BOTAO_2;
  }
  else if ((sensorValue >= BOTAO_PRET_INF) && (sensorValue <= BOTAO_PRET_SUP)) {
    return BOTAO_3;
  }
  else if ((sensorValue >= BOTAO_AMAR_INF) && (sensorValue <= BOTAO_AMAR_SUP)) {
    return BOTAO_4;
  }  
  else if (sensorValue > BOTAO_VERM_SUP) {
    return BOTAO_ERR;
  }  
  return BOTAO_ERR;

}


void setup() {

  Serial.begin(9600);

}

void loop() {
  // read the value from the sensor:

  estadoLeituraAtual = leBotoes(sensorPin);
  switch (estadoLeituraAtual) {
  case BOTAO_1:
    valorLido = "VERMELHO";
    break;
  case BOTAO_2:
    valorLido = "AZUL";
    break;
  case BOTAO_3:
    valorLido = "PRETO";
    break;
  case BOTAO_4:
    valorLido = "AMARELO";
    break;
  case SEM_BOT:
    valorLido = "";
    break;
  default:
    valorLido = "ERRO";
  }


  if (estadoLeituraAnterior != estadoLeituraAtual && (estadoLeituraAtual != BOTAO_ERR)) {
   if ((estadoLeituraAtual != SEM_BOT)) {
      Serial.println("Botao pressionado: " + valorLido);
   }
    estadoLeituraAnterior = estadoLeituraAtual;
  }
}


