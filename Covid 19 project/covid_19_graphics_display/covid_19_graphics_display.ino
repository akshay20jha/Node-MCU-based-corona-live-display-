#include <ESP8266WiFi.h>
#include <TFT_eSPI.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include "bitmap.h"
#include "Free_Fonts.h"
////ALL Libraries included
#define C "CASES"
#define D "DEATHS"
#define R "RECOVER"

long int a, b, c;

// WiFi Parameters
const char* ssid = "JfourE";
const char* password = "12345678";


TFT_eSPI tft = TFT_eSPI();


void setup(void) {
  
  Serial.begin(115200);
  Serial.print("ST7789 TFT Bitmap Test");

  tft.begin();     // initialize a ST7789 chip
  tft.setSwapBytes(true); // Swap the byte order for pushImage() - corrects endianness
tft.init();
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    tft.pushImage(0, 0, 240, 240, wifi  );
    delay(1000);
    
    Serial.println("Connecting...");

  }
}

void loop() {

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Connected...");
    GetData("http://coronavirus-19-api.herokuapp.com/all");
    Display( a, b, c , world );
    GetData("http://coronavirus-19-api.herokuapp.com/countries/india");
    Display( a, b, c , india );
    GetData("http://coronavirus-19-api.herokuapp.com/countries/usa");
    Display( a, b, c , usa );
    GetData("http://coronavirus-19-api.herokuapp.com/countries/italy");
    Display( a, b, c , italy );
    GetData("http://coronavirus-19-api.herokuapp.com/countries/spain");
    Display( a, b, c , spain );
    GetData("http://coronavirus-19-api.herokuapp.com/countries/germany");
    Display( a, b, c , germany );


  }
  
    //Close connection


}




void Display( long int cases , long int rec ,  long int  death , const uint16_t *place  ) {

  
  tft.fillScreen(0x0000);// background black
  tft.pushImage(50, 5, 140, 140, place  );
  tft.setFreeFont(FM24);                 // Select the font
  tft.drawString(C, 50, 155, GFXFF);// Print the string name of the font


  int cx = centre(cases) ;
  tft.drawNumber(cases, cx , 200, GFXFF);
  delay(2000);
  tft.fillRect(0,155,240,85,0x0000);
    tft.drawString(R, 25, 155, GFXFF);



  cx = centre(rec);
  tft.drawNumber(rec, cx , 200, GFXFF);
  delay(2000);
  tft.fillScreen(0x0000);// background black
  tft.pushImage(50, 5, 140, 140, place);
  tft.drawString(D, 42, 155, GFXFF);



  cx = centre(death);
  tft.drawNumber(death , cx , 200, GFXFF);


  

  delay(2000);

}

int long GetData(String url)
{ 

  HTTPClient http;
  http.begin(url);
  int httpCode = http.GET();
  Serial.println("http code");
  Serial.println(httpCode);
  
  if (httpCode > 0) {
    String payload = http.getString();
    Serial.println(payload);
    const size_t bufferSize = JSON_OBJECT_SIZE(12)+317  ;
    DynamicJsonBuffer jsonBuffer(bufferSize);
    JsonObject& root = jsonBuffer.parseObject(payload);


    a = root["cases"]; // {"cases":737589,"deaths":35000,"recovered":156295}
    b = root["recovered"];
    c = root["deaths"];
 
    return a, b, c;



  }http.end();
}

  int centre(long int someValue) {

    int valLen;
    if (someValue > 9999999)
      valLen = 8;
    else if (someValue > 999999)
      valLen = 7;
    else if (someValue > 99999)
      valLen = 6;
    else if (someValue > 9999)
      valLen = 5;
    else if (someValue > 999)
      valLen = 4;
    else if (someValue > 99)
      valLen = 3;
    else if (someValue > 9)
      valLen = 2;
    else
      valLen = 1;
    int mid;
    mid = ((240 - (valLen * 27)) / 2);
    return mid;
  }
