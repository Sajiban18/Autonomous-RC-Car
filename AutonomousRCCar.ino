#include <AccelStepper.h>
#include <NewPing.h>
#define HALFSTEP 8  //Half-step mode (8 step control signal sequence)

// Motor pin definitions
#define mtrPin1  10     //IN1 on the ULN2003 driver 1
#define mtrPin2  11     //IN2 on the ULN2003 driver 1
#define mtrPin3  12     //IN3 on the ULN2003 driver 1
#define mtrPin4  13     //IN4 on the ULN2003 driver 1

//Accel Stepper function is used for stepper motor
AccelStepper stepper1(HALFSTEP, mtrPin1, mtrPin3, mtrPin2, mtrPin4);

//Forward & Backward Motor Pins
int FB1 = 9;
int FB2 = 6;

//Left & Right Motor Pins 
int LR1 = 5;
int LR2 = 3;

//UltraSonic Sensor Pins
int USTrig = 7;
int USEcho = 8;
int maxDist = 350;

NewPing sonar(USTrig, USEcho, maxDist);

long duration;
int distance;

// Distance will be updated at first scan
int distances[5] = {150, 150, 150, 150, 150}; 
bool scanComplete = false;

//Distance to keep from object
int objectDistance = 25; 

//Forward/ Backward Speed 0 - 255 (0V - 5V) PWM
int forwardSpeed = 125;
int backwardSpeed = 125;



void forward() {
  analogWrite(FB1, forwardSpeed);
  digitalWrite(FB2, LOW);
  digitalWrite(LR1, LOW);
  digitalWrite(LR2, LOW);
}

void backward() {
  digitalWrite(FB1, LOW);
  analogWrite(FB2, backwardSpeed);
  digitalWrite(LR1, LOW);
  digitalWrite(LR2, LOW);
}

void applyBreak() {
  digitalWrite(FB1, LOW);
  digitalWrite(FB2, LOW);
  digitalWrite(LR1, LOW);
  digitalWrite(LR2, LOW);
}

void leftForward(int turnAmount) {
  analogWrite(FB1, forwardSpeed);
  digitalWrite(FB2, LOW);
  analogWrite(LR1, turnAmount);
  digitalWrite(LR2, LOW);
}

void rightForward(int turnAmount) {
  analogWrite(FB1, forwardSpeed);
  digitalWrite(FB2, LOW);
  digitalWrite(LR1, LOW);
  analogWrite(LR2, turnAmount);
}

void leftBackward() {
  digitalWrite(FB1, LOW);
  analogWrite(FB2, backwardSpeed);
  digitalWrite(LR1, HIGH);
  digitalWrite(LR2, LOW);
}

void rightBackward() {
  digitalWrite(FB1, LOW);
  analogWrite(FB2, backwardSpeed);
  digitalWrite(LR1, LOW);
  digitalWrite(LR2, HIGH);
}

int calculateDistance(int msTime) {
//  digitalWrite(USTrig, LOW);
//  delayMicroseconds(2);
//  digitalWrite(USTrig, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(USTrig, LOW);
//
//  duration = pulseIn(USEcho, HIGH, msTime);
//  return duration*0.034/2;

  //return sonar.ping_cm();
  return sonar.convert_cm(sonar.ping_median(2)); 
}

void printDistance() {
   Serial.print("[ ");
   Serial.print(distances[0]);
   Serial.print(" , ");
   Serial.print(distances[1]);
   Serial.print(" , ");
   Serial.print(distances[2]);
   Serial.print(" , ");
   Serial.print(distances[3]);
   Serial.print(" , ");
   Serial.print(distances[4]);
   Serial.print(" ]");
   Serial.println();
}

