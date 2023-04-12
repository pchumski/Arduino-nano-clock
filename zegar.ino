#include <TM1637Display.h>
#include <Rotary.h>
#include <SparkFunDS1307RTC.h>
#include <Wire.h>
Rotary r = Rotary(3, 2);

#define CLK 5
#define DIO 6


int i,m,h,l,n,time;
bool st;
TM1637Display display(CLK, DIO);

void setup() {
  Serial.begin(9600);
  r.begin();
   rtc.begin(); 
PCICR |= (1 << PCIE2);
  PCMSK2 |= (1 << PCINT18) | (1 << PCINT19);
  sei();
pinMode(4,INPUT_PULLUP);
 
 Serial.print(rtc.minute());

}

void loop() {
  static int8_t lastSecond = -1;
  rtc.update();

  display.setBrightness(0x0f);
if(n>0){
time=(h*100)+m;
 display.showNumberDecEx(time, 0b11100000, true);}
  if(!digitalRead(4)&!st){
    st=1;
  n++;
  if(n>2){n=0;
  rtc.setMinute(m);
  rtc.setHour(h);
  }
  }
  if(digitalRead(4))st=0;
if(n==0) { 
  

  if (rtc.second() != lastSecond)
  {  m=rtc.minute();
h=rtc.hour();
      time=(h*100)+m;    
    lastSecond = rtc.second();
  }
l++;



if(l<45)display.showNumberDecEx(time, 0b11100000, true);
if(l==90){

}
 if(l>45)display.showNumberDecEx(time, 0, true);
 if(l>90)l=0;

}

}
ISR(PCINT2_vect) {
  unsigned char result = r.process();
  if (result == DIR_NONE) {
  }
  if (result== DIR_CW){
      if(n==1)m=m+1;
   
      if(n==2)h=h+1;
    
     if(m>59)m=59;
     if(h>23)h=23;
     Serial.print("CW");
     Serial.println(m);}

     if (result== DIR_CCW){
      if(n==1)m=m-1;
     
      if(n==2)h=h-1;
     
     if(m<0)m=0;
     if(h<0)h=0;
      Serial.print("CCW");
     Serial.println(m); }
}
