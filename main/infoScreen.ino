#include <SPI.h>
#include <TFT_eSPI.h>
#include <ArduinoJson.h>

#define BLACK 0X0000
#define WHITE 0xFFFF
#define RED   0xF800
#define GREEN 0x07E0
#define YELLOW 0xFFE0  

const int name_offset_x = 30,
          name_offset_y = 15,
          line_spacing = 10,
          padding_x = 5;

void infoScreen( DynamicJsonDocument doc, TFT_eSPI display, String name ){
    
    //displaying name of coin
    display.setCursor( name_offset_x, name_offset_y );
    display.setTextSize(2);
    display.print(name);


    //displaying price of coin
    display.setCursor( 2*padding_x, name_offset_y + line_spacing );
    display.setTextSize(1);
    display.setTextColor(YELLOW);
    display.print("Price: $ ");
    display.print(doc["market_data"]["current_price"]["usd"]);


    //displaying recent price change
    display.setTextColor(WHITE);
    display.setCursor( padding_x, name_offset_y + 2*line_spacing );
    display.print("1h");
    display.setCursor( 3*padding_x, name_offset_y + 2*line_spacing );
    display.print("24h");
    display.setCursor( 5*padding_x, name_offset_y + 2*line_spacing );
    display.print("7d");

    display.setCursor( padding_x, name_offset_y + 3*line_spacing );
    float temp = doc["market_data"]["price_change_percentage_1h_in_currency"]["usd"];
    temp>0 ? display.setTextColor(GREEN) : display.setTextColor(RED);
    display.print(temp);
    display.print("%");

    display.setCursor( 3*padding_x, name_offset_y + 3*line_spacing );
    temp = doc["market_data"]["price_change_percentage_24h_in_currency"]["usd"];
    temp>0 ? display.setTextColor(GREEN) : display.setTextColor(RED);
    display.print(temp);
    display.print("%");

    display.setCursor( 5*padding_x, name_offset_y + 3*line_spacing );
    temp = doc["market_data"]["price_change_percentage_7d_in_currency"]["usd"];
    temp>0 ? display.setTextColor(GREEN) : display.setTextColor(RED);
    display.print(temp);
    display.print("%");


    //displaying market sentiment
    display.setCursor( padding_x, name_offset_y + 4*line_spacing );
    display.print("Market Sentiment: ");
    display.setTextColor(GREEN);
    display.print(doc["sentiment_votes_up_percentage"]);
    display.print("%");

    display.setTextColor(WHITE);
    display.print(" | ");

    display.setTextColor(RED);
    display.print(doc["sentiment_votes_down_percentage"]);
    display.print("%");

}