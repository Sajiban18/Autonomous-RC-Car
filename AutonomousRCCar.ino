#include <AccelStepper.h>
#define HALFSTEP 8  //Half-step mode (8 step control signal sequence)

// Motor pin definitions
#define mtrPin1  10     // IN1 on the ULN2003 driver 1
#define mtrPin2  11     // IN2 on the ULN2003 driver 1
#define mtrPin3  12     // IN3 on the ULN2003 driver 1
#define mtrPin4  13     // IN4 on the ULN2003 driver 1

//Forward & Backward Motor Pins
int FB1 = 7;
int FB2 = 6;

//Left & Right Motor Pins 
int LR1 = 5;
int LR2 = 4;

//UltraSonic Sensor Pins
int USTrig = 9;
int USEcho = 8;

long duration;
int distance;
int distances[5] = {150, 150, 150, 150, 150};
int objectDistance = 7; 
bool firstScanComplete = false;

AccelStepper stepper1(HALFSTEP, mtrPin1, mtrPin3, mtrPin2, mtrPin4);

void forward() {
  digitalWrite(FB1, HIGH);
  digitalWrite(FB2, LOW);
  digitalWrite(LR1, LOW);
  digitalWrite(LR2, LOW);
}

void backward() {
  digitalWrite(FB1, LOW);
  digitalWrite(FB2, HIGH);
  digitalWrite(LR1, LOW);
  digitalWrite(LR2, LOW);
}

void applyBreak() {
  digitalWrite(FB1, LOW);
  digitalWrite(FB2, LOW);
  digitalWrite(LR1, LOW);
  digitalWrite(LR2, LOW);
}

void leftForward(int turn) {
  digitalWrite(FB1, HIGH);
  digitalWrite(FB2, LOW);
  analogWrite(LR1, turn);
  digitalWrite(LR2, LOW);
}

void rightForward(int turn) {
  digitalWrite(FB1, HIGH);
  digitalWrite(FB2, LOW);
  digitalWrite(LR1, LOW);
  analogWrite(LR2, turn);
}

void leftBackward() {
  digitalWrite(FB1, LOW);
  digitalWrite(FB2, HIGH);
  digitalWrite(LR1, HIGH);
  digitalWrite(LR2, LOW);
}

void rightBackward() {
  digitalWrite(FB1, LOW);
  digitalWrite(FB2, HIGH);
  digitalWrite(LR1, LOW);
  digitalWrite(LR2, HIGH);
}

int calculateDistance() {
  digitalWrite(USTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(USTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(USTrig, LOW);

  duration = pulseIn(USEcho, HIGH);
  return duration*0.0343/2;
}

void directionChoice() {
  if((distances[0] + distances[1]) > (distances[3] + distances[4])) {
    leftForward(255);
    //Serial.println("LeftForward");
    //delay(90);
  } else if((distances[0] + distances[1]) < (distances[3] + distances[4])){
    rightForward(255);
    //Serial.println("RightForward");
    //delay(90);
  } else {
    int choice = rand() % 10 + 1;
    choice % 2 == 0 ? leftForward(255) : rightForward(255);
    //Serial.println("Random");
  }
}

void checkCurrentPosition() {
  if(stepper1.currentPosition() == -340) {
    distances[0] = calculateDistance();
    firstScanComplete = true;
  } 
  if(stepper1.currentPosition() == -225)
    distances[1] = calculateDistance();
  if(stepper1.currentPosition() == 0)
    distances[2] = calculateDistance();
  if(stepper1.currentPosition() == 225)
    distances[3] = calculateDistance();
  if(stepper1.currentPosition() == 340)
    distances[4] = calculateDistance();
}


void setup() {
  Serial.begin(9600);
  stepper1.setMaxSpeed(1000.0);
  stepper1.setAcceleration(500.0);  //Make the acc quick
  stepper1.setSpeed(500.0);
  stepper1.moveTo(4096/12);  //Rotate 1 revolution 4096/2

  pinMode(FB1, OUTPUT);
  pinMode(FB2, OUTPUT);
  
  pinMode(LR1, OUTPUT);
  pinMode(LR2, OUTPUT);
  
  pinMode(USTrig, OUTPUT);
  pinMode(USEcho, INPUT);
}

void loop() {
  //Change direction when the stepper reaches the target position
  if(stepper1.distanceToGo() == 0) {
    stepper1.moveTo(-stepper1.currentPosition());  //Reverse motor
  }
  stepper1.run();  //Start

  //Store distances of data in distances array 
  checkCurrentPosition();

  if(firstScanComplete) {
    if(distances[0] < objectDistance || distances[1] < objectDistance || distances[2] < objectDistance || distances[3] < objectDistance || distances[4] < objectDistance) {
      //Object in Front but not on Left or Right
      if(distances[0] >= objectDistance && distances[1] >= objectDistance && distances[2] < objectDistance && distances[3] >= objectDistance && distances[4] >= objectDistance) {
        applyBreak();
        //delay(500);
        directionChoice();
      }

      //Object onRight
      if((distances[0] >= objectDistance && distances[1] >= objectDistance && distances[2] >= objectDistance) && (distances[3] < objectDistance || distances[4] < objectDistance)) {
        if(distances[4] < objectDistance) {
          leftForward(165);
          //Serial.println("leftForward1");
          //delay(45);
        } else {
          leftForward(255);
          //Serial.println("leftForward2");
          //delay(90);
        }
      } 
    
      if((distances[0] >= objectDistance && distances[1] >= objectDistance && distances[2] < objectDistance) && (distances[3] < objectDistance || distances[4] < objectDistance)) {
        rightBackward();
        //Serial.println("rightBackward");
        //delay(90);
      }
  
      //Object onLeft
      if((distances[4] >= objectDistance && distances[3] >= objectDistance && distances[2] >= objectDistance) && (distances[0] < objectDistance || distances[1] < objectDistance)) {
        if(distances[0] < objectDistance) {
          rightForward(165);
          //Serial.println("rightForward1");
          //delay(45);
        } else {
          rightForward(255);
          //Serial.println("rightForward2");
          //delay(90);
        }
      } 
      
      if((distances[4] >= objectDistance && distances[3] >= objectDistance && distances[2] < objectDistance) && (distances[0] < objectDistance || distances[1] < objectDistance)) {
        leftBackward();
        //Serial.println("leftBackward");
        //delay(90);
      }
  
      // Fully blocked at the front left and right
      if((distances[0] < objectDistance && distances[1] < objectDistance && distances[2] < objectDistance && distances[3] < objectDistance && distances[4] < objectDistance)
      || (distances[0] >= objectDistance && distances[1] < objectDistance && distances[2] < objectDistance && distances[3] < objectDistance && distances[4] >= objectDistance)) {
        //stepper1.moveTo(0);
        applyBreak();
        //delay(500);
        while(distances[1] < objectDistance && distances[2] < objectDistance && distances[3] < objectDistance) {
          backward();
          //Serial.println("Backward");
        }
        applyBreak();
        directionChoice();
      }  
    } else {
      forward();
      //Serial.println("Forward");
    }
  }
}
