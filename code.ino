#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

const int speakerPin = 10;

// Define the keypad buttons and their corresponding frequencies
const byte numRows = 4;
const byte numCols = 4;
char keymap[numRows][numCols] = {
   {'1', '2', '3','A'},
  {'4', '5', '6','B'},
  {'7', '8', '9','C'},
  {'*', '0', '#','D'}
};
float frequencies[numRows][numCols] = {
  {261.63, 293.66, 329.63,0.00},
  {349.23, 392.00, 440.00,0.00},
  {493.88, 523.25, 587.33,0.00},
  {0.00, 0.00, 0.00,0.00}
};

// Define the LCD display
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define the keypad and its pins
byte rowPins[numRows] = {2, 3, 4, 5};
byte colPins[numCols] = {6, 7, 8,9};
Keypad keypad = Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

// Define the Bluetooth module
SoftwareSerial bluetooth(11, 12); // RX, TX

void setup() {
  pinMode(speakerPin, OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.print("Enter a frequency:");
  Serial.begin(9600);
  bluetooth.begin(9600);
}

void loop() {
  // Check for Bluetooth input
  if (BTserial.available()) { // If data is available from Bluetooth
    char c = BTserial.read(); 
    if (c == '1') { // If '1' is received, turn on LED
      tone(speakerPin, frequency);
      Serial.println("1");
    // Read the data
          tone(speakerPin, frequency);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Frequency:");
          lcd.setCursor(0, 1);
          lcd.print(frequency);
          delay(500);
          noTone(speakerPin);
        }
      }
    }
  }
  
  // Check for keypad input
  char key = keypad.getKey();
  if (key != NO_KEY) {
    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numCols; j++) {
        if (keymap[i][j] == key) {
          float frequency = frequencies[i][j];
          tone(speakerPin, frequency);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Frequency:");
          lcd.setCursor(0, 1);
          lcd.print(frequency);
          delay(500);
          noTone(speakerPin);
          bluetooth.print(keymap[i][j]);
        }
      }
    }
  }
  
  // Check for incoming serial data
  if (Serial.available()) {
    char incoming = Serial.read();
    if (incoming == 'A') {
      bluetooth.print("A");
      bluetooth;
    }
  }
