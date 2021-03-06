/*
  MIDI MERGE by Sandy Sims
  October 24 2019
  www.freshnelly.com/midimerge.htm
  (site may not be active yet!)
  Feel free to modify this to you liking but if you start selling them, you will require explicit permission
  fresh@freshnelly.com

  Teensy 4.1 version

*/

#include <EEPROM.h>
#include <Wire.h> //uses i2c for OLED Display
#include <USBHost_t36.h>

#define IN_LED1 2
#define IN_LED2 3
#define IN_LED3 4
#define IN_LED4 5
#define IN_LED5 33
#define OUT_LED1 6
#define OUT_LED2 29
#define OUT_LED3 28
#define OUT_LED4 9
#define OUT_LED5 36

#define UP_BUTTON 12
#define DOWN_BUTTON 11
#define SELECT 24

// digital pin 2 has a pushbutton attached to it. Give it a name:
byte cable = 0;
byte hours = 0;
byte mins = 0;
byte secs = 0;
byte midi1in = 0;
byte midi2in = 0;
byte midi3in = 0;
byte midi4in = 0;
byte midi5in = 0;
byte p1 = 0;
byte p2 = 0;
byte p3 = 0;
byte p4 = 0;
byte p5 = 0;
byte sysExCnt1 = 0;
byte sysExCnt2 = 0;
byte sysExCnt3 = 0;
byte sysExCnt4 = 0;
byte sysExCnt5 = 0;
byte rx1Buf[4];
byte rx2Buf[4];
byte rx3Buf[4];
byte rx4Buf[4];
byte rx5Buf[4];
byte lastCom1 = 0;
byte lastCom2 = 0;
byte lastCom3 = 0;
byte lastCom4 = 0;
byte lastCom5 = 0;
byte midiChannel1 = 0; //used in rx midi's
byte midiChannel2 = 0;
byte midiChannel3 = 0;
byte midiChannel4 = 0;
byte midiChannel5 = 0;
//menus
byte menuLev = 0; //this is menu levels
byte lev1Ptr = 0;
byte lev2Ptr = 0;
byte outListPtr = 0;
byte outListFid = 0;
byte a[16]; //temp use buffers
byte chanAdj = 0;
byte  optSel = 0;
byte  clkSel = 0;
byte pcSel = 0;
byte tranSel = 0;
byte ccSel = 0;
byte letSel = 0;
boolean letEdit = false;
int splitSel = 0;
int splitFid = 0;
byte splitEd = 0;
int bDir = 0;
boolean inList = false; //may use to show in a list....
byte onRelease = 0;
byte retToStby = 0;
byte  userWrite = 0;
char Str[18];


byte inLED1 = 0;
byte inLED2 = 0;
byte inLED3 = 0;
byte inLED4 = 0;
byte inLED5 = 0;
byte outLED1 = 0;
byte outLED2 = 0;
byte outLED3 = 0;
byte outLED4 = 0;
byte outLED5 = 0;


int upHeld = 0;
int dnHeld = 0;
int selHeld = 0;
String afterSpaces = "       ";

unsigned long microsNext = 0;
unsigned long butMillisNext = 0;
unsigned long secTimer = 0;
byte timeShow = 1;

String sss = "";
boolean done = false;
byte seconds5 = 0;

unsigned long t;
byte gDisplay = 0; //so only displays every 5th

byte curse = 0; //present cursor position 0-127
byte lastCurse = 0;

byte OUTheld = 0;
byte RECheld = 0;
byte SELheld = 0;
byte armed = 0;

boolean REC = false;

unsigned int selNum = 0;
byte selTOT = 0;

byte bytesOut = 1;
boolean OLEDbusy = false;

union u_tag {
  byte b[4];//lsb to msb "little endian"
  long fval; // example Serial.print(u.fval,HEX);
} u;

byte user = 0;

