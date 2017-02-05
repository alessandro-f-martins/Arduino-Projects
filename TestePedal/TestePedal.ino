#include <LiquidCrystal.h>

// Variaveis do Programa:

byte configPedaleira = 0;
char entradaFormatada[] = "00000000";
char patchFormatado[] = "00000000";
byte bancos[8] = {0,0,0,0,0,0,0,0};
byte banco = 0;
byte bancoEscolhido = 0;
byte pedal = 0;
byte patchEscolhido;
byte patch;
byte patchEscolhido2 = 0;

//Variaveis de I/O

const int botoesSelecao =  A0;
const int pedal1 = 6;
const int pedal2 = 7;
const int pedal3 = 8;
const int pedal4 = 9;

const int patch1 = A1;
const int patch2 = A2;
const int patch3 = A3;
const int patch4 = A4;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

byte leBanco() {


  return (byte)0; 
}

byte lePatch() {
  return (byte)0; 
}

byte lePedal() {
  return (byte)0; 
}


byte leEntrada(byte entrada, byte estadoAnterior) {

  byte estadoAtual = 0;

  switch (entrada) {
  case 's':
    exit(1);
  case '1':
    estadoAtual = (byte)1;
    break;
  case '2':
    estadoAtual = (byte)2;
    break;
  case '3':
    estadoAtual = (byte)4;
    break;
  case '4':
    estadoAtual = (byte)8;
    break;
  case '5':
    estadoAtual = (byte)16;
    break;
  case '6':
    estadoAtual = (byte)32;
    break;
  case '7':
    estadoAtual = (byte)64;
    break;
  case '8':
    estadoAtual = (byte)128;
    break;
  default:
    estadoAtual = (byte)0;               
  }

  if (estadoAnterior == estadoAtual) estadoAtual = (byte)0;

  return estadoAtual;
}

void formata(byte entrada, char *formatada) {

  byte iter = entrada;
  char  i;

  for (i = 7; i >= 0; i--) {
    formatada[i] = ((iter % 2)?'1':'0');
    iter = iter >> 1;
  }
}

byte selecionaPatch(byte configPedaleira, byte* bancos) {
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

  pinMode(pedal1, INPUT);
  pinMode(pedal2, INPUT);
  pinMode(pedal3, INPUT);
  pinMode(pedal4, INPUT);

  pinMode(patch1, OUTPUT);
  pinMode(patch2, OUTPUT);
  pinMode(patch3, OUTPUT);
  pinMode(patch4, OUTPUT);

  lcd.begin(16, 2);
  lcd.print("BarbaLooper 1.0");


  Serial.println("Programe os bancos:");
  for (;;) {
    Serial.println("\nEntre com o banco desejado: (T para terminar): ");
    //          banco = _getch();
    //          putchar(banco); putchar('\n');

    banco = leBanco();   
    if (banco == 't') break;
    bancoEscolhido = (byte) (banco - '0');
    if ((bancoEscolhido < 1) || (bancoEscolhido > 8))
      continue;
    patchEscolhido = 0; 
    patch = 0;
    Serial.println("Inclua os patches desejados (T para terminar): ");
    while ((patch = lePatch()) != 't') {
      Serial.print(patch); 
      Serial.print(" ");
      patchEscolhido += leEntrada(patch, patchEscolhido);
    }
    Serial.println("\n");
    bancos[bancoEscolhido-1] = patchEscolhido;
  }
}

void loop() {

  Serial.println("\nEscolha o pedal (banco) desejado (1-8) (S para sair)");
  pedal = lePedal();
  configPedaleira = leEntrada(pedal, configPedaleira);
   Serial.println("Pedaleira selecionada com o banco desejado: " /*+ configPedaleira*/  );
  formata(configPedaleira, entradaFormatada);
   Serial.println("Pedaleira (em main): " /*+ entradaFormatada*/  );
  patchEscolhido2 = selecionaPatch(configPedaleira, bancos);
  formata(patchEscolhido2, patchFormatado);
   Serial.println("\nPatches selecionados:" /*+ patchFormatado)*/  );

}


