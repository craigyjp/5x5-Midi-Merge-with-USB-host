
void factory() { //reset all EEPROM to factory "USER MIDI CFG nn"
  // ** note: This must be called from setup while variables are loaded with declaration values
  //  for (int i = 0; i < 512; i++) { //make bigger
  //    EEPROM.write(i, 0xFF);
  //  }
  OLEDwerds("FACTORY", 10, 0, 0);
  delay(100);
  for (int k = 0; k < 5; k++) { //80 total bytes
    name = "USER MIDI CFG "; if (k < 5)name += "0";
    name += String(k + 1);
    if (k == 0) name = "INITIAL CONFIG 1";
    for (int i = 0; i < 16; i++) {
      EEPROM.write(i + (k * 16), name.charAt(i));
      //Serial.println(name.charAt(i));
    }
  }
  //EEPROM.write(256 + i + (k * 16), i); // 80 to
  for ( int k = 0; k < 16; k++) {
    in1out1[k] = k ; //in1out1[inChan]-->out1, bit 4=off
    in1out2[k] = k ;
    in1out3[k] = k ;
    in1out4[k] = k ;
    in1out5[k] = k ;
    in2out1[k] = k ;
    in2out2[k] = k ;
    in2out3[k] = k ;
    in2out4[k] = k ;
    in2out5[k] = k ;
    in3out1[k] = k ;
    in3out2[k] = k ;
    in3out3[k] = k ;
    in3out4[k] = k ;
    in3out5[k] = k ;
    in4out1[k] = k ;
    in4out2[k] = k ;
    in4out3[k] = k ;
    in4out4[k] = k ;
    in4out5[k] = k ;
    in5out1[k] = k ;
    in5out2[k] = k ;
    in5out3[k] = k ;
    in5out4[k] = k ;
    in5out5[k] = k ;
  }
  //quick write these values to all 10 user configs 0-15 90 times from160+
  byte c = 0;
  for (int i = 0; i < 2000; i++) {
    EEPROM.write(i + 80, c);
    c++; if (c == 16) c = 0;
  }//next is 2080


  //load defaults set in variable declaraion
  for (int k = 0; k < 5; k++) { //splits: 18 * 5 user=150 bytes
    int kk = k * 24;
    EEPROM.write(2080 + kk, split1); EEPROM.write(2081 + kk, split1low); EEPROM.write(2082 + kk, split1hi); EEPROM.write(2083 + kk, split1chan1); EEPROM.write(2084 + kk, split1chan2); EEPROM.write(2085 + kk, split1chan3);
    EEPROM.write(2086 + kk, split1chan4); EEPROM.write(2087 + kk, split1chan5);
    EEPROM.write(2088 + kk, split1); EEPROM.write(2089 + kk, split1low); EEPROM.write(2090 + kk, split1hi); EEPROM.write(2091 + kk, split1chan1); EEPROM.write(2092 + kk, split1chan2); EEPROM.write(2093 + kk, split1chan3);
    EEPROM.write(2094 + kk, split1chan4); EEPROM.write(2095 + kk, split1chan5);
    EEPROM.write(2096 + kk, split1); EEPROM.write(2097 + kk, split1low); EEPROM.write(2098 + kk, split1hi); EEPROM.write(2099 + kk, split1chan1); EEPROM.write(2100 + kk, split1chan2); EEPROM.write(2101 + kk, split1chan3);
    EEPROM.write(2102 + kk, split1chan4); EEPROM.write(2103 + kk, split1chan5);
    // next is 2230
  }


  for (int i = 0; i < 5; i++) {
    clk1[i] = 0x0e; //out[] from inX? bit0=clk,bit1=trnspt,bit2=PC,bit3=CC's
    clk2[i] = 0x0e; //clock is off by default!
    clk3[i] = 0x0e;
    clk4[i] = 0x0e;
    clk5[i] = 0x0e;
  }

  for (int i = 0; i < 75; i++) { //0 to 8 (9 bytes per user cfg)*10=90 -->1870
    int ii = 2230 + i;
    EEPROM.write(ii, 0x0e);
  } //2305 next
  for (int i = 0; i < 75; i++) { //Program Changes to be sent for each channel/output
    EEPROM.write(2305 + i, 0); //all default to piano1
  }
  for (int i = 0; i < 75; i++) { //75-15 (last config is fixed at 36's) entries for Split Note Offsets...default=36 for all
    EEPROM.write(2380 + i, 36);
  }
  //Next is 4095 for any odd settings

  EEPROM.write(4095, user);
  userSel();
}

