/*
 *This program takes in humidity and temperature and outputs to a Neopixel ring, LCD and buzzer as a output
 *This control system of inputs and outputs create a greenhouse monitoring system
 */
#include <LiquidCrystal_I2C.h>
#include <Adafruit_NeoPixel.h>
#include "DHT.h"
#ifdef __AVR__
#include <avr/power.h>
#endif

//Sets up humidity/temp sensor
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

//Sets up neopixel
#define PIN 13
Adafruit_NeoPixel strip = Adafruit_NeoPixel(12, PIN, NEO_GRB + NEO_KHZ800);

//Sets up lcd
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

//all input and output variables
int buzzerPin = 10;
int powerButton = 2;
int displayButton = 3;
int lcdClear = 1;
int ledValue, tempValue;
float h, t;

//Creates variables for state change
volatile byte powerState = LOW;
volatile byte dataState = LOW;

void setup() {
  dht.begin();

  strip.begin();
  strip.show();

  lcd.init();
  lcd.backlight();

  //Sets up interrupt pins for state change
  pinMode(powerButton, INPUT_PULLUP);
  pinMode(displayButton, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(powerButton), powerValue, RISING);
  attachInterrupt(digitalPinToInterrupt(displayButton), dataValue, RISING);

  Serial.begin(9600);
}

//Creates State change for displaying data
void dataValue()
{
  if (dataState == LOW)
  {
    dataState = HIGH;
  }
  else if (dataState == HIGH)
  {
    dataState = LOW;
  }
  lcdClear = 0;
}

//Creates state change for turning on/off the system
void powerValue()
{
  if (powerState == LOW)
  {
    powerState = HIGH;
  }
  else if (powerState == HIGH)
  {
    powerState = LOW;
  }
}

void loop()
{
  while (powerState == HIGH)
  {
    powerOn();
  }
  while (powerState == LOW)
  {
    powerOff();
  }
}

//Turns lcd and leds off
void powerOff()
{
  strip.clear();
  strip.show();
  lcd.noDisplay();
}

//Turns on inputs and outputs
void powerOn()
{
  strip.setBrightness(100);
  h = dht.readHumidity();
  delay(100);
  t = dht.readTemperature();
  delay(100);
  tempCheck(round(t));
  colours(humidCheck(h), 50);
  lcd.display();
  if(dataState == LOW)
  {
    lcdPrintTemp();
  }
  if(dataState == HIGH)
  {
    lcdPrintHumid();
  }
}

//Method to print temp on lcd
void lcdPrintTemp()
{
  for(lcdClear; lcdClear < 1; lcdClear++)
  {
    lcd.clear();
  }
  lcd.setCursor(0, 0);
  lcd.print("The temp is");
  lcd.setCursor(0 , 1);
  lcd.print(t);
}

//Method to print humidity on lcd
void lcdPrintHumid()
{
  for(lcdClear; lcdClear < 1; lcdClear++)
  {
    lcd.clear();
  }
  lcd.setCursor(0, 0);
  lcd.print("The humidity is");
  lcd.setCursor(0 , 1);
  lcd.print(h);
}

//Method to check if temp is in optimal range
void tempCheck(int temp)
{
  if (temp < 18 || temp >  24)
  {
    tone(buzzerPin, 262, (1000 / 4));
    int pauseBetweenNotes = (1000 / 4) * 1.30;
    delay(pauseBetweenNotes);
    noTone(buzzerPin);
  }
}

//Method to return how far off humidity level is from optimal level
int humidCheck(int humid)
{
  if(humid > 72 || humid < 48 )
  {
    return 12;
  }
  if(humid > 60)
  {
    return humid - 60;
  }
  if(humid < 60)
  {
    return 60 - humid;
  }
}

//Sets colors for neopixel
void colours(int values, int wait)
{
  for (int i = 0; i < values; i++)
  {
    strip.setPixelColor(i, strip.Color(255, 0, 0));
    strip.show();
    delay(wait);
  }

  for (int y = strip.numPixels(); y  >= values; y--)
  {
    strip.setPixelColor(y, strip.Color(0, 255, 0));
    strip.show();
    delay(wait);
  }
}
