#include <SPI.h>
#include <TFT_eSPI.h>

#define BLACK 0X0000
#define WHITE 0xFFFF

TFT_eSPI display = TFT_eSPI();       // Invoke custom library

void setup() {

  display.init();

  display.setRotation(6);
  display.fillScreen(BLACK);
  // display.fillRect(2, 1, 128, 128, BLACK);
  display.setCursor(10,20);
  display.print("Shlok");

  // display.setCursor(2,1);
  display.drawPixel(2,1,WHITE);

  // for(int i=0;i<10;i++){
  //   display.setRotation(i);
  //   display.fillScreen(TFT_BLACK);
  //   display.fillRect(0, 1, 128, 128, BLACK);
  //   display.setCursor(50,50);
  //   display.println(i);
  //   display.println("Hii");
  //   delay(1000);}




  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}