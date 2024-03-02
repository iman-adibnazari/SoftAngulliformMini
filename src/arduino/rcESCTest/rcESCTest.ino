#include <Servo.h>

Servo ESC0;     // create servo object to control the ESC
Servo ESC1;     // create servo object to control the ESC
Servo ESC2;     // create servo object to control the ESC

int potValue;  // value from the analog pin

int pos = 0;    // variable to store the servo position

float pi = 3.14159;
float time = 0; // internal time for generating sinusoids

int pump0Pwm = 0;  // PWM signal for pwmp
int pump1Pwm = 0;  // PWM signal for pwmp
int pump2Pwm = 0;  // PWM signal for pwmp

float amp0 = 500; // amplitude of sinusoid (1000 is max, 0 is min)
float freq0 = 0.5; // frequency of sinusoid in Hz
float phi0 = 0;  // phase of sinusoid (in degrees)

float amp1 = 500; // amplitude of sinusoid (1000 is max, 0 is min)
float freq1 = 0.5; // frequency of sinusoid in Hz
float phi1 = 120;  // phase of sinusoid (in degrees)

float amp2 = 500; // amplitude of sinusoid (1000 is max, 0 is min)
float freq2 = 0.5; // frequency of sinusoid in Hz
float phi2 = 240;  // phase of sinusoid (in degrees)


void initESCs(){
/*
Initializes ESC to start running
*/
 ESC0.write(180);
 ESC1.write(180);
 ESC2.write(180);
 Serial.print("Writing High");
  delay(1000);

  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    ESC0.write(pos);              // tell servo to go to position in variable 'pos'
    ESC1.write(pos);              // tell servo to go to position in variable 'pos'
    ESC2.write(pos);              // tell servo to go to position in variable 'pos'
    Serial.println(pos);
    delay(5);                       // waits 15 ms for the servo to reach the position
  }

 ESC0.write(90);
 ESC1.write(90);
 ESC2.write(90);

  

  delay(500);

}
void setup() {
  // Attach the ESC on pin 9
  ESC0.attach(9,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 
  ESC1.attach(6,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 
  ESC2.attach(5,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 
  Serial.begin(9600);

  initESCs();

}

void loop() {

  // compute pwms and directions for each pump
  time = millis()/1000.0;
// Compute value of pwm from shifted sin waves
  pump0Pwm = int(amp0*sin(2*pi*freq0*time + phi0*pi/180.0));
  pump1Pwm = int(amp1*sin(2*pi*freq1*time + phi1*pi/180.0));
  pump2Pwm = int(amp2*sin(2*pi*freq2*time + phi2*pi/180.0));

// Remap PWM signal for servo library
pump0Pwm = int(map(pump0Pwm,-1000,1000,0,180));
pump1Pwm = int(map(pump1Pwm,-1000,1000,0,180));
pump2Pwm = int(map(pump2Pwm,-1000,1000,0,180));
Serial.println(pump0Pwm);

// Write PWM signal
ESC0.write(pump0Pwm);
ESC1.write(pump1Pwm);
ESC2.write(pump2Pwm);

delay(1);


}
