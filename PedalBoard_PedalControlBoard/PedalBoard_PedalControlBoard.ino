#define BOARD_SIZE 4
#define PATCH_SIZE 4

// Definindo as saidas dos botoes
#define SEM_BOT 0

/* Definindo o tempo de resposta da pedaleira (quanto tempo o pedal pode ficar pressionado para mudar de estado apenas uma vez)
Pode ser ajustado de acordo com a necessidade. */

#define TEMPO_RESPOSTA_PEDAL 25

// Variaveis do Programa:

int configPedaleira = 0;
int configPedaleiraAnterior = 0;
int bancos[PATCH_SIZE] = {0, 0, 0, 0};

//Variaveis de I/O

const int pedalButtons[BOARD_SIZE]  = {0, 1, 10, 13};
const int patches[PATCH_SIZE] = {6, 7, 8, 9};

int debouncedRead(int pin) {
  int ret = digitalRead(pin);
  delay(TEMPO_RESPOSTA_PEDAL);
  return ret;
}

int acionaPedaleira() {

  int leitura = SEM_BOT;

  for (int i = 0; i < BOARD_SIZE; i++)
    //    bitWrite(leitura, i, ((debouncedRead(pedalButtons[i]) == LOW) ? 0 : 1));
    if (debouncedRead(pedalButtons[i]) == HIGH) {
      leitura = i + 1;
      break;
    }
  // Se pisou em algum pedal
  if (leitura != SEM_BOT) {
    // Se o pedal pisado for o mesmo que o ultimo, zera a pedaleira e o pedal escolhido
    // Senao, configura a nova pedaleira e guarda o valor do pedal escolhido (banco)
    configPedaleira = (configPedaleira == leitura) ? 0 : leitura;
    //delay(TEMPO_RESPOSTA_PEDAL);  // Ver se o debounce deve vir aqui; se precisar, devo tirar o debounceRead() 
  }

  return configPedaleira;
}

void acionaLoops() {
  for (int i = 0; i < PATCH_SIZE; i++)
    digitalWrite(patches[i], (bitRead(bancos[configPedaleira - 1], i) ? HIGH : LOW));
}

void setup() {

  //Serial.begin(9600);
  for (int i = 0; i < BOARD_SIZE; i++) {
    pinMode(pedalButtons[i], INPUT);
    pinMode(patches[i], OUTPUT);;
  }

  bancos[0] = 1; // Patch 1
  bancos[1] = 1 + 2 + 4 + 8; // Patches 1, 2 e 3
  bancos[2] = 1 + 8; // Patches 1 e 4
  bancos[3] = 2; // Patch 2
}

void loop() {

  while (acionaPedaleira() == configPedaleiraAnterior);

  configPedaleiraAnterior = configPedaleira;
  acionaLoops();
  //delay(TEMPO_RESPOSTA_PEDAL);

}

