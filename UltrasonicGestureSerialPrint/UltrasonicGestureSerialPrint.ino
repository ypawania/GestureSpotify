float duration_us, distanceCM;
int trigPin = 9;
int echoPin = 8;
int btn_in = 2;
int volumeLED = 3;
bool toggleVolume;
int volume;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // configure the trigger pin to output mode
  pinMode(trigPin, OUTPUT);
  // configure the echo pin to input mode
  pinMode(echoPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(btn_in, INPUT);
  pinMode(volumeLED, OUTPUT);
}


void loop() {
  // put your main code here, to run repeatedly:
  distanceCM = distance();
  if (digitalRead(btn_in) == HIGH){
    toggleVolume = !toggleVolume;
    delay(400);
  }
  if (toggleVolume == false){
    digitalWrite(volumeLED, LOW);
    if (distanceCM < 40 && distanceCM > 20){
      digitalWrite(LED_BUILTIN, HIGH);
      delay(1000);
      distanceCM = distance();
      
      if (distanceCM < 20 && distanceCM > 2){
        Serial.println('1');
      }
      else if (distanceCM < 40 && distanceCM > 20){
        Serial.println('3');
      }
    }
    if (distanceCM < 10){
      delay(1000);
      distanceCM = distance();
      if (distanceCM > 10 && distanceCM < 60){
        Serial.println('2');
      }
      else if (distanceCM < 10){
        Serial.println('4');
      }
    }
  }
  else if (toggleVolume == true){
    digitalWrite(volumeLED, HIGH);
    volume = map(distanceCM, 4, 40, 5, 100);
    if (volume < 5){volume = 5;}
    else if (volume>100){volume=100;}
    Serial.println(volume);
    delay(600);
  }

}
float distance() {
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(echoPin, HIGH);
  // calculate the distance
  distanceCM = 0.017 * duration_us;
  digitalWrite(LED_BUILTIN, LOW);
  return distanceCM;
}



