#define BOARD_SIZE 4
#define PATCH_SIZE 4

// Initializing ins and outs
int pedalButtons[BOARD_SIZE]  = {0, 1, 10, 13};
int patches[BOARD_SIZE]  = {6, 7, 8, 9};

int pedalBoardState = 0;
int pedalBoardReadState = 0;

int i;

// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.

  for (i = 0; i < BOARD_SIZE; i++) {
    pinMode(pedalButtons[i], INPUT);
    pinMode(patches[i], OUTPUT);
  }

  //Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {

  for (i = 0; i < BOARD_SIZE; i++)
    bitWrite(pedalBoardReadState, i, ((digitalRead(pedalButtons[i]) == LOW) ? 0 : 1));

  if (pedalBoardReadState != 0) {
    pedalBoardState = (pedalBoardState == pedalBoardReadState) ? 0 : pedalBoardReadState;
    delay(50); //debounce
  }

  for (i = 0; i < BOARD_SIZE; i++) {
    digitalWrite(patches[i], (bitRead(pedalBoardState, i) == 0 ? LOW : HIGH));
  }

}
