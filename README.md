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
* Cardboard
* Tape, rubber band, and/or any other items used to fasten items together

## Implementation

### H-Bridge DC Motor Controller
L298N is a dual H-Bridge motor driver which allows speed and direction control of two DC motors at the same time. Instead of using L298N driver, a H-Bridge was built reusing the RC Car's circuit board components. The transistors and resistors that was used in the original circuit board was soldered out. This was only done to further improve my understanding of the components and logic.

<img src="RC%20Car%20Circuit%20Board.JPG" width="420" height="270"> &nbsp;&nbsp;&nbsp;&nbsp; <img src="Temp%20H-Bridge.JPG" width="420" height="270">

The transistors and resistors were temporarily installed as a circuit on a breadboard. This H-Bridge circuit was connected to Arduino and the RC cars DC motor for testing. The logic was tested for simple commands such as moving forward, backward, left and right. Once the H-Bridge became fully functioning it was transfered ont a PCB board and soldered; making it lightweight and tidier.

<img src="H-Bridge%20Circuit.JPG" width="420" height="270">

There is 4 wires that are taped they act as the input voltage. The 4 non taped wires are output that is connected directly to two dc motors. Yellow/ Green for steering motor and Blue/ White for the main drive motor. 

### HC-SR04 Ultrasonic sensor
The ultrasonic sensor acts as the eyes for this autonomous car. The readings from the sensor is used to identify any obstacle in its path, these readings are used to compute the directional change of the car.

The HC-SR04 sensor uses 4 pins: VCC (5V), Trig (pulse out), Echo (pulse duration) and GND. Female-Male Dupont wires were used to connect the HC-SR04 pins to the Arduino board. The Trig and Echo pins were directly connected to the Arduino board. VCC and GND of the sensor is connected to a breadboard. The breadboard contains supply of the 5V in parallel circuit to power HC-SR04, ULN2003 driver and SG90 micro servo.

### 28BYJ-48 Stepper motor (with ULN2003 driver)
The stepper motor allows the HC-SR04 to take readings at multiple positions. Allowing the car to dynamically adapt to the changing environment. The stepper motor is blu tacked on the front flat surface of the car. The stepper motor contains 5 wires representing: Coil 1 (Orange), Coil 3 (Yellow), 5V (Red), Coil 4 (Blue) and Coil 2 (Pink). These pins are connected to the ULN2003 driver.

The ULN2003 driver takes in 5V and GND and this is connected to the breadboard (parallel circuit). It also, takes in 4 input pins which is used to control the coils in the stepper motor. Theses 4 pins are connected directly to the Arduino board. The input signals from the Arduino board is redirected to the stepper motor (5 wires) via the ULN2003 driver, to perform a step rotation in either direction.  

### SG90 Micro servo

### Additional changes
As the RC Car was quiet old the wires had a little tear hence, the RC car wires from motor and battery compartment was rewired.

## Performance



