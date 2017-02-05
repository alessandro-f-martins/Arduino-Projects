int pinoEntradaConf = A1;    // select the input pin for the potentiometer
int val = 0;
int estadoAnterior = 0;
int estado = 0;

void setup() {
  Serial.begin(9600);  
}

void loop() {
  // read the value from the sensor:
  val = analogRead(pinoEntradaConf);

  if (val <= 110)
    estado = 1;
  if ((val >= 310) && (val <= 330))
    estado = 2;
  if ((val >= 510) && (val <= 530))
    estado = 3;
  if ((val >= 710) && (val <= 730))
    estado = 4;
  if (val >= 910)
    estado = 5;
    
  if (estado != estadoAnterior) {
    Serial.println("Valor atual: " + String(estado)); 
    estadoAnterior = estado;
  }
  
}
