/*
 *  Project 09-oled-dht
 *      Austral 2023 - Electronica Digital - EAM
 *      Show DHT measurements in OLED display SSD1306 in text mode
 *      File: main.cpp
 */

#include <Arduino.h>

#include <Adafruit_Sensor.h>
#include <DHT.h>

#include "oled_ruts.h"      //  Wrapper for SSD1306 text only routines

/*
 *      Definitions in platformio.ini
 *      DHTPIN      GPIO where DHTxx data is connected
 *      DHTTYPE     Constant defining sensor type: DHT11 or DHT22
 *      BAUD        Serial port Baud rate
 */

DHT dht(DHTPIN, DHTTYPE);   // New DHT type object

void
setup()
{
    Serial.begin(BAUD);
    Serial.printf("\n\nDHT%d test!\n", DHTTYPE);
    dht.begin();
    oled_init();
}


void
loop()
{
    float h, t, f;
    char buffer[130];

    delay(2000);                    // It is a low speed sensor !!

    oled_open(LITTLE_TEXT);
    sprintf(buffer,"DHT%d data", DHTTYPE);
    oled_line(CENTER_ALIGN,0,buffer);

    h = dht.readHumidity();
    t = dht.readTemperature();     // in Celsius
    f = dht.readTemperature(true); // in Fahrenheit

    if (isnan(h) || isnan(t) || isnan(f))   //    Failed measurement ?
    {
        Serial.printf("Measurement failure\n");
        oled_line(CENTER_ALIGN,2,"Measure fail");
    }
    else
    {
        Serial.printf( "DHT%d -> Humedad: %5.1f %%, Temperatura: %5.1f C | %5.1f F\n", DHTTYPE, h, t, f );
        sprintf(buffer,"Humedad: %5.1f %%", h);
        oled_line(CENTER_ALIGN,2,buffer);
        sprintf(buffer,"T-Cent: %5.1f C", t );
        oled_line(CENTER_ALIGN,3,buffer);
        sprintf(buffer,"T-Fahr: %5.1f F", f );
        oled_line(CENTER_ALIGN,4,buffer);
    }
    oled_close();
}

