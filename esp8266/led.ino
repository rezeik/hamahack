//ライブラリインクルード
#include <Adafruit_NeoPixel.h>

#define LED_COUNT ( 32 )
#define DIGITAL_PIN ( 13 )
Adafruit_NeoPixel led = Adafruit_NeoPixel( LED_COUNT, DIGITAL_PIN , NEO_GRB + NEO_KHZ800);

//case 1の海の表現用
const byte A[32] = {
  random(255), random(255), random(255), random(255), random(255),
  random(255), random(255), random(255), random(255), random(255),
  random(255), random(255), random(255), random(255), random(255),
  random(255), random(255), random(255), random(255), random(255),
  random(255), random(255), random(255), random(255), random(255),
  random(255), random(255), random(255), random(255), random(255),
  random(255), random(255)
};

//case 3の山の表現用
byte windForest = 0;

//case 4の果物用
byte positionPoint[2] = {};


void setup() {
  //初期化処理
  led.begin();
  led.show();
}


void loop() {

  //AWSからGETする光らせ方のパターン情報
  byte awsTriggerNum = 1;

  //TODO
  //皿が置かれていない条件では光らない処理の追加

  switch (awsTriggerNum) {

    //初期状態
    case 0:
      break;

    //魚(海)
    case 1:
      for (int n = 0 ; n < LED_COUNT ; n++ ) {
        for (int i = 0 ; i < LED_COUNT ; i++ ) {
          led.setPixelColor(i, led.Color(0, 0, A[(i + n) % 31]));
        }
        led.show();
        delay(150);
      }
      break;

    //餃子(熱)
    case 2:
      for (int i = 0 ; i < LED_COUNT ; i++ ) {
        byte firePower = random(255);
        led.setPixelColor(i, led.Color(firePower, random(firePower / 2), 0));
      }
      led.show();
      delay(300);
      break;

    //野菜(山)
    case 3:
      if (windForest <= 55) {
        for (int n = 0 ; n < LED_COUNT ; n++ ) {
          for (int i = 0 ; i < LED_COUNT ; i++ ) {
            led.setPixelColor(i, led.Color(random(A[(i + n) % 31] / 5), A[(i + n) % 31], A[(i + n) % 31] / 5));
          }
          led.show();
          delay(random(50 + 5 * windForest));
          windForest += 1;
        }
      } else {
        for (int n = LED_COUNT ; n >= 0 ; n-- ) {
          for (int i = 0 ; i < LED_COUNT ; i++ ) {
            led.setPixelColor(i, led.Color(random(A[(i + n) % 31] / 5), A[(i + n) % 31], A[(i + n) % 31] / 5));
          }
          led.show();
          delay(random(255 - 5 * (windForest - 55)));
          windForest += 1;
          if (windForest > 110) {
            windForest = 0;
          }
        }
      }
      break;

    //果物
    case 4:
      positionPoint[0] = random(0, 11);
      positionPoint[1] = random(0, 3);
      for (int n = 0; n < random(6, 12); n++) {
        for (int m = 0 ; m < positionPoint[1] ; m++ ) {
          for (int i = 0 ; i < positionPoint[2] ; i++ ) {
            led.setPixelColor(i + positionPoint[2], led.Color(A[(i + n) % 31], 0, A[(i + n) % 31]));
            led.setPixelColor(positionPoint[2] - 1 - i, led.Color(A[(i + n) % 31], 0, A[(i + n) % 31]));
            led.show();
            delay(100);
            led.setPixelColor(i + positionPoint[2], led.Color(0, 0, 0));
            led.setPixelColor(positionPoint[2] - 1 - i, led.Color(0, 0, 0));
            led.show();
          }
        }
      }
      break;

    //笑顔
    case 11:
      for (int n = 0 ; n < LED_COUNT ; n++ ) {
        for (int m = 0 ; m < 4 ; m++ ) {
          for (int i = 0 ; i < 6 ; i++ ) {
            led.setPixelColor(i + 6 + 4 * m, led.Color(A[(i + n) % 31], A[(i + n) % 31] / 2, 0));
            led.setPixelColor(5 - i + 4 * m, led.Color(A[(i + n) % 31], A[(i + n) % 31] / 2, 0));
          }
        }
        led.show();
        delay(150);
      }
      break;

    //不満
    case 12:
      for (int n = LED_COUNT ; n >= 0 ; n-- ) {
        for (int m = 4 ; m >= 0 ; m-- ) {
          for (int i = 6 ; i >= 0 ; i-- ) {
            led.setPixelColor(i + 5 + 4 * m, led.Color(0, A[(i + n) % 31] / 2, A[(i + n) % 31]));
            led.setPixelColor(6 - i + 4 * m, led.Color(0, A[(i + n) % 31] / 2, A[(i + n) % 31]));
          }
        }
        led.show();
        delay(150);
      }
      break;

    default:
      Serial.println("Not Action");

  }
}
