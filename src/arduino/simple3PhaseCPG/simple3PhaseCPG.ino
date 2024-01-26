int pump0PwmPin = 9;
int pump1PwmPin = 10;
int pump2PwmPin = 11;

int pump0DirPin = 3;
int pump1DirPin = 4;
int pump2DirPin = 5;

bool pump0Dir = LOW;
bool pump1Dir = LOW;
bool pump2Dir = LOW;

int pump0Pwm = 0;
int pump1Pwm = 0;
int pump2Pwm = 0;

float pi = 3.14159;

float amp0 = 255;
float freq0 = 0.4; 
float phi0 = 240; 

float amp1 = 255;
float freq1 = 0.4; 
float phi1 = 120; 

float amp2 = 255;
float freq2 = 0.4; 
float phi2 = 0; 


float time = 0;

void setup() {
  pinMode(pump0PwmPin, OUTPUT);
  pinMode(pump1PwmPin, OUTPUT);
  pinMode(pump2PwmPin, OUTPUT);
  pinMode(pump0DirPin, OUTPUT);
  pinMode(pump1DirPin, OUTPUT);
  pinMode(pump2DirPin, OUTPUT);


}

void loop() {
  // compute pwms and directions for each pump
  time = millis()/1000.0;
// Compute value of pwm from shifted sin waves
  pump0Pwm = int(amp0*sin(2*pi*freq0*time + phi0*pi/180.0));
  pump1Pwm = int(amp1*sin(2*pi*freq1*time + phi1*pi/180.0));
  pump2Pwm = int(amp2*sin(2*pi*freq2*time + phi2*pi/180.0));
// grab sign of pwm
  pump0Dir = (pump0Pwm>=0);
  pump1Dir = (pump1Pwm>=0);
  pump2Dir = (pump2Pwm>=0);
  // grab magnitude of speeds
  pump0Pwm = abs(pump0Pwm);
  pump1Pwm = abs(pump1Pwm);
  pump2Pwm = abs(pump2Pwm);

  
  // assign pwm values and directions to each pump
    analogWrite(pump0PwmPin, pump0Pwm);
    digitalWrite(pump0DirPin,pump0Dir);
    analogWrite(pump1PwmPin, pump1Pwm);
    digitalWrite(pump1DirPin,pump1Dir);
    analogWrite(pump2PwmPin, pump2Pwm);
    digitalWrite(pump2DirPin,pump2Dir);

}