// need 5x5 array. These all have channels (0-15) & bit4=OFF
// For "same channel" then array # will match channel #, for channel change there will be a different channel
// This will route all channel based MIDI messages to set outputs. Channels can be different now
// defaults will be 0-15 with bit 4 set. so if input at port2 on chan3, out 1,2 &3 will all send channel 3
byte in1out1[17]; //in1out1[inChan]-->out1  ** IF  IS 0xFx then all are invalid as output is turned off
byte in1out2[17];
byte in1out3[17];
byte in1out4[17];
byte in1out5[17];
byte in2out1[17];
byte in2out2[17];
byte in2out3[17];
byte in2out4[17];
byte in2out5[17];
byte in3out1[17];
byte in3out2[17];
byte in3out3[17];
byte in3out4[17];
byte in3out5[17];
byte in4out1[17];
byte in4out2[17];
byte in4out3[17];
byte in4out4[17];
byte in4out5[17];
byte in5out1[17];
byte in5out2[17];
byte in5out3[17];
byte in5out4[17];
byte in5out5[17];
byte usbBuff[3];
int usbPointer = 0;
byte usbChannel = 0;

//keyboard splits: each input can have a channel/lowNote/highNote.
//These can be sent to "in" channels (before re-distribution) or outputs 1,2,3 on set channels
// ** only 1 split per input!  Only Notes.
byte split1 = 0x10; //bits0-3 is inX channel 0-15, bit4 is OFF, //bit 5,6,7 are overLap in two's from EEPROM, not here!
byte split1low = 36;
byte split1hi = 48;
byte split1chan1 = 0x10; //These are used with both types of split: outs1,2,3 or chans on one or more outs
byte split1chan2 = 0x21; //bits 0-3=channel, bits 4&5 are out 1-3 (always 1,2,3 but if 0, then no out!)
byte split1chan3 = 0x32;
byte split1chan4 = 0x43; //bits 0-3=channel, bits 4&5 are out 1-3 (always 1,2,3 but if 0, then no out!)
byte split1chan5 = 0x54;
byte split1NO1 = 36;
byte split1NO2 = 36;
byte split1NO3 = 36;
byte split1NO4 = 36;
byte split1NO5 = 36;
byte split1PC1 = 0; //piano
byte split1PC2 = 0;
byte split1PC3 = 0;
byte split1PC4 = 0;
byte split1PC5 = 0;

byte split2 = 0x10;
byte split2low = 36;
byte split2hi = 48;
byte split2chan1 = 0x10;
byte split2chan2 = 0x21;
byte split2chan3 = 0x32;
byte split2chan4 = 0x43; //bits 0-3=channel, bits 4&5 are out 1-3 (always 1,2,3 but if 0, then no out!)
byte split2chan5 = 0x54;
byte split2NO1 = 36;
byte split2NO2 = 36;
byte split2NO3 = 36;
byte split2NO4 = 36;
byte split2NO5 = 36;
byte split2PC1 = 0; //piano
byte split2PC2 = 0;
byte split2PC3 = 0;
byte split2PC4 = 0;
byte split2PC5 = 0;

byte split3 = 0x10;
byte split3low = 36;
byte split3hi = 48;
byte split3chan1 = 0x10;
byte split3chan2 = 0x21;
byte split3chan3 = 0x32;
byte split3chan4 = 0x43; //bits 0-3=channel, bits 4&5 are out 1-3 (always 1,2,3 but if 0, then no out!)
byte split3chan5 = 0x54;
byte split3NO1 = 36;
byte split3NO2 = 36;
byte split3NO3 = 36;
byte split3NO4 = 36;
byte split3NO5 = 36;
byte split3PC1 = 0; //piano
byte split3PC2 = 0;
byte split3PC3 = 0;
byte split3PC4 = 0;
byte split3PC5 = 0;

byte split4 = 0x10;
byte split4low = 36;
byte split4hi = 48;
byte split4chan1 = 0x10;
byte split4chan2 = 0x21;
byte split4chan3 = 0x32;
byte split4chan4 = 0x43; //bits 0-3=channel, bits 4&5 are out 1-3 (always 1,2,3 but if 0, then no out!)
byte split4chan5 = 0x54;
byte split4NO1 = 36;
byte split4NO2 = 36;
byte split4NO3 = 36;
byte split4NO4 = 36;
byte split4NO5 = 36;
byte split4PC1 = 0; //piano
byte split4PC2 = 0;
byte split4PC3 = 0;
byte split4PC4 = 0;
byte split4PC5 = 0;

