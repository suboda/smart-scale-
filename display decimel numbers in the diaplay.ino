#include <ShiftRegister74HC595.h>

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
}

void loop()
{
  if (Serial.available() > 0)
  {
    // Read the floating-point value from the serial monitor
    float inputValue = Serial.parseFloat();

    // Print the received value
    Serial.print("Received: ");
    Serial.println(inputValue);

    // Display the digits on the 7-segment display
    printFloat(inputValue);
  }

  delay(1000); // Adjust the delay as needed
}

void printFloat(float value)
{
  int intValue;

  if (value < 10)
  {
    intValue = (int)(value * 1000);
    printDigit(intValue);
    sr.set(7, 0);
  }
  else if (value < 100)
  {
    intValue = (int)(value * 100);
    printDigit(intValue);
    sr.set(15, 0);
  }
  else if (value < 1000)
  {
    intValue = (int)(value * 10);
    printDigit(intValue);
    sr.set(23, 0);
  }
  else
  {
    intValue = (int)(value);
    printDigit(intValue);
  }
}

void printDigit(int value)
{
  int d4, d3, d2, d1;

  d4 = value % 10;
  value = value / 10;
  d3 = value % 10;
  value = value / 10;
  d2 = value % 10;
  value = value / 10;
  d1 = value % 10;

  uint8_t numberToPrintOne[] = {numberB[d1], numberB[d2], numberB[d3], numberB[d4]};
  sr.setAll(numberToPrintOne);
}