void userSel() { //load present user configuration
  //char Str[17];
  int i = 0;
  int k = user * 16; //(0 - 144 {+15})
  for (i = 0; i < 16; i++) {
    Str[i] = EEPROM.read(i + k);
  }
  Str[i] = 0;
  name = Str;
  //Serial.println(name);
  k = user;
  // load all port channels for this config from 160. 0-15 * 9 *user
  for (int i = 0; i < 16; i++) {
    int kk = (k * 400) + i; //user0:160-559, user1:560-959 user9:1456-1599
    in1out1[i] = EEPROM.read(80 + kk);
    in1out2[i] = EEPROM.read(96 + kk);
    in1out3[i] = EEPROM.read(112 + kk);
    in1out4[i] = EEPROM.read(128 + kk);
    in1out5[i] = EEPROM.read(144 + kk);
    in2out1[i] = EEPROM.read(160 + kk);
    in2out2[i] = EEPROM.read(176 + kk);
    in2out3[i] = EEPROM.read(192 + kk);
    in2out4[i] = EEPROM.read(208 + kk);
    in2out5[i] = EEPROM.read(224 + kk);
    in3out1[i] = EEPROM.read(240 + kk);
    in3out2[i] = EEPROM.read(236 + kk);
    in3out3[i] = EEPROM.read(252 + kk);
    in3out4[i] = EEPROM.read(268 + kk);
    in3out5[i] = EEPROM.read(284 + kk);
    in4out1[i] = EEPROM.read(300 + kk);
    in4out2[i] = EEPROM.read(316 + kk);
    in4out3[i] = EEPROM.read(332 + kk);
    in4out4[i] = EEPROM.read(348 + kk);
    in4out5[i] = EEPROM.read(364 + kk);
    in5out1[i] = EEPROM.read(380 + kk);
    in5out2[i] = EEPROM.read(396 + kk);
    in5out3[i] = EEPROM.read(412 + kk);
    in5out4[i] = EEPROM.read(428 + kk);
    in5out5[i] = EEPROM.read(444 + kk);

  }
  //split variables, 24 per user config!
  int kk = user * 24;
  split1 = EEPROM.read(2080 + kk); split1low = EEPROM.read(2081 + kk); split1hi = EEPROM.read(2082 + kk); split1chan1 = EEPROM.read(2083 + kk); split1chan2 = EEPROM.read(2084 + kk); split1chan3 = EEPROM.read(2085 + kk);
  split1chan4 = EEPROM.read(2086 + kk); split1chan5 = EEPROM.read(2087 + kk);
  split2 = EEPROM.read(2088 + kk); split2low = EEPROM.read(2089 + kk); split2hi = EEPROM.read(2090 + kk); split2chan1 = EEPROM.read(2091 + kk); split2chan2 = EEPROM.read(2092 + kk); split2chan3 = EEPROM.read(2093 + kk);
  split1chan4 = EEPROM.read(2094 + kk); split1chan5 = EEPROM.read(2095 + kk);
  split3 = EEPROM.read(2096 + kk); split3low = EEPROM.read(2097 + kk); split3hi = EEPROM.read(2098 + kk); split3chan1 = EEPROM.read(2099 + kk); split3chan2 = EEPROM.read(2100 + kk); split3chan3 = EEPROM.read(2101 + kk);
  split1chan4 = EEPROM.read(2102 + kk); split1chan5 = EEPROM.read(2103 + kk);
  overLap[0] = split1 >> 5; split1 &= 0x1F; overLap[1] = split2 >> 5; split2 &= 0x1F; overLap[2] = split3 >> 5; split3 &= 0x1F;
  overLap[0] = overLap[0] << 1; overLap[1] = overLap[1] << 1; overLap[2] = overLap[2] << 1; //double them so 0-14 notes
  //1780 is next
  for (int i = 0; i < 3; i++) {
    int ii = (user * 4) + i;
    clk1[i] = EEPROM.read(ii + 2230); //out[] from inX? bit0=clk,bit1=trnspt,bit2=PC,bit3=CC's
    clk2[i] = EEPROM.read(ii + 2233);
    clk3[i] = EEPROM.read(ii + 2236);
    clk4[i] = EEPROM.read(ii + 2239);
    clk5[i] = EEPROM.read(ii + 2242);

  }//1870 is next
  k = user * 4;
  split1PC1 = EEPROM.read(2305 + k); //program changes for splits
  split1PC2 = EEPROM.read(2306 + k);
  split1PC3 = EEPROM.read(2307 + k);
  split1PC4 = EEPROM.read(2308 + k);
  split1PC5 = EEPROM.read(2309 + k);
  split2PC1 = EEPROM.read(2310 + k);
  split2PC2 = EEPROM.read(2311 + k);
  split2PC3 = EEPROM.read(2312 + k);
  split2PC4 = EEPROM.read(2313 + k);
  split2PC5 = EEPROM.read(2314 + k);
  split3PC1 = EEPROM.read(2315 + k);
  split3PC2 = EEPROM.read(2316 + k);
  split3PC3 = EEPROM.read(2317 + k);
  split3PC4 = EEPROM.read(2318 + k);
  split3PC5 = EEPROM.read(2319 + k);
  // next is 1960
  if (user < 4) {
    split1NO1 = EEPROM.read(2380 + k);
    split1NO2 = EEPROM.read(2381 + k);
    split1NO3 = EEPROM.read(2382 + k);
    split1NO4 = EEPROM.read(2383 + k);
    split1NO5 = EEPROM.read(2384 + k);
    split2NO1 = EEPROM.read(2385 + k);
    split2NO2 = EEPROM.read(2386 + k);
    split2NO3 = EEPROM.read(2387 + k);
    split2NO4 = EEPROM.read(2388 + k);
    split2NO5 = EEPROM.read(2389 + k);
    split3NO1 = EEPROM.read(2390 + k);
    split3NO2 = EEPROM.read(2391 + k);
    split3NO3 = EEPROM.read(2392 + k);
    split3NO4 = EEPROM.read(2393 + k);
    split3NO5 = EEPROM.read(2394 + k);
  } else {
    split1NO1 = 36;
    split1NO2 = 36;
    split1NO3 = 36;
    split1NO4 = 36;
    split1NO5 = 36;
    split2NO1 = 36;
    split2NO2 = 36;
    split2NO3 = 36;
    split2NO4 = 36;
    split2NO5 = 36;
    split3NO1 = 36;
    split3NO2 = 36;
    split3NO3 = 36;
    split3NO4 = 36;
    split3NO5 = 36;
  }
  splitPC1 = 0; splitPC2 = 0; splitPC3 = 0; // send program change at first split event
  userWrite = 5; //EEPROM.write(2047, user); //update for next power-up <<do after a 5 second delay!!
}



