# Autonomous-RC-Car

Built an Autonomous RC Car using a simple RC Car, Arduino Uno Board and some electronic components. In summary this car collects data from HC-SR04 Ultrasonic sensors. The HC-SR04 sensor is connected to either a stepper or servo motor. This acts like a radar scanning for obstacles dynamicly from left to right. As this RC Car is a rear wheel drive it only uses two motors; a motor to handle the rear wheels and another for the steering. The car moves in forward direction and whenerver it comes across an obstacle (object or wall) the program makes a decision on the direction to move based on the readings from the HC-SR04 sensor. 

## Hardware List

* Dodge Viper GTS-R - Any working RC Car
* Arduino Uno
* HC-SR04 Ultrasonic sensor
* 28BYJ-48 Stepper motor
* ULN2003 Driver - Arduino
* SG90 Micro servo
* Breadboard
* Double Sided PCB board
* 22 AWG Solid core wires - 6 Different colours
* Female-Male Dupont wires
* Male-Male Dupont wires
* Anker power bank - Any power bank/ battery that can provide 5V
* Soldering Iron and Solder
* Tape, rubber band, and/or any other items used to fasten items together

## Implementation

### H-Bridge DC Motor Controller

L298N is a dual H-Bridge motor driver which allows speed and direction control of two DC motors at the same time. Instead of using L298N driver, a H-Bridge was built reusing the RC Car's circuit board components. The transistors and resistors that was used in the original circuit board was soldered out. This was only done to further improve my understanding of the components and logic.

<div class="row">
  <div class="column">
    <img src="RC%20Car%20Circuit%20Board.JPG" width="420" height="270">
  </div>
  <div class="column">
     <img src="Temp%20H-Bridge.JPG" width="420" height="270">
  </div>
</div>

The transistors and resistors were temporarily installed as a circuit on a breadboard. This H-Bridge circuit was connected to Arduino and the RC cars DC motor for testing. The logic was tested for simple commands such as moving forward, backward, left and right. Once the H-Bridge became fully functioning it was transfered ont a PCB board and soldered; making it lightweight and tidier.

### HC-SR04 Ultrasonic sensor

### 28BYJ-48 Stepper motor with ULN2003 driver

### SG90 Micro servo

### Additional changes

As the RC Car was quiet old the wires looked a bit weak hence, the RC car wires from motor and battery compartment was rewired.

## Performance



