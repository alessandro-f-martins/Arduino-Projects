#include <LiquidCrystal.h>

// SUGESTAO: usar lcd.createChar() e lcd.write() no modo de uso para mostrar o banco utilizado de forma grande

#define LOOP_SAIR 5 
#define MODO_EDICAO 0
#define MODO_USO 1

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int pinoEntradaConf = A1;    // select the input pin for the potentiometer
int pinoSelecaoModo = A2;
int pinoSelecaoOK = A3;

byte bancoSeletor = 0;
byte loopSeletor = 0;
byte loopSeletorAnterior = 0;
byte modoOperacao = MODO_USO;

byte estadoLeituraSeletor = 0;

byte bancos[4] = {
  0,0,0,0};

void usaSeletor() {

  int val = analogRead(pinoEntradaConf);
  delay(10);

  if (val <= 110)
    estadoLeituraSeletor = 1;
  if ((val >= 310) && (val <= 330))
    estadoLeituraSeletor = 2;
  if ((val >= 510) && (val <= 530))
    estadoLeituraSeletor = 3;
  if ((val >= 710) && (val <= 730))
    estadoLeituraSeletor = 4;
  if (val >= 910)
    estadoLeituraSeletor = 5;

}

int leComDebounce(int pino) {
  int ret = digitalRead(pino);
  delay(10);
  return ret;
}

void setup() {
  pinMode(pinoSelecaoModo, INPUT);
  pinMode(pinoSelecaoOK, INPUT);

  lcd.begin(16, 2);
  lcd.print("PedaleiraDigital");
  lcd.setCursor(0, 1);
  lcd.print("v0.1");
  delay(1000);
}

void loop() {

  leComDebounce(pinoSelecaoModo) != HIGH;

  modoOperacao = !modoOperacao;

  if (modoOperacao == MODO_EDICAO) {

    while (bancoSeletor != LOOP_SAIR) { 
      estadoLeituraSeletor = 0;
      bancoSeletor = 1;
      loopSeletor = 1;

      lcd.clear();
      lcd.print("Selecionar banco");
      lcd.setCursor(0, 1);
      lcd.print("Banco: ");
      lcd.setCursor(7, 1);

      while (leComDebounce(pinoSelecaoOK) != HIGH) {
        usaSeletor();
        bancoSeletor = estadoLeituraSeletor;
        lcd.print(((bancoSeletor != LOOP_SAIR)?String(bancoSeletor):"Sair"));
      }

      if (bancoSeletor != LOOP_SAIR) {

        estadoLeituraSeletor = 0;

        lcd.clear();
        lcd.print("Selecionar loops");
        lcd.setCursor(0, 1);
        
        while (loopSeletor != LOOP_SAIR) {

          while (leComDebounce(pinoSelecaoOK) != HIGH) {
            usaSeletor();
            loopSeletor = estadoLeituraSeletor;
            int posicaoCursorLoop = (2*(loopSeletor-1));
            lcd.setCursor(posicaoCursorLoop, 1);
            lcd.print(loopSeletor);
          }

          if (loopSeletor != LOOP_SAIR) {
            int bitLoop = bitRead(bancos[bancoSeletor-1], loopSeletor-1);
            bitWrite(bancos[bancoSeletor-1], loopSeletor-1, !bitLoop);
            //EM CONSTRUCAO: colocar codigo para verificacao se o loop ja esta selecionado ou nao, e entao apaga-lo ou escreve-lo no LCD
            
          }
          else {
            lcd.setCursor(0, 1);
            lcd.print("Sai edicao loops");
            delay(500);
          }
        }
        
      } // end if (bancoSeletor != LOOP_SAIR) 
    } // end while (bancoSeletor != LOOP_SAIR)
  } // end if (modoOperacao == MODO_EDICAO) 
  else { // MODO_USO
    lcd.clear();
    lcd.print("Banco em uso: "); //modificar aqui quando levar para o codigo final; deve refletir o banco em uso. Ver SUGESTAO acima
    // Aqui vai o codigo de uso da pedaleira
    delay(100);
  }

}





