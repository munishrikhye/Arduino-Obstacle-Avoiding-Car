// Define motor control pins
// ENA and ENB are PWM pins to control motor speed
// IN1, IN2 control the first motor direction
// IN3, IN4 control the second motor direction
// Pins assignment:
// 10 = ENA (Motor A speed control)
// 6  = IN1 (Motor A direction)
// 7  = IN2 (Motor A direction)
// 5  = IN3 (Motor B direction)
// 4  = IN4 (Motor B direction)
// 3  = ENB (Motor B speed control)

#include <Servo.h> // Include Servo library to control the servo motor

Servo myServo; // Create a Servo object
long duration; // Variable to store the time it takes for ultrasonic pulse to return
int distance;  // Variable to store the calculated distance in cm

// Define ultrasonic sensor pins
#define TRIG 11 // Trigger pin of ultrasonic sensor
#define ECHO 8  // Echo pin of ultrasonic sensor

void setup() {
  // Initialize serial communication at 9600 baud
  Serial.begin(9600);

  // Set ultrasonic sensor pins
  pinMode(TRIG, OUTPUT); // TRIG pin will send pulses
  pinMode(ECHO, INPUT);  // ECHO pin will receive pulses

  // Set motor pins as OUTPUT
  pinMode(10, OUTPUT); // ENA
  pinMode(6, OUTPUT);  // IN1
  pinMode(7, OUTPUT);  // IN2
  pinMode(3, OUTPUT);  // ENB
  pinMode(5, OUTPUT);  // IN3
  pinMode(4, OUTPUT);  // IN4

  // Set both motors to move forward initially
  digitalWrite(6, HIGH); // Motor A IN1 HIGH
  digitalWrite(7, LOW);  // Motor A IN2 LOW
  digitalWrite(5, HIGH); // Motor B IN3 HIGH
  digitalWrite(4, LOW);  // Motor B IN4 LOW

  // Turn on motors at full speed
  digitalWrite(10, HIGH); // ENA HIGH -> Motor A ON
  digitalWrite(3, HIGH);  // ENB HIGH -> Motor B ON

  // Print message to serial monitor
  Serial.println("Robot started");
}

void loop() {

  myServo.attach(9); // Attach the servo motor to pin 9

  for (int angle = 0; angle <130; angle+=15){
  
  myServo.write(angle);



  // Ultrasonic distance measurement
  digitalWrite(TRIG, LOW);           // Ensure TRIG is LOW
  delayMicroseconds(2);              // Short delay
  digitalWrite(TRIG, HIGH);          // Send ultrasonic pulse
  delayMicroseconds(10);             // Pulse duration
  digitalWrite(TRIG, LOW);           // Stop pulse

  // Read the echo time (duration for pulse to return)
  duration = pulseIn(ECHO, HIGH);

  // Convert duration to distance in cm
  distance = duration * 0.034 / 2;

  // Print distance to serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Check for obstacles closer than 10 cm
  if (distance > 0 && distance <= 10) {
    // Stop both motors if obstacle detected
    digitalWrite(10, LOW); // Motor A OFF
    digitalWrite(3, LOW);  // Motor B OFF
    Serial.println("Obstacle detected — Motors STOP");
  } else {
    // Otherwise, keep motors moving forward
    digitalWrite(6, HIGH); // Motor A IN1 HIGH
    digitalWrite(7, LOW);  // Motor A IN2 LOW
    digitalWrite(5, HIGH); // Motor B IN3 HIGH
    digitalWrite(4, LOW);  // Motor B IN4 LOW

    digitalWrite(10, HIGH); // Motor A ON
    digitalWrite(3, HIGH);  // Motor B ON
  }
  
  delay(500); // Wait 0.5 seconds before next loop iteration
  }
  myServo.write(0);
}
