#include "HX711.h"
#include <ShiftRegister74HC595.h>

HX711 scale;
ShiftRegister74HC595<4> sr(A4, A5, 2);

uint8_t numberB[] = {
    B11000000, // 0
    B11111001, // 1
    B10100100, // 2
    B10110000, // 3
    B10011001, // 4
    B10010010, // 5
    B10000010, // 6
    B11111000, // 7
    B10000000, // 8
    B10011000, // 9
    B11111111, // null
    B10000110, // E
    B10111111  // -
};

void setup()
{
  Serial.begin(9600);
  scale.begin(A1, A0); // Initialize the HX711 with A0 as DT and A1 as SCK
}

void loop()
{
  if (scale.is_ready())
  {
    // Read the weight from the load cell
    float weight = scale.get_units(1);

    // Display the weight on the LED display
    displayWeightOnLED(weight/10);

    // Print the weight to the serial monitor
    Serial.print("Weight: ");
    Serial.println(weight);
  }

  delay(1000); // Adjust the delay as needed
}

void displayWeightOnLED(int weight)
{
  // Convert negative weight to its absolute value
  weight = abs(weight);

  if (weight <= 9999)
  {
    // Split the number into digits
    int digit1 = weight % 10;
    int digit2 = (weight / 10) % 10;
    int digit3 = (weight / 100) % 10;
    int digit4 = (weight / 1000) % 10;

    // Display the digits on the 7-segment display
    uint8_t numberToPrint[] = {numberB[digit4], numberB[digit3], numberB[digit2], numberB[digit1]};
    sr.setAll(numberToPrint);

    
  }
  else
  {
    Serial.println("Weight out of range (0-9999).");
  }
}