//Checks which side of the car is open to pass through, if they are equal than the direction is randomly chosen
void directionChoice() {
  if((distances[0] + distances[1]) > (distances[3] + distances[4])) {
    leftForward(255);
  } else if((distances[0] + distances[1]) < (distances[3] + distances[4])){
    rightForward(255);
  } else {
    int choice = rand() % 10 + 1;
    choice % 2 == 0 ? leftForward(255) : rightForward(255);
  }
}

int usErrorCheck(int dst) {
  return dst != 0 ? dst : 150;
}

void checkCurrentPosition() {
  if(stepper1.currentPosition() == -1024) {
    distances[0] = usErrorCheck(calculateDistance(40000));
    scanComplete = true;
    printDistance();
  } 
  
  if(stepper1.currentPosition() == -512) {
    distances[1] = usErrorCheck(calculateDistance(87500));
    printDistance();
  }
    
  if(stepper1.currentPosition() == 0) {
    distances[2] = usErrorCheck(calculateDistance(100000));
    printDistance();
  }
  
  if(stepper1.currentPosition() == 512) {
    distances[3] = usErrorCheck(calculateDistance(87500));
    printDistance();
  }
  
  if(stepper1.currentPosition() == 1024) {
    distances[4] = usErrorCheck(calculateDistance(40000));
    printDistance();
  }
}


void setup() {
  Serial.begin(9600);
  stepper1.setMaxSpeed(1250.0);
  stepper1.setAcceleration(450.0);  //Make the acc quick
  //stepper1.setSpeed(500.0);
  stepper1.moveTo(4096/4);  //Rotate 1 revolution 4096/2

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

//  if(scanComplete) {
//    if(distances[0] < objectDistance || distances[1] < objectDistance || distances[2] < objectDistance || distances[3] < objectDistance || distances[4] < objectDistance) {
//      //Object in Front but not on Left or Right
//      if(distances[0] >= objectDistance && distances[1] >= objectDistance && distances[2] < objectDistance && distances[3] >= objectDistance && distances[4] >= objectDistance) {
//        //applyBreak();
//        directionChoice();
//      }
//
//      //Object onRight
//      if((distances[0] >= objectDistance && distances[1] >= objectDistance && distances[2] >= objectDistance) && (distances[3] < objectDistance || distances[4] < objectDistance)) {
//        if(distances[4] < objectDistance) {
//          //applyBreak();
//          leftForward(165);
//        } else {
//          //applyBreak();
//          leftForward(255);
//        }
//      } 
//    
//      if((distances[0] >= objectDistance && distances[1] >= objectDistance && distances[2] < objectDistance) && (distances[3] < objectDistance || distances[4] < objectDistance)) {
//        //applyBreak();
//        rightBackward();
//      }
//  
//      //Object onLeft
//      if((distances[4] >= objectDistance && distances[3] >= objectDistance && distances[2] >= objectDistance) && (distances[0] < objectDistance || distances[1] < objectDistance)) {
//        if(distances[0] < objectDistance) {
//          //applyBreak();
//          rightForward(165);
//        } else {
//          //applyBreak();
//          rightForward(255);
//        }
//      } 
//      
//      if((distances[4] >= objectDistance && distances[3] >= objectDistance && distances[2] < objectDistance) && (distances[0] < objectDistance || distances[1] < objectDistance)) {
//        //applyBreak();
//        leftBackward();
//      }
//  
//      // Fully blocked at the front left and right
//      if((distances[0] < objectDistance && distances[1] < objectDistance && distances[2] < objectDistance && distances[3] < objectDistance && distances[4] < objectDistance)
//      || (distances[0] >= objectDistance && distances[1] < objectDistance && distances[2] < objectDistance && distances[3] < objectDistance && distances[4] >= objectDistance)) {
//        //stepper1.moveTo(0);
//        //applyBreak();
//        if(distances[1] < objectDistance && distances[2] < objectDistance && distances[3] < objectDistance) {
//          backward();
//        }
//        //applyBreak();
//        directionChoice();
//      }  
//    } else {
//      forward();
//    }
//  }
}