byte split5 = 0x10;
byte split5low = 36;
byte split5hi = 48;
byte split5chan1 = 0x10;
byte split5chan2 = 0x21;
byte split5chan3 = 0x32;
byte split5chan4 = 0x43; //bits 0-3=channel, bits 4&5 are out 1-3 (always 1,2,3 but if 0, then no out!)
byte split5chan5 = 0x54;
byte split5NO1 = 36;
byte split5NO2 = 36;
byte split5NO3 = 36;
byte split5NO4 = 36;
byte split5NO5 = 36;
byte split5PC1 = 0; //piano
byte split5PC2 = 0;
byte split5PC3 = 0;
byte split5PC4 = 0;
byte split5PC5 = 0;

byte spLow = 0; byte spHi = 0; byte spCh1 = 0; byte spCh2 = 0; byte spCh3 = 0; byte spCh4 = 0; byte spCh5 = 0; byte spOut1 = 0; byte spOut2 = 0; byte spOut3 = 0; byte spOut4 = 0; byte spOut5 = 0;
byte spNO1 = 0; byte spNO2 = 0; byte spNO3 = 0; byte spNO4 = 0; byte spNO5 = 0; byte spPC1 = 0; byte spPC2 = 0; byte spPC3 = 0; byte spPC4 = 0; byte spPC5 = 0; byte sch = 0; int ip = 0;
byte splitPC1 = 0; //set to zero by config change. If 0 when a split event happens, will send PC info first
byte splitPC2 = 0;
byte splitPC3 = 0;
byte splitPC4 = 0;
byte splitPC5 = 0;
byte overLap[6];

boolean runFlag1 = false;

byte out1circle[256]; //circle buffers called every .320 mS
byte out2circle[256];
byte out3circle[256];
byte out4circle[256];
byte out5circle[256];

byte oc1 = 0; //load circle pointers
byte oc2 = 0;
byte oc3 = 0;
byte oc4 = 0;
byte oc5 = 0;

byte toc1 = 0; //transmit circle pointers, tx until == oc
byte toc2 = 0;
byte toc3 = 0;
byte toc4 = 0;
byte toc5 = 0;

byte clk1[6]; //outX from in1? bit0=clock F8's, bit1=transport messages, bit2=PC messages,bit3=CC's (both all channels): defaults to all on (0x0F)
byte clk2[6]; //outX from in2? (each byte in array is for an OUT)
byte clk3[6]; //outX from in3?
byte clk4[6]; //outX from in4? (each byte in array is for an OUT)
byte clk5[6]; //outX from in5?
byte userwrite = 0; //to invoke 5 second delay before saving new user# to EEPROM

int noHighest = 0; //counts highest
byte no1Chan[256]; //PORT 1:channel of note on..must do seperate as scan of>256 would be slow!
byte no1Note[256]; //      Note on #. bit 7 set means empty
byte no2Chan[256]; //PORT 1:channel of note on..must do seperate as scan of>256 would be slow!
byte no2Note[256]; //
byte no3Chan[256]; //PORT 1:channel of note on..must do seperate as scan of>256 would be slow!
byte no3Note[256]; //
byte no4Chan[256]; //PORT 1:channel of note on..must do seperate as scan of>256 would be slow!
byte no4Note[256]; //
byte no5Chan[256]; //PORT 1:channel of note on..must do seperate as scan of>256 would be slow!
byte no5Note[256]; //


int stbyStep = 0;
byte nameStep = 0;
byte nameScroll = 0;
byte wasClock1 = 0; //unplug detect based on clocks stopping
byte wasClock2 = 0;
byte wasClock3 = 0;
byte wasClock4 = 0;
byte wasClock5 = 0;
String name = "USER MIDI ORG 01 ";
boolean holdExit = false;

//USB HOST MIDI Class Compliant
USBHost myusb;
USBHub hub1(myusb);
USBHub hub2(myusb);
MIDIDevice midi1(myusb);




// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial1.begin(31250);
  Serial2.begin(31250);
  Serial3.begin(31250);
  Serial4.begin(31250);
  Serial.begin(115200);
  delay(100);
  Wire.begin(); // join i2c bus (address optional for master)
  Wire.setClock(800000); //temp, slow to 400k
  oled();
  // for (int i = 0; i < 256; i++) {
  //    Serial.print(i); Serial.print("\t"); Serial.println(EEPROM.read(i));
  //  }
  delay(10);
  splash();
  delay(100);
  OLED_UD(1024, 0, 127, 8, 7); //full screen whatever
  OLEDwerds("MIDI", 30, 0, 0);

  overLap[0] = 0; overLap[1] = 0; overLap[2] = 0;

  pinMode(UP_BUTTON, INPUT_PULLUP); //UP button
  pinMode(DOWN_BUTTON, INPUT_PULLUP); //DN button
  pinMode(SELECT, INPUT_PULLUP);  //SEL
  pinMode(IN_LED1, OUTPUT);
  pinMode(IN_LED2, OUTPUT);
  pinMode(IN_LED3, OUTPUT);
  pinMode(IN_LED4, OUTPUT);
  pinMode(IN_LED5, OUTPUT);
  pinMode(OUT_LED1, OUTPUT);
  pinMode(OUT_LED2, OUTPUT);
  pinMode(OUT_LED3, OUTPUT);
  pinMode(OUT_LED4, OUTPUT);
  pinMode(OUT_LED5, OUTPUT);

  for (int i = 100; i >= 0; i--) {
    analogWrite(IN_LED1, i);
    analogWrite(IN_LED2, i);
    analogWrite(IN_LED3, i);
    analogWrite(IN_LED4, i);
    analogWrite(IN_LED5, i);
    analogWrite(OUT_LED1, i);
    analogWrite(OUT_LED2, i);
    analogWrite(OUT_LED3, i);
    analogWrite(OUT_LED4, i);
    analogWrite(OUT_LED5, i);
    delay(16);
  }
  OLEDwerds("MERGE", 20, 0, 0); //6 chars max...CONF:1
  delay(200);

  if ( !digitalRead(UP_BUTTON) && !digitalRead(DOWN_BUTTON)) factory(); //hold up & down buttons to do factory reset, no warning!
  user = EEPROM.read(4095);
  userSel();

  for (int i = 0; i < 256; i++) { //initiate note ons
    no1Note[i] = 128;
    no2Note[i] = 128;
    no3Note[i] = 128;
    no4Note[i] = 128;
    no5Note[i] = 128;
  }

  microsNext = micros();
  butMillisNext = millis();
  secTimer = millis();

  myusb.begin();

}
// the loop routine runs over and over again forever:
void loop()
{

  // USB host input
  // Effectively MIDI input 4 with a DIN output

  myusb.Task();
  if (midi1.read())
  {
    // get the USB MIDI message, defined by these 5 numbers (except SysEX)
    rx4Buf[0] = midi1.getType();
    rx4Buf[1] = midi1.getData1();
    rx4Buf[2] = midi1.getData2();
    rx4Buf[3] = midi1.getChannel();
    usbEvent4();
  }

  // USB input
  // Effectively MIDI input 5 with USB output

  if (usbMIDI.read())
  {
    // get the USB MIDI message, defined by these 5 numbers (except SysEX)
    rx5Buf[0] = usbMIDI.getType();
    rx5Buf[1] = usbMIDI.getData1();
    rx5Buf[2] = usbMIDI.getData2();
    rx5Buf[3] = usbMIDI.getChannel();
    usbEvent5();
  }

  //  if (micros() > microsNext) {
  //    microsNext += 320UL;
  if (micros() - microsNext > 319UL) {
    microsNext = micros();

    //TX any
    if (oc1 != toc1) {
      Serial1.write(out1circle[toc1]); if (out1circle[toc1] == 0xF8) { //temp!
        analogWrite(OUT_LED1, 20); outLED1 = 10;
      }
      toc1++;
    }
    if (oc2 != toc2) {
      Serial2.write(out2circle[toc2]); toc2++;
    }
    if (oc3 != toc3) {
      Serial3.write(out3circle[toc3]); toc3++;
    }
    if (oc4 != toc4) {
      Serial4.write(out4circle[toc4]); toc4++;
    }
    if (oc5 != toc5) {
      if ( out5circle[toc5] > 127 )
      {
        usbPointer = 1;
        usbBuff[0] = out5circle[toc5];
        usbChannel = (out5circle[toc5] &= 0x0f);
        usbBuff[0] &= 0xf0;
        if ( (usbBuff[0] == 0xC0) | (usbBuff[0] == 0xD0))
        {
          usbPointer = 2 ;
        }
        usbBuff[1] = 255;
      }
      else
      {
        usbPointer = usbPointer + 1;
        if ( usbBuff[1] != 255 )
        {
          usbBuff[2] = out5circle[toc5];
        }
        else
        {
          usbBuff[1] = out5circle[toc5];
        }
      }
      toc5++;
      if ( usbPointer == 3 )
      {
        if ( usbBuff[0] == 0xC0 )
        {
          usbMIDI.sendProgramChange(usbBuff[1], usbChannel + 1);
        }
        else if ( usbBuff[0] == 0xD0 )
        {
          usbMIDI.sendAfterTouch(usbBuff[1], usbChannel + 1);
        }
        else
        {
          usbMIDI.send(usbBuff[0], usbBuff[1], usbBuff[2], usbChannel + 1, cable);
        }
        usbPointer = 0;
      }
      // usbMIDI.send(c, m, v, 0, cable);
    }

  }

  if (millis() > butMillisNext) { //scan buttons every 10mS. don't use for any timed app as is set tp 50 by release!
    butMillisNext += 10;

    if (!digitalRead(UP_BUTTON)) { //UP
      upButton();
    } else {
      if (upHeld != 0) UPrelease();
    }
    if (!digitalRead(DOWN_BUTTON)) { //DN
      dnButton();
    } else {
      if (dnHeld != 0) DNrelease();
    }
    if (!digitalRead(SELECT)) { //SEL
      selButton();
    } else {
      if (selHeld != 0) SELrelease();
    }

    standBy();
    if ( secTimer > 0xfff00000 && micros() < 0x7fffffff) secTimer += 1000000UL;

    if (inLED1) {
      inLED1 -= 2; analogWrite(IN_LED1, inLED1);
    }
    if (inLED2) {
      inLED2 -= 2; analogWrite(IN_LED2, inLED2);
    }
    if (inLED3) {
      inLED3 -= 2; analogWrite(IN_LED3, inLED3);
    }
    if (inLED4) {
      inLED4 -= 2; analogWrite(IN_LED4, inLED4);
    }
    if (inLED5) {
      inLED5 -= 2; analogWrite(IN_LED5, inLED5);
    }
    if (outLED1) {
      if (outLED1 < 4) outLED1 = 4; //must do this as wirks from velocity etc
      outLED1 -= 4; analogWrite(OUT_LED1, outLED1);
    }
    if (outLED2) {
      if (outLED2 < 4) outLED2 = 4;
      outLED2 -= 4; analogWrite(OUT_LED2, outLED2);
    }
    if (outLED3) {
      if (outLED3 < 4) outLED3 = 4;
      outLED3 -= 4; analogWrite(OUT_LED3, outLED3);
    }
    if (outLED4) {
      if (outLED4 < 4) outLED4 = 4;
      outLED4 -= 4; analogWrite(OUT_LED4, outLED4);
    }
    if (outLED5) {
      if (outLED5 < 4) outLED5 = 4;
      outLED5 -= 4; analogWrite(OUT_LED5, outLED5);
    }
  }



  if (millis() > secTimer) {
    secTimer += 0x3E8;//1000UL;
    //  Serial.println(" since power-up");
    //   Serial.println( microsNext, HEX);
    secs++;
    if (secs == 60) {
      secs = 0; mins++;
      //Serial.print(hours);  Serial.print(":"); Serial.print(mins); Serial.print(":"); Serial.println(secs);
      if ( mins == 60) {
        mins = 0;
        hours++; //could save to EEPROM lol
      }
    }
    if (userWrite) {
      userWrite--; if (userWrite == 0)EEPROM.write(2047, user);
    }
    if (retToStby) {
      retToStby--; if (retToStby == 0) ret2standby();
    }
    //turn off all notes 5 secs after clock stop (unless cancelled by a transport event)
    if (wasClock1) {
      wasClock1--; if (wasClock1 == 0) {
        allNotesOff(16, 4); //Serial.println("All Off 1");
      }
    }
    if (wasClock2) {
      wasClock2--; if (wasClock2 == 0) {
        allNotesOff(16, 4); //Serial.println("All Off 2");
      }

    }
    if (wasClock3) {
      wasClock3--; if (wasClock3 == 0) {
        allNotesOff(16, 4); //Serial.println("All Off 3");
      }
    }
    if (wasClock4) {
      wasClock4--; if (wasClock4 == 0) {
        allNotesOff(16, 4); //Serial.println("All Off 4");
      }

    }
    if (wasClock5) {
      wasClock5--; if (wasClock5 == 0) {
        allNotesOff(16, 4); //Serial.println("All Off 5");
      }
    }
  }
}
