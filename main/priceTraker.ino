#include <SPI.h>
#include <TFT_eSPI.h>
#include <ArduinoJson.h>

#define BLACK 0X0000
#define WHITE 0xFFFF
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define DBLUE 0x00AC
#define DRED 0x7841
#define DGREEN 0x0266

TFT_eSPI display = TFT_eSPI();       // Invoke custom library

int X_offSet= 2;
int Y_offSet= 1;
int cnDispWidth=20;
int color=WHITE;

typedef struct cryptoCoins{
    String name;
    int high;
    int low;
}crypC;
    
    
crypC coin_dat[]= {"bitcoin","ethereum","tether","binancecoin","usd-coin","ripple","cardano","dogcoin"};

int cryptoLim[8][2] = {{2,5},{2,6},{45,76},{2,8},{21,342},{2,10},{34,244},{4,13}};
// screen is of 127 * 127

int colorcheck(int indx,DynamicJsonDocument doc)
{
  int val;
  if(doc[coin_dat[indx]][usd]>cryptoLim[indx][1])
  val=GREEN;
  if(doc[coin_dat[indx]][usd]<cryptoLim[indx][0])
  val=RED;
  if(doc[coin_dat[indx]][usd]<=cryptoLim[indx][1] && coin_dat[indx]][usd]>=cryptoLim[indx][0])
  val=BLUE;
  return val;
}

int colordeactivate(int indx,DynamicJsonDocument doc)
{
  int val;
  if(doc[coin_dat[indx]][usd]>cryptoLim[indx][1])
  val=DGREEN;
  if(doc[coin_dat[indx]][usd]<cryptoLim[indx][0])
  val=DRED;
  if(doc[coin_dat[indx]][usd]<=cryptoLim[indx][1] && coin_dat[indx]][usd]>=cryptoLim[indx][0])
  val=DBLUE;
  return val;
}

void priceTraker(DynamicJsonDocument doc,TFT_eSPI display,int indx) {

 color=colorcheck(indx,doc);
  display.fillRect(2,1,107,8,color);
  display.fillRect(2,120,107,8,color);
  display.fillRect(2,1,8,128,color);
  display.fillRect(101,1,8,128,color);

for(int i=0;i<8;i++){
    if(i==idx)
    color=colorcheck(i,doc);
    else
    color=colordeactivate(i,doc);
    display.fillRect(110,1+8*i,20,16,color);
}



//   display.fillRect(110,1,20,16,color);
//   display.fillRect(110,9,20,16,color);
//   display.fillRect(110,17,20,16,color);
//   display.fillRect(110,25,20,16,color);
//   display.fillRect(110,33,20,16,color);
//   display.fillRect(110,41,20,16,color);
//   display.fillRect(110,49,20,16,color);
//   display.fillRect(110,57,20,16,color);


  display.setCursor(10,20);
  display.print("Shlok");

  // Checking Display Corners
  display.drawPixel(2,1,WHITE);
  display.drawPixel(129,1,WHITE);
  display.drawPixel(2,128,WHITE);
  display.drawPixel(129,128,WHITE);

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

