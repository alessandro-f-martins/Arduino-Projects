#define LOOP_SAIR 5 
#define MODO_EDICAO 0
#define MODO_USO 1

int pinoEntradaConf = A0;    // select the input pin for the potentiometer
int pinoSelecaoModo = A1;
int pinoSelecaoOK = A2;

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
  Serial.begin(9600);
  pinMode(pinoSelecaoModo, INPUT);
  pinMode(pinoSelecaoOK, INPUT);
}

void loop() {

//  leComDebounce(pinoSelecaoModo) != HIGH;
  modoOperacao = !modoOperacao;

  if (modoOperacao == MODO_EDICAO) {

    while (bancoSeletor != LOOP_SAIR) { 
      estadoLeituraSeletor = 0;
      bancoSeletor = 1;
      loopSeletor = 1;

      Serial.println("Selecionar banco");
      while (leComDebounce(pinoSelecaoOK) != HIGH) {
        usaSeletor();
        bancoSeletor = estadoLeituraSeletor;
        Serial.println("Banco: " + ((bancoSeletor != LOOP_SAIR)?String(bancoSeletor:''):"S"));
      }

      if (bancoSeletor != LOOP_SAIR) {

        estadoLeituraSeletor = 0;

        Serial.println("Selecionar loops");
        while (loopSeletor != LOOP_SAIR) {

          while (leComDebounce(pinoSelecaoOK) != HIGH) {
            usaSeletor();
            loopSeletor = estadoLeituraSeletor;
          }

          if (loopSeletor != LOOP_SAIR) {
            bitWrite(bancos[bancoSeletor-1], loopSeletor-1, !bitRead(bancos[bancoSeletor-1], loopSeletor-1));
            Serial.println("Loop " + String(loopSeletor) + (bitRead(bancos[bancoSeletor-1], loopSeletor-1)?" incluido":" excluido"));
          }
        }
        
      } // end if (bancoSeletor != LOOP_SAIR) 
    } // end while (bancoSeletor != LOOP_SAIR)
  } // end if (modoOperacao == MODO_EDICAO) 
  else { // MODO_USO
    Serial.println("Estou em modo de uso");
    delay(100);
  }

}





