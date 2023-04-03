#include <SPI.h>
#include <TFT_eSPI.h>
#include <ArduinoJson.h>
#include <string.h>

#define BLACK 0X0000
#define WHITE 0xFFFF
#define RED   0xF800
#define GREEN 0x07E0
#define YELLOW 0xFFE0  

const int name_offset_x = 30,
          name_offset_y = 15,
          line_spacing = 20,
          padding_x = 15;

// TFT_eSPI display = TFT_eSPI(); 

String coin_dat[]= {"bitcoin","ethereum","tether","binancecoin","usd-coin","ripple","cardano","dogcoin"};

void infoScreen( DynamicJsonDocument doc, TFT_eSPI display, String name, int coin_index ){
    
    //displaying name of coin
    display.setCursor( name_offset_x, name_offset_y );
    display.setTextSize(2);
    display.print(name);


    //displaying price of coin
    display.setCursor( 2*padding_x, name_offset_y + line_spacing );
    display.setTextSize(1);
    display.setTextColor(YELLOW);
    display.print("Price: $ ");
    float temp = doc[coin_dat[coin_index]]["usd"];
    display.print(temp);


    //displaying recent price change
    display.setTextColor(WHITE);
    display.setCursor( padding_x, name_offset_y + 2*line_spacing );
    display.print("Market Cap: $ ");
    display.setCursor( padding_x, name_offset_y + 3*line_spacing );
    temp = doc[coin_dat[coin_index]]["usd_market_cap"];
    display.print(temp);

    display.setCursor( padding_x, name_offset_y + 4*line_spacing );
    display.print("24h vol: $ ");
    display.setCursor( padding_x, name_offset_y + 5*line_spacing );
    temp = doc[coin_dat[coin_index]]["usd_24h_vol"];
    display.print(temp);

    display.setCursor( padding_x, name_offset_y + 6*line_spacing );
    display.print("24h Change: $ ");
    temp = doc[coin_dat[coin_index]]["usd_24h_change"];
    temp>0 ? display.setTextColor(GREEN) : display.setTextColor(RED);
    display.print(temp);

}