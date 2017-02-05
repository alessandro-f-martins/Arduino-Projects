/*
Resistores Usados no Divisor: 3k9 (pode trocar para valores maiores para baixar a corrente)
 Resistor usado para pull-down: 100k (mais estavel que o anterior de 1M)
 
 		Média			Min	Max
 Botao Vermelho	795	                738     802
 Botao Azul	588  	                580	596
 Botao preto	390			363	425
 Botao amarelo	196	                190	204
 Sem botao	22              	62	0
 
 
 Medicao:
 Analog Input: Azul
 
 Alimentacao:
 Fio Gnd: Preto
 Fio 5+: Vermelho
 
 */

//Constantes de limites para atuaçao dos botoes nas entradas analogicas

#define BOTAO_1_INF 730 // VERMELHO
#define BOTAO_1_SUP 830 
#define BOTAO_2_INF 550 // AZUL
#define BOTAO_2_SUP 650
#define BOTAO_3_INF 350 // PRETO
#define BOTAO_3_SUP 435
#define BOTAO_4_INF 190 // AMARELO
#define BOTAO_4_SUP 250
#define SEM_BOTAO_INF 0
#define SEM_BOTAO_SUP 150

// Definindo as saidas dos botoes
#define SEM_BOT 0
#define BOTAO_1 1
#define BOTAO_2 2
#define BOTAO_3 3
#define BOTAO_4 4
#define BOTAO_ERR 255

/* Definindo o tempo de resposta da pedaleira (quanto tempo o pedal pode ficar pressionado para mudar de estado apenas uma vez)
Pode ser ajustado de acordo com a necessidade. */

#define TEMPO_RESPOSTA_PEDAL 150


// Variaveis do Programa:

byte configPedaleira = 0;
byte configPedaleiraAnterior = 0;
byte bancos[4] = {
  0,0,0,0};
byte banco = 0;
byte bancoEscolhido = 0;
byte pedal = 0;
byte patchEscolhido;
byte patch;

byte estadoLeituraAtual = 0;
byte estadoLeituraAnterior = 0;

//Variaveis de I/O

int pinoEntradaPedais = A0;
int pinoEntradaConf = A1;
const int patches[4] = {
  6, 7, 8, 9};


byte leBotoes(int sPin) {

  int sensorValue = analogRead(sPin);
  delay(10);  // pequeno debounce

  if ((sensorValue >= SEM_BOTAO_INF) && (sensorValue <= SEM_BOTAO_SUP)) {
    return SEM_BOT;
  }
  else if ((sensorValue >= BOTAO_1_INF) && (sensorValue <= BOTAO_1_SUP)) {
    return BOTAO_1;
  }
  else if ((sensorValue >= BOTAO_2_INF) && (sensorValue <= BOTAO_2_SUP)) {
    return BOTAO_2;
  }
  else if ((sensorValue >= BOTAO_3_INF) && (sensorValue <= BOTAO_3_SUP)) {
    return BOTAO_3;
  }
  else if ((sensorValue >= BOTAO_4_INF) && (sensorValue <= BOTAO_4_SUP)) {
    return BOTAO_4;
  }  
  else if (sensorValue > BOTAO_1_SUP) {
    return BOTAO_ERR;
  }  

  return BOTAO_ERR;

}


byte acionaPedaleira(int sensorPin) {

  byte cPedaleira = 1;

  byte leitura = leBotoes(sensorPin);

  // Se pisou em algum pedal
  if ((leitura != SEM_BOT) && (leitura != BOTAO_ERR)) {
    // Se o pedal pisado for o mesmo que o ultimo, zera a pedaleira e o pedal escolhido
    if (leitura == bancoEscolhido) {
        configPedaleira = 0;
        bancoEscolhido = 0;
    }
    // Senao, configura a nova pedaleira e guarda o valor do pedal escolhido (banco)
    else {
      configPedaleira = cPedaleira << (leitura-1);
      bancoEscolhido = leitura;
    }
  }

  return configPedaleira;

}

void acionaLoops(byte loopPedais) {
  byte iter = loopPedais;
  byte i;

  for (i = 0; i < 4; i++) {
    if (iter % 2)
      digitalWrite(patches[i],HIGH);
    else  
      digitalWrite(patches[i],LOW);
    iter = iter >> 1;
  }
}

byte selecionaLoop() {
  byte cP = configPedaleira;
  byte count = 0;

  if (cP == 0)
    return 0;

  while (cP > 0) {
    count++;
    cP = cP >> 1;
  }
  return bancos[count-1];
}


void setup() {

  //Serial.begin(9600);
  for (int i = 0; i < 4; i++) {
    pinMode(patches[i], OUTPUT);
  }


  bancos[0] = 1; // Patch 1
  bancos[1] = 1 + 2 + 4 + 8; // Patches 1, 2 e 3 
  bancos[2] = 1 + 8; // Patches 1 e 4
  bancos[3] = 2; // Patch 2
}

void loop() {

  while ((configPedaleira = acionaPedaleira(pinoEntradaPedais)) == configPedaleiraAnterior);

  configPedaleiraAnterior = configPedaleira;
  acionaLoops(selecionaLoop());
//delay para garantir que houve tempo de pisar e soltar o pedal sem comprometer a resposta do circuito
// PARA ANALISAR: se deve ir para dentro de acionaLoops(), como ultima linha
  delay(TEMPO_RESPOSTA_PEDAL); 

}






