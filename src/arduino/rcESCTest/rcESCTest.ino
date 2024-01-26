#include <Servo.h>

Servo ESC;     // create servo object to control the ESC

int potValue;  // value from the analog pin

int pos = 0;    // variable to store the servo position

float pi = 3.14159;
float time = 0; // internal time for generating sinusoids

int pump0Pwm = 0;  // PWM signal for pwmp

float amp0 = 1000; // amplitude of sinusoid (1000 is max, 0 is min)
float freq0 = 1; // frequency of sinusoid in Hz
float phi0 = 0;  // phase of sinusoid (in degrees)


void initESC(){
/*
Initializes ESC to start running
*/
 ESC.write(180);
 Serial.print("Writing High");
  delay(2000);

  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    ESC.write(pos);              // tell servo to go to position in variable 'pos'
    Serial.println(pos);
    delay(15);                       // waits 15 ms for the servo to reach the position
  }

}
void setup() {
  // Attach the ESC on pin 9
  ESC.attach(9,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 
  Serial.begin(9600);

  initESC();

}

void loop() {

  // compute pwms and directions for each pump
  time = millis()/1000.0;
// Compute value of pwm from shifted sin waves
  pump0Pwm = int(amp0*sin(2*pi*freq0*time + phi0*pi/180.0));

// Remap PWM signal for servo library
pump0Pwm = int(map(pump0Pwm,-1000,1000,0,180));
Serial.println(pump0Pwm);

// Write PWM signal
ESC.write(pump0Pwm);

delay(1);


}
