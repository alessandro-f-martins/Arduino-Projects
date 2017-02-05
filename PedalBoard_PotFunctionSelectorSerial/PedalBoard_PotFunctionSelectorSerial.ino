#define LOOP_SAIR 5
#define MODO_EDICAO 0
#define MODO_USO 1

int pinoEntradaConf = A0;    // select the input pin for the potentiometer
int pinoSelecaoModo = A1;
int pinoSelecaoOK = A2;

byte bancoSeletor;
byte bancoSeletorAnterior;
byte loopSeletor;
byte loopSeletorAnterior;
byte modoOperacao = MODO_EDICAO;

boolean selecaoBotaoOK;

int bancos[4] = {
  0, 0, 0, 0
};

int usaSeletor() {

  int val = analogRead(pinoEntradaConf);
  delay(10);

  val = map(val, 0, 1023, 1, LOOP_SAIR);

  return val;
}

boolean leComDebounce(int pin) {

  boolean state;
  boolean previousState;

  previousState = digitalRead(pin); // store switch state
  for (int i = 0; i < 10; i++) {
    delay(1); // wait for 1 millisecond
    state = digitalRead(pin); // read the pin
    if (state != previousState) {
      i = 0; // reset the counter if the state changes
      previousState = state; // and save the current state
    }
  }
  // here when the switch state has been stable longer than the debounce period
  return state;
}

void setup() {
  Serial.begin(9600);
  pinMode(pinoSelecaoModo, INPUT);
  pinMode(pinoSelecaoOK, INPUT);
}

void loop() {

  if (leComDebounce(pinoSelecaoModo) == HIGH)
    modoOperacao = !modoOperacao;

  if (modoOperacao == MODO_EDICAO) {

    while (bancoSeletor != LOOP_SAIR) {
      bancoSeletor = 1;
      bancoSeletorAnterior = 0;
      loopSeletor = 1;
      loopSeletorAnterior = 0;
      selecaoBotaoOK = false;

      Serial.println("Selecionar banco");
      while (!selecaoBotaoOK) {
        while ((bancoSeletorAnterior == bancoSeletor) && !(selecaoBotaoOK = leComDebounce(pinoSelecaoOK)))
          bancoSeletor = usaSeletor();
        Serial.println("Banco: " + ((bancoSeletor != LOOP_SAIR) ? String(bancoSeletor) : "S"));
        bancoSeletorAnterior = bancoSeletor;
      }

      selecaoBotaoOK = false;
      Serial.println("Banco selecionado: " + String (bancoSeletor));

      if (bancoSeletor != LOOP_SAIR) {

        Serial.println("Selecionar loops");
        while (loopSeletor != LOOP_SAIR) {

          while (!selecaoBotaoOK) {
            while ((loopSeletorAnterior == loopSeletor) && !(selecaoBotaoOK = leComDebounce(pinoSelecaoOK)))
              loopSeletor = usaSeletor();
            Serial.println("Loop: " + ((loopSeletor != LOOP_SAIR) ? String(loopSeletor) : "S"));
            loopSeletorAnterior = loopSeletor;
          }

          selecaoBotaoOK = false;
          Serial.println("Loop selecionado: " + String (loopSeletor));

          if (loopSeletor != LOOP_SAIR) {
            bitWrite(bancos[bancoSeletor - 1], loopSeletor - 1, !bitRead(bancos[bancoSeletor - 1], loopSeletor - 1));
            Serial.println("Loop " + String(loopSeletor) + (bitRead(bancos[bancoSeletor - 1], loopSeletor - 1) ? " incluido" : " excluido"));
          }
        }

      } // end if (bancoSeletor != LOOP_SAIR)
    } // end while (bancoSeletor != LOOP_SAIR)
  } // end if (modoOperacao == MODO_EDICAO)
  else { // MODO_USO
    Serial.println("Estou em modo de uso");
    delay(5000);
  }

}