void saveConfig() {
  int k = user;
  for (int i = 0; i < 16; i++) {
    EEPROM.write(i + (k * 16), name.charAt(i));
  }
  for (int i = 0; i < 16; i++) {
    int kk = (k * 144) + i; //user0:160-303, user1:304-447 user9:1456-1599
    EEPROM.write(80 + kk, in1out1[i]);
    EEPROM.write(160 + kk, in1out2[i]);
    EEPROM.write(240 + kk, in1out3[i]);
    EEPROM.write(320 + kk, in1out4[i]);
    EEPROM.write(400 + kk, in1out5[i]);
    EEPROM.write(480 + kk, in2out1[i]);
    EEPROM.write(560 + kk, in2out2[i]);
    EEPROM.write(640 + kk, in2out3[i]);
    EEPROM.write(720 + kk, in2out4[i]);
    EEPROM.write(800 + kk, in2out5[i]);
    EEPROM.write(880 + kk, in3out1[i]);
    EEPROM.write(960 + kk, in3out2[i]);
    EEPROM.write(1040 + kk, in3out3[i]);
    EEPROM.write(1120 + kk, in3out4[i]);
    EEPROM.write(1200 + kk, in3out5[i]);
    EEPROM.write(1280 + kk, in4out1[i]);
    EEPROM.write(1360 + kk, in4out2[i]);
    EEPROM.write(1440 + kk, in4out3[i]);
    EEPROM.write(1520 + kk, in4out4[i]);
    EEPROM.write(1600 + kk, in4out5[i]);
    EEPROM.write(1680 + kk, in5out1[i]);
    EEPROM.write(1760 + kk, in5out2[i]);
    EEPROM.write(1840 + kk, in5out3[i]);
    EEPROM.write(1920 + kk, in5out4[i]);
    EEPROM.write(2000 + kk, in5out5[i]);
  }
  int kk = k * 4; byte o = 0; //to save 2x note overlap (0-14, lowest bit always 0)
  o = overLap[0] << 4; o = split1 | o; EEPROM.write(2080 + kk, o); EEPROM.write(2081 + kk, split1low); EEPROM.write(2082 + kk, split1hi); EEPROM.write(2083 + kk, split1chan1); EEPROM.write(2084 + kk, split1chan2); EEPROM.write(2085 + kk, split1chan3);
  EEPROM.write(2086 + kk, split1chan4); EEPROM.write(2087 + kk, split1chan5);
  o = overLap[1] << 4; o = split2 | o; EEPROM.write(2088 + kk, o); EEPROM.write(2089 + kk, split2low); EEPROM.write(2090 + kk, split2hi); EEPROM.write(2091 + kk, split2chan1); EEPROM.write(2092 + kk, split2chan2); EEPROM.write(2093 + kk, split2chan3);
  EEPROM.write(2094 + kk, split1chan4); EEPROM.write(2095 + kk, split1chan5);
  o = overLap[2] << 4; o = split3 | o; EEPROM.write(2096 + kk, o); EEPROM.write(2097 + kk, split3low); EEPROM.write(2098 + kk, split3hi); EEPROM.write(2099 + kk, split3chan1); EEPROM.write(2100 + kk, split3chan2); EEPROM.write(2101 + kk, split3chan3);
  EEPROM.write(2102 + kk, split1chan4); EEPROM.write(2103 + kk, split1chan5);
  //1780 is next

  for (int i = 0; i < 5; i++) {
    int ii = (k * 4) + i; //user0:
    EEPROM.write(ii + 2230, clk1[i]); //out[] from inX? bit0=clk,bit1=trnspt,bit2=PC,bit3=CC's
    EEPROM.write(ii + 2233, clk2[i]);
    EEPROM.write(ii + 2236, clk3[i]);
    EEPROM.write(ii + 2239, clk4[i]);
    EEPROM.write(ii + 2242, clk5[i]);
  }//1870 is next

  k = user * 4;
  EEPROM.write(2305 + k, split1PC1); //program changes for splits
  EEPROM.write(2306 + k, split1PC2);
  EEPROM.write(2307 + k, split1PC3);
  EEPROM.write(2308 + k, split1PC4);
  EEPROM.write(2309 + k, split1PC5);
  EEPROM.write(2310 + k, split2PC1);
  EEPROM.write(2311 + k, split2PC2);
  EEPROM.write(2312 + k, split2PC3);
  EEPROM.write(2313 + k, split2PC4);
  EEPROM.write(2314 + k, split2PC5);
  EEPROM.write(2315 + k, split3PC1);
  EEPROM.write(2316 + k, split3PC2);
  EEPROM.write(2317 + k, split3PC3);
  EEPROM.write(2318 + k, split3PC4);
  EEPROM.write(2319 + k, split3PC5);
  //1960 is next
  if (user < 4) { //can'r save last config note offsets, uses default
    EEPROM.write(2380 + k, split1NO1);
    EEPROM.write(2381 + k, split1NO2);
    EEPROM.write(2382 + k, split1NO3);
    EEPROM.write(2383 + k, split1NO4);
    EEPROM.write(2384 + k, split1NO5);
    EEPROM.write(2385 + k, split2NO1);
    EEPROM.write(2386 + k, split2NO2);
    EEPROM.write(2387 + k, split2NO3);
    EEPROM.write(2388 + k, split2NO4);
    EEPROM.write(2389 + k, split2NO5);
    EEPROM.write(2390 + k, split3NO1);
    EEPROM.write(2391 + k, split3NO2);
    EEPROM.write(2392 + k, split3NO3);
    EEPROM.write(2393 + k, split3NO4);
    EEPROM.write(2394 + k, split3NO5);
  }

  userWrite = 5;
  OLEDwerds(F("SAVED "), 0, 0, 0);

}



//
