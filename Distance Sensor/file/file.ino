const int trig = 7;
const int echo = 8;

// safety pins
const int pin1 = 3;
const int pin2 = 4;
const int pin3 = 5;
const int pin4 = 6;
const int buzzer = 12; 

void setup() {
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  // initialize safety pins
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  // establish variables for duration of the ping, and the distance result
  long duration, cm;

  // set all lights to low
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, LOW);
  digitalWrite(pin4, LOW);
  digitalWrite(buzzer, LOW);

  // make it low for 2sec to remove all noise and release a clean 10s high
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10); // the sensor needs 10 microseconds before it recognises it and sends out 8 bursts
  digitalWrite(trig, LOW);

  // time how long it took for the sound wave to travel and come back
  duration = pulseIn(echo, HIGH);

  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);

  // check if obj is too close
  if (cm < 5)
  {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, HIGH);
    digitalWrite(pin3, HIGH);
    digitalWrite(pin4, HIGH);
    digitalWrite(buzzer, HIGH);
  }
  else if (cm < 10)
  {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, HIGH);
    digitalWrite(pin3, HIGH);
    digitalWrite(buzzer, HIGH);
  }
  else if (cm < 15)
  {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, HIGH);
  }
  else if (cm < 20)
  {
    digitalWrite(pin1, HIGH);
  }
  else 
  {
    // all lights are off
  }



  // print distance
  Serial.print(cm);
  Serial.println("cm");
  delay(100);
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}
