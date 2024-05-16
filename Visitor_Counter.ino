#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
 
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
//#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW
 
#define MAX_DEVICES 4
#define CS_PIN 10
#define CLK_PIN 13 
#define DIN_PIN 11
 
MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
 int count = 0;

long readUltrasonicDistance(int triggerPin, int echoPin)
{

  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}
void setup() {
  Serial.begin(9600);
  myDisplay.begin();
  myDisplay.setIntensity(4);
  myDisplay.displayClear(1);
  myDisplay.displayScroll("",PA_CENTER, PA_SCROLL_LEFT, 200);
  
  
}
 
void loop() {
 
  
   if (0.01723 * readUltrasonicDistance(2, 3) < 100) {
    count = (count + 1);
    Serial.print("Car Enter ");
    Serial.println(count); 
    myDisplay.print(count);  
    delay(3500); // Wait for 3500 millisecond(s)
  }
  if (0.01723 * readUltrasonicDistance(4, 5) < 100) {
    count = (count - 1);
    Serial.print(" Car Left ");
    Serial.println(count);
     myDisplay.print(count);  
    delay(3500); // Wait for 3500 millisecond(s)
    }
 
}