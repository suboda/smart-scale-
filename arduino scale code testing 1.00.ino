#include "HX711.h"
#include <SoftwareSerial.h>
HX711 scale;
SoftwareSerial bluetoothSerial(0, 1);
char val;

void setup() {
  Serial.begin(9600);
  scale.begin(A1, A0); // Initialize the HX711 with A0 as DT and A1 as SCK
  bluetoothSerial.begin(9600);
}

void loop() {
  if (scale.is_ready()) {
    long weight = scale.get_units(10); // Read the weight (adjust the argument as needed)
    float displayedValue = weight / 1000;
    Serial.print("Weight: ");
    Serial.println(displayedValue);
    bluetoothSerial.print(displayedValue);
      bluetoothSerial.print('\n') ;
  }
  {
  if(Serial.available ()){
    val = Serial.read();
    Serial.print(val);
    Serial.println();
    }
if   (val=='SN2'){
Serial.println("WON");
}
  }   
  
  delay(1); // Adjust the delay as needed
}
