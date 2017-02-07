#include <wiringPi.h>

// Pin that button press will be read from
#define BUTTON_PIN 26
#define UP -1
#define DOWN 1


//////// VARIABLES //////////

int ledPins[8] = {21,22,23,24,25,27,28,29};
int numOfLEDs = 8;
int topLED = 0;
int bottomLED = 7;
int currentLED = 0;
volatile int direction = 1;


///////// FUNCTIONS //////////

/* Interrupt function that changes direction LEDs light up
by increasing the direction flag */
void changeDirection() {
  direction = direction * -1; 
}



///////// MAIN //////////

int main (void) {

  wiringPiSetup();

  // Declaring Pin Modes
  int pinToSetMode = 0;
  for (; pinToSetMode < numOfLEDs; pinToSetMode++) {
    pinMode (ledPins[pinToSetMode], OUTPUT);
  }
  pinMode (BUTTON_PIN, INPUT);

  // Setting up changeDirection function as interrupt 
  wiringPiISR (BUTTON_PIN, INT_EDGE_RISING, &changeDirection);

  // Light LEDs in direction based on direction flag
  while(1) {

    digitalWrite(ledPins[currentLED],HIGH); delay(250);
    digitalWrite(ledPins[currentLED],LOW); delay(250);
    
    if (currentLED == topLED && direction == UP) {
      currentLED = bottomLED;
    } else if (currentLED == bottomLED && direction == DOWN) {
      currentLED = topLED;
    } else {
      currentLED += direction;  
    }

  }
  return 0;
}


  