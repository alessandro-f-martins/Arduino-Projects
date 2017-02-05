
#define BOTAO_VERM_INF 775
#define BOTAO_VERM_SUP 850
#define BOTAO_AZUL_INF 580
#define BOTAO_AZUL_SUP 596
#define BOTAO_PRET_INF 363
#define BOTAO_PRET_SUP 425
#define BOTAO_AMAR_INF 190
#define BOTAO_AMAR_SUP 205
#define SEM_BOTAO_INF 0
#define SEM_BOTAO_SUP 150

/*
Resistores Usados: 33k (pode trocar para valores maiores para baixar a corrente)
 
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
int sensorValue = 0;  // variable to store the value coming from the sensor

String valorLido;
byte  estadoLeituraAtual = 0;
byte estadoLeituraAnterior = 0;


void setup() {

  Serial.begin(9600);

}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  delay(10);  
 

 if ((sensorValue >= SEM_BOTAO_INF) && (sensorValue <= SEM_BOTAO_SUP)) {
    valorLido = "sem botao";
    estadoLeituraAtual = 0;
  }
  else if ((sensorValue >= BOTAO_VERM_INF) && (sensorValue <= BOTAO_VERM_SUP)) {
    valorLido = "botao 1 (vermelho)";
    estadoLeituraAtual = 1;
  }
  else if ((sensorValue >= BOTAO_AZUL_INF) && (sensorValue <= BOTAO_AZUL_SUP)) {
    valorLido = "botao 2 (azul)";
    estadoLeituraAtual = 2;
  }
  else if ((sensorValue >= BOTAO_PRET_INF) && (sensorValue <= BOTAO_PRET_SUP)) {
    valorLido = "botao 3 (preto)";
    estadoLeituraAtual = 3;
  }
  else if ((sensorValue >= BOTAO_AMAR_INF) && (sensorValue <= BOTAO_AMAR_SUP)) {
    valorLido = "botao 4 (amarelo)";
    estadoLeituraAtual = 4;
  }  
  else if (sensorValue > BOTAO_VERM_SUP) {
    valorLido = "fora da escala";
    estadoLeituraAtual = 255;
  }  


  if (estadoLeituraAnterior != estadoLeituraAtual)
  {
    Serial.println("Botao pressionado: " + valorLido);
    Serial.println("Valor lido: " + String(sensorValue));
    estadoLeituraAnterior = estadoLeituraAtual;
  }
}

