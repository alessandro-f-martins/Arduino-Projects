int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor

String valorLido;

void setup() {

  Serial.begin(9600);

}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  delay(10);  
 
    Serial.println("Valor lido: " + String(sensorValue));
}

