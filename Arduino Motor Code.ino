// connect motor controller pins to Arduino digital pins

// motor one connections
int E1 = 10;                  // J2 PIN 3
int in1 = 11;                 // J2 PIN 2
int in2 = 12;                 // J2 PIN 4
int csA = A0;                 // J2 PIN 1     

// motor two connections 
int E2 = 2;                   // J2 PIN 6
int in3 = 3;                  // J2 PIN 5
int in4 = 4;                  // J2 PIN 7
int csB = A1;                 // J2 PIN 8

// counter pin 
int counter = 5;              // J3 COUNTER -VE

// ratio between current and voltage
double currentFactor = 2/1;   // output of 1V per 2A

void setup() {
  // set all the motor control pins to outputs
  pinMode(E1, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(E2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(counter, OUTPUT);
}

void MotorsForward() {
  // Arduino sends a low signal to counter at the beginning of the cycle
  digitalWrite(counter, LOW);
  
  // set speeds and directions of motor terminal A and motor terminal B for three seconds`
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(E1, 255);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(E2, 255);
}  
void Brake() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(E1, 0);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(E2, 0);
  delay(1000);
}

void MotorsBackward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(E1, 255);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(E2, 255); 
}

void FinishCycle(){
  Brake();
  delay(500);
  digitalWrite(counter, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  MotorsForward();
  double currentVB = map(analogRead(csB), 0, 1024, 0, 5000)/1000;
  double currentB = currentVB*currentFactor;
  double currentVA = map(analogRead(csA), 0, 1024, 0, 5000)/1000;
  double currentA = currentVA*currentFactor;
  if (currentA > 1.5 || currentB > 1.5){
    exit(1);
  }
  delay(3000);

  Brake();
  
  MotorsBackward();
  double RevcurrentVB = map(analogRead(csB), 0, 1024, 0, 5000)/1000;
  double RevcurrentB = RevcurrentVB*currentFactor;
  double RevcurrentVA = map(analogRead(csA), 0, 1024, 0, 5000)/1000;
  double RevcurrentA = RevcurrentVA*currentFactor;
  if (RevcurrentA > 1.5 || RevcurrentB > 1.5){
    exit(1);
  }  
  delay(3000);  

  FinishCycle();
  delay(500);

}
