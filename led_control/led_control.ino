#include <FastLED.h>

#define LED_PIN     9
#define NUM_LEDS    146
#define LIGHT_KEYBOARD_START  132
#define LIGHT_KEYBOARD_WIDTH  14
#define LEDS_ABOVE  66

CRGB leds[NUM_LEDS];
int led_meta[NUM_LEDS] = {0};

CRGB orange = CRGB(255,64,0);

void init(){
  solid(orange, 0, NUM_LEDS );
  FastLED.show();
}

void setup() {

  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  init();
  
}

void solid(CRGB color, int start, int length){
  for(int i = start; i < start + length; i++){
    leds[i] = color;
  }
}

bool command_is(char * string){
  return strcmp(command, string) == 0;
}

char command[16];
char read_bytes = 0;
void loop() {
  if (Serial.available() > 0) {
    // read the incoming byte:
    read_bytes = Serial.readBytes(command, 16);
    if(command_is("KL_ON")){
      solid(CRGB::White, LIGHT_KEYBOARD_START, LIGHT_KEYBOARD_WIDTH);
    }else if(command_is("KL_OFF")){
      solid(orange, LIGHT_KEYBOARD_START, LIGHT_KEYBOARD_WIDTH);
    }else if(command_is("RESET")){
      init();
    }else if(command_is("")){
      
    }
    
    FastLED.show();
    
  }
}

void single(){
  int prev = 0;
  int next = 0;
  CRGB color = CRGB(255,64,0);
  int msDelay = 15;
  while(1){
     next = (prev + 1) % NUM_LEDS;
     leds[prev] = CRGB(0,0,0);
     leds[next] = color;
     FastLED.show();
     delay(msDelay);
     prev = next;
  }
}


void backnforth(){
  int prev = 0;
  int next = 0;
  CRGB color = CRGB(255,64,0);
//  CRGB color = CRGB(255,255,255);
  int msDelay = 10;
  for( int i = 0; i<NUM_LEDS;i++){
     if(i > 0) leds[i-1] = CRGB(0,0,0);
     leds[i] = color;
     FastLED.show();
     delay(msDelay);
  }

  for( int i = 0; i<NUM_LEDS;i++){
     if(i < (NUM_LEDS - 1)) leds[NUM_LEDS - i] = CRGB(0,0,0);
     leds[NUM_LEDS - 1 - i] = color;
     FastLED.show();
     delay(msDelay);
  }
}

void backnforth_multi(int size, CRGB color, int ms_delay, CRGB blank){
  int prev = 0;
  int next = 0;
 

  if(size < 1) size = 1;
  
  for( int i = size; i<NUM_LEDS;i++){
     if(i > size - 1) leds[i-size] = blank;
     leds[i] = color;
     FastLED.show();
     delay(ms_delay);
  }

  for( int i = NUM_LEDS-size; i>0;i--){
     if(i < (NUM_LEDS - size)) leds[i+size] = blank;
     leds[i] = color;
     FastLED.show();
     delay(ms_delay);
  }
}



void rando(){
  int delta = 1;
  int rand_led;
  int off;
  while(1){
    for(int i = 0; i<delta; i++){
       rand_led = random(0,NUM_LEDS);
       off = random() % 2;
       if(off){
          leds[rand_led] = CRGB(255,64,0);
       }else{
        leds[rand_led] = CRGB(0,0,0);
       }
       
    }
    FastLED.show();
    delay(50);
    
  }
}
