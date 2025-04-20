
#include <SoftwareSerial.h>

SoftwareSerial sim(4, 5); // SIM800L Tx & Rx
SoftwareSerial gpsSerial(12, 13); // GPS Tx & Rx

#define BUTTON_PIN D1

void setup() {
  Serial.begin(9600);
  sim.begin(9600);
  gpsSerial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {
    String gpsData = "";
    while (gpsSerial.available()) {
      char c = gpsSerial.read();
      gpsData += c;
    }
    Serial.println("Sending SMS...");
    sim.println("AT+CMGF=1"); // Set SMS mode
    delay(100);
    sim.println("AT+CMGS=\"+911234567890\""); // Replace with your number
    delay(100);
    sim.print("Bus has arrived. Location:\n");
    sim.print(gpsData);
    sim.write(26); // End SMS with Ctrl+Z
    delay(1000);
  }
}
