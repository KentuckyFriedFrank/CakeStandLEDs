// This is a demonstration on how to use an input device to trigger changes on your neo pixels. 
// You should wire a momentary push button to connect from ground to a digital IO pin. When you 
// press the button it will change to a new pixel animation. Note that you need to press the 
// button once to start the first animation! 
 
#include <Adafruit_NeoPixel.h> 
 
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.  
 
 
#include <avr/power.h>  
 
 
#endif  
 
///////AnimationButton/////// 
#define BUTTON_PIN_1 2 // Digital IO pin connected to the button2.  
int animationState = 0; // hold which Animation State is current 
int maxAnimationState = 9; //how many different animations 
bool oldAnimationState = LOW; 
 
///////ColorButton/////// 
#define BUTTON_PIN_2 7 // Digital IO pin connected to the button1. 
int colorState = 0; // holds which Color State is current 
#define maxColorSate 20 // how many different colors will be 
bool oldColorState = LOW; 
 
int currentPixel = 0; 
uint32_t color = 0; 
int offset = 0; 
 
///////POT/////// 
#define POT_PIN 10
#define PIXEL_PIN 3 // Digital IO pin connected to the NeoPixels. 
#define PIXEL_COUNT 40 
 
// Parameter 1 = number of pixels in strip, neopixel stick has 8 
// Parameter 2 = pin number (most are valid) 
// Parameter 3 = pixel type flags, add together as needed: 
// NEO_RGB Pixels are wired for RGB bitstream 
// NEO_GRB Pixels are wired for GRB bitstream, correct for neopixel stick 
// NEO_KHZ400 400 KHz bitstream (e.g. FLORA pixels) 
// NEO_KHZ800 800 KHz bitstream (e.g. High Density LED strip), correct for neopixel stick 

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN);  


 
 
void setup() { 
  //Serial.begin(9600); 
  // delay(5000); 
  pinMode(BUTTON_PIN_1, INPUT_PULLUP); 
  pinMode(BUTTON_PIN_2, INPUT_PULLUP); 
  #ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.  
   
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);  
   
  #endif  
  strip.begin(); 
  strip.show(); // Initialize all pixels to 'off' 
} 
 
void loop() { 
  getAnimationButtonState(); 
  getColorButtonState(); 
  // setLEDBrightness(): 
  
  //    Serial.print("animationState: ");Serial.println(animationState); 
  //    Serial.print("colorState: ");Serial.println(colorState);     
  //    Serial.print("color: ");Serial.println(color); 
  //    Serial.print("currentPixel: ");Serial.println(currentPixel);     
  //    Serial.print("offset: ");Serial.println(offset);     
  //    Serial.println(); 
  
  showLEDs(); 
} 
  
   
   
void showLEDs(){ 
  setColor(); 
  setAnimation(); 
} 
 
 
 
 
void setColor(){ 
  switch(colorState){ 
    case 0: color = strip.Color(199, 21, 133); // Pink 
      break; 
    case 1: color = strip.Color(255, 0, 0); // Red 
      break; 
    case 2: color = strip.Color(0, 255, 0); // Green 
      break; 
    case 3: color = strip.Color(0, 0, 255); // Blue 
      break; 
    case 4: color = strip.Color(127, 127, 127); // White 
      break; 
    case 5: color = strip.Color(47,79,79); // dark slate gray 
      break; 
    case 6: color = strip.Color(255, 48, 48); // firebrick1 
      break; 
    case 7: color = strip.Color(139, 54, 38); // tomato4 
      break; 
    case 8: color = strip.Color(139, 0, 129); // darkmagenta 
      break; 
    case 9: color = strip.Color(255, 185, 15); // darkgoldenrod1 
      break; 
    case 10: color = strip.Color(255, 255, 0); // yellow 
      break; 
    case 11: color = strip.Color(0, 255, 127); // springgreen1 
      break; 
    case 12: color = strip.Color(0, 255, 255); // cyan 
      break; 
    case 13: color = strip.Color(75,0,130); // indigo 
      break; 
    case 14: color = strip.Color(255, 69, 0); // orange red 
      break; 
    case 15: color = strip.Color(173, 255, 47); // green yellow 
      break; 
    case 16: color = strip.Color(255, 20, 147); // deep pink 
      break; 
    case 17: color = strip.Color(210, 105, 30); // chocolate 
      break; 
    case 18: color = strip.Color(148, 0, 211); // dark violet 
      break; 
    case 19: color = strip.Color(139, 69, 19); // saddle brown 
      break; 
    case 20: color = strip.Color(128, 128, 0); // olive 
      break; 
  } 
}  
 
void setAnimation(){ 
  switch(animationState){ 
    case 4: colorWipe(color); 
      break; 
    case 1: flash(color); 
      break; 
    case 2: spinnyWheel(); 
      break; 
    case 3: randomFill(color);
      break;
    case 0: breathe(color);
      break;
  } 
} 
 
// Fill setAnimationthe dots one after the other with a color 
void colorWipe(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
  }
 }
 
//flash crawling lights.
void flash(uint32_t c) {
    for (int q=0; q < 8; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+8) {
        c = color;
        strip.setPixelColor(i+q, c);    //turn every 8 pixel on
        strip.show();
      }
      delay(30);
      for (uint16_t i=0; i < strip.numPixels(); i=i+8) {
        strip.setPixelColor(i+q, 0);        //turn every 8 pixel off
      }
    }
}

