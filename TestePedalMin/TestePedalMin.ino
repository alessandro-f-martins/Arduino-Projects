
// Variaveis do Programa:

byte configPedaleira = 0;
byte configPedaleiraAnterior = 0;
byte bancos[4] = {0,0,0,0};
byte banco = 0;
byte bancoEscolhido = 0;
byte pedal = 0;
byte patchEscolhido;
byte patch;


//Variaveis de I/O

//const int botoesSelecao =  A0;
const int pedais[4] = {
  6, 7, 8, 9};
const int patches[4] = {
  A1, A2, A3, A4};

int debounceRead(int pin) {
  int valor = 0;
  int valorAnterior = -1;

  while ((valor = digitalRead(pin)) != valorAnterior){
    delay(10);
    valorAnterior = valor;
  }
  return valor;
}

byte acionaPedaleira(byte nPedal) {

  byte cPedaleira = 1;

  // Se pisou no pedal "nPedal", devolve a pedaleira com so ele ligado
  if (digitalRead(nPedal) == HIGH) return (cPedaleira << nPedal); // trocar depois para versao com debounce
  // Caso contrario, mantem a configuracao 
  return configPedaleira;
}

/*
byte leBanco() {


  return (byte)0; 
}

byte lePatch() {
  return (byte)0; 
}

byte lePedal() {
  return (byte)0; 
}
*/

void acionaLoops(byte loopPedais) {
  byte iter = loopPedais;
  byte i;

  for (i = 0; i > 4; i++) {
    if (iter % 2)
      digitalWrite(patches[i],LOW);
    else  
      digitalWrite(patches[i],HIGH);
    iter = iter >> 1;
  }
}

byte selecionaLoop() {
  byte cP = configPedaleira;
  char count = 0;

  while (cP > 0) {
    count++;
    cP = cP >> 1;
  }
  return bancos[count-1];
}


void setup() {

  Serial.begin(9600);

  for (int i = 0; i < 4; i++) {
    pinMode(pedais[i], INPUT);
    pinMode(patches[i], OUTPUT);
  }

  bancos[0] = 1; // Patch 1
  bancos[1] = 1 + 4; // Patches 1 e 3 
  bancos[2] = 2 + 4; // Patches 2 e 3
  bancos[3] = 8; // Patch 4
}

void loop() {

  banco = 0;
  while ((configPedaleira = acionaPedaleira(banco)) == configPedaleiraAnterior)
    banco = ((banco < 3)?banco+1:0);

  configPedaleiraAnterior = configPedaleira;

  Serial.print("Banco selecionado:");
  Serial.println(banco+1);
  acionaLoops(selecionaLoop());

  Serial.println("\nPatches selecionados:" /*+ patchFormatado)*/  );

}




