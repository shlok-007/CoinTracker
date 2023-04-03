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

// TFT_eSPI display = TFT_eSPI();       // Invoke custom library

int X_offSet= 2;
int Y_offSet= 1;
int cnDispWidth=20;
int color=WHITE;

    
String coin_dat[]= {"bitcoin","ethereum","tether","binancecoin","usd-coin","ripple","cardano","dogcoin"};
String coinSrtName[]= {"BTC","ETH","USDT","BNB","USDC","XRP","ADA","DOGE"};

int cryptoLim[8][2] = {{2,5},{2,6},{45,76},{2,8},{21,342},{2,10},{34,244},{4,13}};
// screen is of 128 * 128

int colorcheck(int indx,DynamicJsonDocument doc)
{
  int val;
  if(doc[coin_dat[indx]]["usd"]>cryptoLim[indx][1])
  val=GREEN;
  if(doc[coin_dat[indx]]["usd"]<cryptoLim[indx][0])
  val=RED;
  if(doc[coin_dat[indx]]["usd"]<=cryptoLim[indx][1] && doc[coin_dat[indx]]["usd"]>=cryptoLim[indx][0])
  val=BLUE;
  return val;
}

int colordeactivate(int indx,DynamicJsonDocument doc)
{
  int val;
  if(doc[coin_dat[indx]]["usd"]>cryptoLim[indx][1])
  val=DGREEN;
  if(doc[coin_dat[indx]]["usd"]<cryptoLim[indx][0])
  val=DRED;
  if(doc[coin_dat[indx]]["usd"]<=cryptoLim[indx][1] && doc[coin_dat[indx]]["usd"]>=cryptoLim[indx][0])
  val=DBLUE;
  return val;
}

void priceTraker(DynamicJsonDocument doc,TFT_eSPI display,int indx) {

 color=colorcheck(indx,doc);
  display.fillRect(2,1,107,3,color);
  display.fillRect(2,126,107,3,color);
  display.fillRect(2,1,3,128,color);
  display.fillRect(106,1,8,128,color);

for(int i=0;i<8;i++){
    if(i==indx)
    color=colorcheck(i,doc);
    else
    color=colordeactivate(i,doc);
    display.fillRect(110,1+16*i,20,16,color);
    display.setCursor(112,3+16*i);
    display.print(coinSrtName[i]);
}

}

