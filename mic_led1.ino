#include <M5Core2.h>
#include <Adafruit_NeoPixel.h>

#define MIC 36
#define LED_PIN 32
#define LED_COUNT 15// Popular NeoPixel ring size
#define DELAYVAL  100

const int sampleWindow = 50;

int led_color[3][3] ={{10,0,0},{0,10,0},{0,0,10}};
Adafruit_NeoPixel pixels(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
//LEDオブジェクトの作成

void setup() {
  M5.begin();
  Serial.begin(115200);
  while (!Serial);
  M5.lcd.setBrightness(20);
  

  pinMode(MIC,INPUT);

  pixels.begin();
  pixels.show();
  //LEDテープを初期状態（前消灯）にする
  pixels.setBrightness(30);
}

void loop() {
  unsigned long t = millis();
  unsigned int sample;
  unsigned int sMax = 0, sMin = 4095;
  
  while(millis() - t < sampleWindow){
    sample = analogRead(MIC);
    if(sample > sMax) sMax = sample;
    if(sample < sMin) sMin = sample;
  }

  float volts = (float)(sMax - sMin) / 4095.0 * 3.6;
  Serial.println(volts);
  delay(100);

  pixels.clear();

  if (volts > 1.0) {
    M5.Lcd.setTextColor(WHITE,BLACK);
    M5.Lcd.setTextSize(5);
    M5.Lcd.setCursor(10, 100);
    M5.Lcd.print("High");

    delay(10); 

    for(int i=0; i<LED_COUNT; i++){
      pixels.setPixelColor(i, pixels.Color(255, 0, 255));//ピンク
    }
    pixels.show();

    delay(500);

    for(int i=0; i<LED_COUNT; i++){
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    }
    pixels.show();

    delay(500);

  }else{
    M5.Lcd.fillScreen(BLACK);
  }
}
