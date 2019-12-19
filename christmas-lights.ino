int LED1 = 10;
int LED2 = 9;
int BUTTON = 4;
int brightness = 0;    // how bright the LED is
int fadeAmount = 3;    // how many points to fade the LED by
int buttonMode = 0;
// the follow variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long time = 0;         // the last time the output pin was toggled
long debounce = 200;   // the debounce time, increase if the output flickers

// the setup routine runs once when you press reset:
void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(BUTTON, INPUT);
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  checkButton();
  lightMode();
}

void lightMode() {
  if(buttonMode == 1) {
    
    fireFlicker(LED1);
    fireFlicker(LED2);  
  }
  else {
    fade(LED1);
    fade(LED2);
  }
}

void checkButton() {
  int stateButton = digitalRead(BUTTON);
  if(stateButton == 1)
  {
    switchMode();    
  }
}

void switchMode() {
  Serial.println("mode switch attempt");
  if(millis() - time > debounce) {
    Serial.println("mode switch");
    if(buttonMode == 0) {
      buttonMode = 1;
    }
    else {
      buttonMode = 0;
    }
    Serial.println(buttonMode);
    time = millis();  
  }
  
}

void fireFlicker(int led) {
  analogWrite(led, random(120)+135);
  delay(random(100));
}

void fade(int led) {
    // set the brightness of pin 9:
  analogWrite(led, brightness);

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(10);
}
