#include <Adafruit_SSD1306.h>
#define OLED_Address 0x3C // 0x3C device address of I2C OLED. Few other OLED has 0x3D
Adafruit_SSD1306 oled(128, 64); // create our screen object setting resolution to 128x64
 
int a=0;
int lasta=0;
int lastb=0;
int LastTime=0;
int ThisTime;
bool BPMTiming=false;
bool BeatComplete=false;
int BPM=0;
#define UpperThreshold 560
#define LowerThreshold 530
 
void setup() {
oled.begin(SSD1306_SWITCHCAPVCC, OLED_Address);
oled.clearDisplay();
oled.setTextSize(2);
}
 
void loop()
{
if(a>127)
{
oled.clearDisplay();
a=0;
lasta=a;
}
 
ThisTime=millis();
int value=analogRead(0);
oled.setTextColor(WHITE);
int b=60-(value/16);
oled.writeLine(lasta,lastb,a,b,WHITE);
lastb=b;
lasta=a;
 
if(value>UpperThreshold)
{
if(BeatComplete)
{
BPM=ThisTime-LastTime;
BPM=int(60/(float(BPM)/1000));
BPMTiming=false;
BeatComplete=false;
tone(8,1000,250);
}
if(BPMTiming==false)
{
LastTime=millis();
BPMTiming=true;
}
}
if((value<LowerThreshold)&(BPMTiming))
BeatComplete=true;
 
oled.writeFillRect(0,50,128,16,BLACK);

 
oled.display();
a++;
}