//spinnyWheel lights.
void spinnyWheel(){ 
  uint32_t c = 0; 
  if(((offset + currentPixel) & 16) < 5){ 
    c = color;
  } 
  strip.setPixelColor(currentPixel, c);  
  if(currentPixel == PIXEL_COUNT - 1){
    strip.show(); 
    currentPixel = 0; 
    delay(900); 
  } 
  else{ 
    currentPixel++; 
  } 
  offset++; 
}
 

void randomFill(uint32_t c) {
  strip.clear();
  int used[strip.numPixels()]; // array to keep track of lit LEDs
  int lights = 0; // counter

  for(int i = 0; i<strip.numPixels(); i++){ // fill array with 0
    used[i] = 0;
  }

  while(lights<strip.numPixels()) {
    int j = random(0,strip.numPixels()); // pick a random LED
    if(used[j] != 1){ // if LED not already lit, proceed
      strip.setPixelColor(j, c);
      used[j] = 1; // update array to remember it is lit
      lights++;
      strip.show(); // display
      delay(700);
    }
  }
}


///////////////////////////////////////////////////////////////////
//Breath
///////////////////////////////////////////////////////////////////

#define SLEEP_BRIGHTNESS 1
#define SLEEP_CYCLE_MS 5000 // 5 second breathing cycle.

const uint8_t KEYFRAMES[]  = {
  // Rising
  20, 21, 22, 24, 26, 28, 31, 34, 38, 41, 45, 50, 55, 60, 66, 73, 80, 87, 95,
  103, 112, 121, 131, 141, 151, 161, 172, 182, 192, 202, 211, 220, 228, 236,
  242, 247, 251, 254, 255,

  // Falling
  254, 251, 247, 242, 236, 228, 220, 211, 202, 192, 182, 172, 161, 151, 141,
  131, 121, 112, 103, 95, 87, 80, 73, 66, 60, 55, 50, 45, 41, 38, 34, 31, 28,
  26, 24, 22, 21, 20,
  20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 
};

unsigned long lastBreath = 0.0;
int keyframePointer = 0;

void resetBreathe() {
  Serial.println("resetBreathe()");
  keyframePointer = 0;
}

void breathe(uint32_t c) {
//  Serial.println("breathe()");
  int numKeyframes = sizeof(KEYFRAMES) - 1;
  float period = SLEEP_CYCLE_MS / numKeyframes;
  unsigned long now = millis();
  
  if ((now - lastBreath) > period) {
    lastBreath = now;

    for (int i = 0; i < strip.numPixels(); i++) {
      strip.setBrightness(SLEEP_BRIGHTNESS * KEYFRAMES[keyframePointer]);
      Serial.print(c); Serial.println();
//      uint8_t color = (SLEEP_BRIGHTNESS * 127 * KEYFRAMES[keyframePointer]) / 256;
      strip.setPixelColor(i, c);
    }
    strip.show();   

    // Increment the keyframe pointer.
    if (++keyframePointer > numKeyframes) {
      // Reset to 0 after the last keyframe.
      keyframePointer = 0;
    }   
  }
}

 
//INPUT FUNCTIONS 
void getAnimationButtonState(){ 
  // Get current button state. 
  bool newAnimationState = digitalRead(BUTTON_PIN_1); 
   
  // Check if state changed from high to low (button press). 
  if (newAnimationState == LOW && oldAnimationState == HIGH) { 
  // Serial.println("*******************buttonpress*********************"); 
  // Short delay to debounce button. 
  delay(1); 
  // Check if button is still low after debounce. 
  newAnimationState = digitalRead(BUTTON_PIN_1); 
  if (newAnimationState == LOW) { 
    //Serial.println("animationState++"); 
    currentPixel = 0; 
    animationState++; 
    //Serial.print("animationState");Serial.println(animationState); 
    if (animationState > maxAnimationState) 
      animationState = 0; 
  } 
} 
 
// Set the last button state to the old state. 
oldAnimationState = newAnimationState; 
} 
 
 
 
void getColorButtonState(){ 
  // Get current button state. 
  bool newColorState = digitalRead(BUTTON_PIN_2); 
   
  // Check if state changed from high to low (button press). 
  if (newColorState == LOW && oldColorState == HIGH) { 
    // Short delay to debounce button. 
    delay(1); 
    // Check if button is still low after debounce. 
    newColorState = digitalRead(BUTTON_PIN_2); 
    if (newColorState == LOW) { 
    colorState++; 
    currentPixel = 0; 
    if (colorState > maxColorSate) 
      colorState = 0; 
  } 
} 
 
// Set the last button state to the old state. 
oldColorState = newColorState; 
} 
 
int previousPotVal = 0; 
int currentPotVal = 0; 
 
//void setLEDBrightness(){ 
// currentPotVal = analogRead(POT_PIN); // read pot  
// if(currentPotVal != previousPotVal){ 
// brightness = map(analogRead(POT_PIN),0,1023,0,255); // convert the POT reading of 0-1023 to brightness of 0-255 
// previousPotVal = currentPovVal; 
// } 
//} 
