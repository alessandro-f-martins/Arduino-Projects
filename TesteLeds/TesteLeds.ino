const int leds[4] = {
  6, 7, 8, 9};
int i = 0;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  for (i=0; i < 4; i++)
    pinMode(leds[i], OUTPUT);
  i = 0;
}

// the loop routine runs over and over again forever:
void loop() {
  
  digitalWrite(leds[i], HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(leds[i], LOW);    // turn the LED off by making the voltage LOW
  i = ((i < 3)?(i+1):0);

}
