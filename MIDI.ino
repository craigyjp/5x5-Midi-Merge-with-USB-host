void serialEvent1() {
  //  Main MIDI input, (TX is VLT2 output)
  while (Serial1.available()) {
    midi1in = Serial1.read(); //read raw serial data bytes
    if (midi1in == 0xF8) {
      wasClock1 = 5;
      if ((clk1[0] & 0x01) == 1) {
        out1circle[oc1] = 0xF8; oc1++; //clk1[] is clock input on input 1 to [output]
      }
      if ((clk1[1] & 0x01)) {
        out2circle[oc2] = 0xF8; oc2++;
      }
      if ((clk1[2] & 0x01)) {
        out3circle[oc3] = 0xF8; oc3++;
      }
      if ((clk1[3] & 0x01)) {
        out4circle[oc4] = 0xF8; oc4++;
      }
      if ((clk1[4] & 0x01)) {
        out5circle[oc5] = 0xF8; oc5++;
      }
      analogWrite(IN_LED1, 20); inLED1 = 20;
      //      Serial.print("MIDI DATA 1");
    } else {
      //Serial1.write(midi1in);
      rxMIDI1();
    }
  }
}

void serialEvent2() {
  //  Main MIDI input, (TX is VLT2 output)
  while (Serial2.available()) {
    midi2in = Serial2.read(); //read raw serial data byte
    if (midi2in == 0xF8) {
      wasClock2 = 5;
      if ((clk2[0] & 0x01)) {
        out1circle[oc1] = 0xF8; oc1++;
      }
      if ((clk2[1] & 0x01)) {
        out2circle[oc2] = 0xF8; oc2++;
      }
      if ((clk2[2] & 0x01)) {
        out3circle[oc3] = 0xF8; oc3++;
      }
      if ((clk2[3] & 0x01)) {
        out4circle[oc4] = 0xF8; oc4++;
      }
      if ((clk2[4] & 0x01)) {
        out5circle[oc5] = 0xF8; oc5++;
      }
      analogWrite(IN_LED2, 20); inLED2 = 20;
      //      Serial.print("MIDI DATA 2");
    } else {
      rxMIDI2();
    }
  }
}

void serialEvent3() {
  //  Main MIDI input, (TX is VLT2 output)
  while (Serial3.available()) {
    midi3in = Serial3.read(); //read raw serial data byte
    if (midi3in == 0xF8) {
      wasClock3 = 5;
      if ((clk3[0] & 0x01)) {
        out1circle[oc1] = 0xF8; oc1++;
      }
      if ((clk3[1] & 0x01)) {
        out2circle[oc2] = 0xF8; oc2++;
      }
      if ((clk3[2] & 0x01)) {
        out3circle[oc3] = 0xF8; oc3++;
      }
      if ((clk3[3] & 0x01)) {
        out4circle[oc4] = 0xF8; oc4++;
      }
      if ((clk3[4] & 0x01)) {
        out5circle[oc5] = 0xF8; oc5++;
      }
      analogWrite(IN_LED3, 20); inLED3 = 20;
      //      Serial.print("MIDI DATA 3");
    } else {
      rxMIDI3();
    }
  }
}

void usbEvent4() {
//      Serial.print("Midi Type ");
//    Serial.println(rx4Buf[0], HEX);
//    Serial.print("Data1 ");
//    Serial.println(rx4Buf[1]);
//    Serial.print("Data2 ");
//    Serial.println(rx4Buf[2]);
//    Serial.print("Channel ");
//    Serial.println(rx4Buf[3]);
  midi4in = rx4Buf[0];
  if (midi4in == 0xF8) {
    wasClock4 = 5;
    if ((clk4[0] & 0x01)) {
      out1circle[oc1] = 0xF8; oc1++;
    }
    if ((clk4[1] & 0x01)) {
      out2circle[oc2] = 0xF8; oc2++;
    }
    if ((clk4[2] & 0x01)) {
      out3circle[oc3] = 0xF8; oc3++;
    }
    if ((clk4[1] & 0x01)) {
      out4circle[oc4] = 0xF8; oc4++;
    }
    if ((clk4[2] & 0x01)) {
      out5circle[oc5] = 0xF8; oc5++;
    }
    analogWrite(IN_LED4, 20); inLED4 = 20;
  } else {
    rxMIDI4();
  }
}

void usbEvent5() {
  //  Serial.print("Midi Type ");
  //  Serial.println(rx5Buf[0], HEX);
  //  Serial.print("Data1 ");
  //  Serial.println(rx5Buf[1]);
  //  Serial.print("Data2 ");
  //  Serial.println(rx5Buf[2]);
  //  Serial.print("Channel ");
  //  Serial.println(rx5Buf[3]);
  midi5in = rx5Buf[0];
  if (midi5in == 0xF8) {
    wasClock5 = 5;
    if ((clk5[0] & 0x01)) {
      out1circle[oc1] = 0xF8; oc1++;
    }
    if ((clk5[1] & 0x01)) {
      out2circle[oc2] = 0xF8; oc2++;
    }
    if ((clk5[2] & 0x01)) {
      out3circle[oc3] = 0xF8; oc3++;
    }
    if ((clk5[3] & 0x01)) {
      out2circle[oc2] = 0xF8; oc2++;
    }
    if ((clk5[4] & 0x01)) {
      out3circle[oc3] = 0xF8; oc3++;
    }
    analogWrite(IN_LED5, 20); inLED5 = 20;
  } else {
    rxMIDI5();
  }
}

void rxMIDI4()
{
  if (midi4in == 0xFE || midi4in == 0xF8) return;
  if (midi4in == 0xF7) {
    sysExCnt4 = 0; return; //not sure..can't really combine sysex's so maybe just send through on same port out??
  }
  //  if (midi5in == 0xF0 || sysExCnt5) {
  //    sysExCnt5 = 1;
  //    return;
  //  }
  midiChannel4 = (rx4Buf[3] - 1);
  rx4Buf[0] &= 0xf0; //chop channel for now
  if (rx4Buf[0] == 0x90 && rx4Buf[2] == 0) {
    rx4Buf[0] = 0x80; rx4Buf[2] = 64;
  }
  if (rx4Buf[0] == 0xC0) {
    rx4Buf[2] = rx4Buf[1];
  }
  if ((rx4Buf[0] == 0x90 || rx4Buf[0] == 0x80 || rx4Buf[0] == 0xE0 ) && midiChannel4 == split4) { // is on split channel??
    split4handler();
  } else {
    if ((in4out1[midiChannel4] < 16)) { // this chann is assigned?
      byte csw = rx4Buf[0] | (in4out1[midiChannel4] & 0x0F);
      if ((rx4Buf[0] == 0xC0 && !(clk4[0] & 0x04)) || (rx4Buf[0] == 0xB0 && !(clk4[0] & 0x08))) {
        // don't send PC or CC
      } else {
        midiOut1(csw, rx4Buf[1], rx4Buf[2]);
      }
    }
    if ((in4out2[midiChannel4] < 16)) { // this chann is assigned?
      byte csw = rx4Buf[0] | (in4out2[midiChannel4] & 0x0F);
      if ((rx4Buf[0] == 0xC0 && !(clk4[1] & 0x04)) || (rx4Buf[0] == 0xB0 && !(clk4[1] & 0x08))) {
        // don't send PC or CC
      } else {
        midiOut2(csw, rx4Buf[1], rx4Buf[2]);
      }
    }
    if ((in4out3[midiChannel4] < 16)) { // this chann is assigned?
      byte csw = rx4Buf[0] | (in4out3[midiChannel4] & 0x0F);
      if ((rx4Buf[0] == 0xC0 && !(clk4[2] & 0x04)) || (rx4Buf[0] == 0xB0 && !(clk4[2] & 0x08))) {
        // don't send PC or CC
      } else {
        midiOut3(csw, rx4Buf[1], rx4Buf[2]);
      }
    }
    if ((in4out4[midiChannel4] < 16)) { // this chann is assigned?
      byte csw = rx4Buf[0] | (in4out4[midiChannel4] & 0x0F);
      if ((rx4Buf[0] == 0xC0 && !(clk4[3] & 0x04)) || (rx4Buf[0] == 0xB0 && !(clk4[3] & 0x08))) {
        // don't send PC or CC
      } else {
        midiOut4(csw, rx4Buf[1], rx4Buf[2]);
      }
    }
    if ((in4out5[midiChannel4] < 16)) { // this chann is assigned?
      byte csw = rx4Buf[0] | (in4out5[midiChannel4] & 0x0F);
      if ((rx4Buf[0] == 0xC0 && !(clk4[4] & 0x04)) || (rx4Buf[0] == 0xB0 && !(clk4[4] & 0x08))) {
        // don't send PC or CC
      } else {
        midiOut5(csw, rx4Buf[1], rx4Buf[2]);
      }
    }
  }
  analogWrite(IN_LED4, 100); inLED4 = 100;


  switch (midi4in) {
    case 0x90: //m++;break;//noteOn (or off)
    case 0x80: //m++;break;//noteOff
    case 0xA0: //key pressure ignored
    case 0xE0:
    case 0xF2:
    case 0xB0: p3++; break; // CC ignored
    case 0xC0: // PC is 2 byte
    case 0xD0: p3 += 2; break; // also 2 byte
      break;
    case 0xFA:
    case 0xFB:
    case 0xFC:
      wasClock4 = 0;
      if ((clk4[0] & 0x02)) { // send transport messages??
        out1circle[oc1] = midi4in; oc1++;
      }
      if ((clk4[1] & 0x02)) {
        out2circle[oc2] = midi4in; oc2++;
      }
      if ((clk4[2] & 0x02)) {
        out3circle[oc3] = midi4in; oc3++;
      }
      if ((clk4[1] & 0x02)) {
        out4circle[oc4] = midi4in; oc4++;
      }
      if ((clk4[2] & 0x02)) {
        out4circle[oc4] = midi4in; oc5++;
      }
      splitPC4 = 0; //reset so split event sends PC's again
      break;
  }
}

void rxMIDI5()
{
  //    Serial.print("Midi Type ");
  //    Serial.println(rx5Buf[0], HEX);
  //    Serial.print("Data1 ");
  //    Serial.println(rx5Buf[1]);
  //    Serial.print("Data2 ");
  //    Serial.println(rx5Buf[2]);
  //    Serial.print("Channel ");
  //    Serial.println(rx5Buf[3]);
  if (midi5in == 0xFE || midi5in == 0xF8) return;
  if (midi5in == 0xF7) {
    sysExCnt5 = 0; return; //not sure..can't really combine sysex's so maybe just send through on same port out??
  }
  //  if (midi5in == 0xF0 || sysExCnt5) {
  //    sysExCnt5 = 1;
  //    return;
  //  }
  midiChannel5 = (rx5Buf[3] - 1);
  rx5Buf[0] &= 0xf0; //chop channel for now
  //    Serial.print("Midi Type ");
  //    Serial.println(rx5Buf[0], HEX);
  //    Serial.print("Data1 ");
  //    Serial.println(rx5Buf[1]);
  //    Serial.print("Data2 ");
  //    Serial.println(rx5Buf[2]);
  //    Serial.print("Channel ");
  //    Serial.println(rx5Buf[3]);
  if (rx5Buf[0] == 0x90 && rx5Buf[2] == 0) {
    rx5Buf[0] = 0x80; rx5Buf[2] = 64;
  }
  if (rx5Buf[0] == 0xC0) {
    rx5Buf[2] = rx5Buf[1];
  }
  if ((rx5Buf[0] == 0x90 || rx5Buf[0] == 0x80 || rx5Buf[0] == 0xE0 ) && midiChannel5 == split5) { // is on split channel??
    split5handler();
  } else {
    if ((in5out1[midiChannel5] < 16)) { // this chann is assigned?
      byte csw = rx5Buf[0] | (in5out1[midiChannel5] & 0x0F);
      if ((rx5Buf[0] == 0xC0 && !(clk5[0] & 0x04)) || (rx5Buf[0] == 0xB0 && !(clk5[0] & 0x08))) {
        // don't send PC or CC
      } else {
        midiOut1(csw, rx5Buf[1], rx5Buf[2]);
      }
    }
    if ((in5out2[midiChannel5] < 16)) { // this chann is assigned?
      byte csw = rx5Buf[0] | (in5out2[midiChannel5] & 0x0F);
      if ((rx5Buf[0] == 0xC0 && !(clk5[1] & 0x04)) || (rx5Buf[0] == 0xB0 && !(clk5[1] & 0x08))) {
        // don't send PC or CC
      } else {
        midiOut2(csw, rx5Buf[1], rx5Buf[2]);
      }
    }
    if ((in5out3[midiChannel5] < 16)) { // this chann is assigned?
      byte csw = rx5Buf[0] | (in5out3[midiChannel5] & 0x0F);
      if ((rx5Buf[0] == 0xC0 && !(clk5[2] & 0x04)) || (rx5Buf[0] == 0xB0 && !(clk5[2] & 0x08))) {
        // don't send PC or CC
      } else {
        midiOut3(csw, rx5Buf[1], rx5Buf[2]);
      }
    }
    if ((in5out4[midiChannel5] < 16)) { // this chann is assigned?
      byte csw = rx5Buf[0] | (in5out4[midiChannel5] & 0x0F);
      if ((rx5Buf[0] == 0xC0 && !(clk5[3] & 0x04)) || (rx5Buf[0] == 0xB0 && !(clk5[3] & 0x08))) {
        // don't send PC or CC
      } else {
        midiOut4(csw, rx5Buf[1], rx5Buf[2]);
      }
    }
    if ((in5out5[midiChannel5] < 16)) { // this chann is assigned?
      byte csw = rx5Buf[0] | (in5out5[midiChannel5] & 0x0F);
      if ((rx5Buf[0] == 0xC0 && !(clk5[4] & 0x04)) || (rx5Buf[0] == 0xB0 && !(clk5[4] & 0x08))) {
        // don't send PC or CC
      } else {
        midiOut5(csw, rx5Buf[1], rx5Buf[2]);
      }
    }
  }
  analogWrite(IN_LED5, 100); inLED5 = 100;


  switch (midi5in) {
    case 0x90: //m++;break;//noteOn (or off)
    case 0x80: //m++;break;//noteOff
    case 0xA0: //key pressure ignored
    case 0xE0:
    case 0xF2:
    case 0xB0: p3++; break; // CC ignored
    case 0xC0: // PC is 2 byte
    case 0xD0: p3 += 2; break; // also 2 byte
      break;
    case 0xFA:
    case 0xFB:
    case 0xFC:
      wasClock5 = 0;
      if ((clk5[0] & 0x02)) { // send transport messages??
        out1circle[oc1] = midi5in; oc1++;
      }
      if ((clk5[1] & 0x02)) {
        out2circle[oc2] = midi5in; oc2++;
      }
      if ((clk5[2] & 0x02)) {
        out3circle[oc3] = midi5in; oc3++;
      }
      if ((clk5[1] & 0x02)) {
        out4circle[oc4] = midi5in; oc4++;
      }
      if ((clk5[2] & 0x02)) {
        out4circle[oc4] = midi5in; oc5++;
      }
      splitPC5 = 0; //reset so split event sends PC's again
      break;
  }
}

void rxMIDI1() {

  if (midi1in == 0xFE || midi1in == 0xF8) return;
  if (midi1in == 0xF7) {
    sysExCnt1 = 0; return; //not sure..can't really combine sysex's so maybe just send through on same port out??
  }
  if (midi1in == 0xF0 || sysExCnt1) {
    sysExCnt1 = 1;
    return;
  }
  if (p1 == 0 && !(midi1in & 0x80)) {
    p1++; //running status!! use last command again. ALways remove running status
    rx1Buf[0] = lastCom1;
    if ((lastCom1 & 0xF0) != 0xF0 && lastCom1 > 127) { //strip channel here for running status!
      midiChannel1 = lastCom1 & 0x0f;
      rx1Buf[0] &= 0xf0; //chop channel for now
    }
  }

  rx1Buf[p1] = midi1in;
  //

  //--MIDI SENTENCE LOADED----
  if (p1 >= 2) {
    p1 = 0;
    // Serial.println(rx1Buf[0], HEX);
    if (rx1Buf[0] == 0x90 && rx1Buf[2] == 0) {
      rx1Buf[0] = 0x80; rx1Buf[2] = 64;
    }
    if ((rx1Buf[0] == 0x90 || rx1Buf[0] == 0x80 || rx1Buf[0] == 0xE0 ) && midiChannel1 == split1) { // is on split channel??
      split1handler();
    } else {
      if ((in1out1[midiChannel1] < 16)) { // this chann is assigned?
        byte csw = rx1Buf[0] | (in1out1[midiChannel1] & 0x0F);
        if ((rx1Buf[0] == 0xC0 && !(clk1[0] & 0x04)) || (rx1Buf[0] == 0xB0 && !(clk1[0] & 0x08))) {
          // don't send PC
        } else {
          midiOut1(csw, rx1Buf[1], rx1Buf[2]);
        }
      }
      if ((in1out2[midiChannel1] < 16)) { // this chann is assigned?
        byte csw = rx1Buf[0] | (in1out2[midiChannel1] & 0x0F);
        if ((rx1Buf[0] == 0xC0 && !(clk1[1] & 0x04)) || (rx1Buf[0] == 0xB0 && !(clk1[1] & 0x08))) {
          // don't send PC
        } else {
          midiOut2(csw, rx1Buf[1], rx1Buf[2]);
        }
      }
      if ((in1out3[midiChannel1] < 16)) { // this chann is assigned?
        byte csw = rx1Buf[0] | (in1out3[midiChannel1] & 0x0F);
        if ((rx1Buf[0] == 0xC0 && !(clk1[2] & 0x04)) || (rx1Buf[0] == 0xB0 && !(clk1[2] & 0x08))) {
          // don't send PC/cc
        } else {
          midiOut3(csw, rx1Buf[1], rx1Buf[2]);
        }
      }
      if ((in1out4[midiChannel1] < 16)) { // this chann is assigned?
        byte csw = rx1Buf[0] | (in1out4[midiChannel1] & 0x0F);
        if ((rx1Buf[0] == 0xC0 && !(clk1[3] & 0x04)) || (rx1Buf[0] == 0xB0 && !(clk1[3] & 0x08))) {
          // don't send PC
        } else {
          midiOut4(csw, rx1Buf[1], rx1Buf[2]);
        }
      }
      if ((in1out5[midiChannel1] < 16)) { // this chann is assigned?
        byte csw = rx1Buf[0] | (in1out5[midiChannel1] & 0x0F);
        if ((rx1Buf[0] == 0xC0 && !(clk1[4] & 0x04)) || (rx1Buf[0] == 0xB0 && !(clk1[4] & 0x08))) {
          // don't send PC/cc
        } else {
          midiOut5(csw, rx1Buf[1], rx1Buf[2]);
        }
      }
    }
    analogWrite(IN_LED1, 100); inLED1 = 100;
  }

  if (p1 == 1) p1++; //continue loading Command sentence
  if (p1 == 0) {
    if ((midi1in & 0xF0) != 0xF0 && midi1in > 127) { //strip channel
      lastCom1 = midi1in; //for running status
      midiChannel1 = midi1in & 0x0f;
      midi1in &= 0xf0; //chop channel for now
      rx1Buf[0] = midi1in;
    }

    switch (midi1in) {
      case 0x90: //m++;break;//noteOn (or off)
      case 0x80: //m++;break;//noteOff
      case 0xA0: //key pressure ignored
      case 0xE0: //pitch bend
      case 0xF2:
      case 0xB0: p1++; break; // CC ignored
      case 0xC0: // PC is 2 byte
      case 0xD0: p1 += 2; break; // also 2 byte
        break;

      case 0xFA:
      case 0xFB:
      case 0xFC:
        wasClock1 = 0;
        if ((clk1[0] & 0x02)) { // send transport messages??
          out1circle[oc1] = midi1in; oc1++;
        }
        if ((clk1[1] & 0x02)) {
          out2circle[oc2] = midi1in; oc2++;
        }
        if ((clk1[2] & 0x02)) {
          out3circle[oc3] = midi1in; oc3++;
        }
        if ((clk1[3] & 0x02)) {
          out4circle[oc4] = midi1in; oc4++;
        }
        if ((clk1[4] & 0x02)) {
          out5circle[oc5] = midi1in; oc5++;
        }
        splitPC1 = 0; //reset so split event sends PC's again
        break;
    }
  }
}

void rxMIDI2() {

  if (midi2in == 0xFE || midi2in == 0xF8) return;
  if (midi2in == 0xF7) {
    sysExCnt2 = 0; return; //not sure..can't really combine sysex's so maybe just send through on same port out??
  }
  if (midi2in == 0xF0 || sysExCnt2) {
    sysExCnt2 = 1;
    return;
  }
  if (p2 == 0 && !(midi2in & 0x80)) {
    p2++; //running status!! use last command again. ALways remove running status
    rx2Buf[0] = lastCom2;
    if ((lastCom2 & 0xF0) != 0xF0 && lastCom2 > 127) { //strip channel here for running status!
      midiChannel2 = lastCom2 & 0x0f;
      rx2Buf[0] &= 0xf0; //chop channel for now
    }
  }
  rx2Buf[p2] = midi2in;
  //

  //--MIDI SENTENCE LOADED----
  if (p2 >= 2) {
    p2 = 0;
    if (rx2Buf[0] == 0x90 && rx2Buf[2] == 0) {
      rx2Buf[0] = 0x80; rx2Buf[2] = 64;
    }
    if ((rx2Buf[0] == 0x90 || rx2Buf[0] == 0x80 || rx2Buf[0] == 0xE0 ) && midiChannel2 == split2) { // is on split channel??
      split2handler();
    } else {
      if ((in2out1[midiChannel2] < 16)) { // this chann is assigned?
        byte csw = rx2Buf[0] | (in2out1[midiChannel2] & 0x0F);
        if ((rx2Buf[0] == 0xC0 && !(clk2[0] & 0x04)) || (rx2Buf[0] == 0xB0 && !(clk2[0] & 0x08))) {
          // don't send PC or CC
        } else {
          midiOut1(csw, rx2Buf[1], rx2Buf[2]);
        }
      }
      if ((in2out2[midiChannel2] < 16)) { // this chann is assigned?
        byte csw = rx2Buf[0] | (in2out2[midiChannel2] & 0x0F);
        if ((rx2Buf[0] == 0xC0 && !(clk2[1] & 0x04)) || (rx2Buf[0] == 0xB0 && !(clk2[1] & 0x08))) {
          // don't send PC or CC
        } else {
          midiOut2(csw, rx2Buf[1], rx2Buf[2]);
        }
      }
      if ((in2out3[midiChannel2] < 16)) { // this chann is assigned?
        byte csw = rx2Buf[0] | (in2out3[midiChannel2] & 0x0F);
        if ((rx2Buf[0] == 0xC0 && !(clk2[2] & 0x04)) || (rx2Buf[0] == 0xB0 && !(clk2[2] & 0x08))) {
          // don't send PC or CC
        } else {
          midiOut3(csw, rx2Buf[1], rx2Buf[2]);
        }
      }
      if ((in2out4[midiChannel2] < 16)) { // this chann is assigned?
        byte csw = rx2Buf[0] | (in2out4[midiChannel2] & 0x0F);
        if ((rx2Buf[0] == 0xC0 && !(clk2[3] & 0x04)) || (rx2Buf[0] == 0xB0 && !(clk2[3] & 0x08))) {
          // don't send PC or CC
        } else {
          midiOut4(csw, rx2Buf[1], rx2Buf[2]);
        }
      }
      if ((in2out5[midiChannel2] < 16)) { // this chann is assigned?
        byte csw = rx2Buf[0] | (in2out5[midiChannel2] & 0x0F);
        if ((rx2Buf[0] == 0xC0 && !(clk2[4] & 0x04)) || (rx2Buf[0] == 0xB0 && !(clk2[4] & 0x08))) {
          // don't send PC or CC
        } else {
          midiOut5(csw, rx2Buf[1], rx2Buf[2]);
        }
      }
    }
    analogWrite(IN_LED2, 100); inLED2 = 100;
  }

  if (p2 == 1) p2++; //continue loading Command sentence
  if (p2 == 0) {
    if ((midi2in & 0xF0) != 0xF0 && midi2in > 127) { //strip channel
      lastCom2 = midi2in; //for running status
      midiChannel2 = midi2in & 0x0f;
      midi2in &= 0xf0; //chop channel for now
      rx2Buf[0] = midi2in;
    }

    switch (midi2in) {
      case 0x90: //m++;break;//noteOn (or off)
      case 0x80: //m++;break;//noteOff
      case 0xA0: //key pressure ignored
      case 0xE0:
      case 0xF2:
      case 0xB0: p2++; break; // CC ignored
      case 0xC0: // PC is 2 byte
      case 0xD0: p2 += 2; break; // also 2 byte
        break;
      case 0xFA:
      case 0xFB:
      case 0xFC:
        wasClock2 = 0;
        if ((clk2[0] & 0x02)) { // send transport messages??
          out1circle[oc1] = midi2in; oc1++;
        }
        if ((clk2[1] & 0x02)) {
          out2circle[oc2] = midi2in; oc2++;
        }
        if ((clk2[2] & 0x02)) {
          out3circle[oc3] = midi2in; oc3++;
        }
        if ((clk2[3] & 0x02)) {
          out4circle[oc4] = midi2in; oc4++;
        }
        if ((clk2[4] & 0x02)) {
          out5circle[oc5] = midi2in; oc5++;
        }
        splitPC2 = 0; //reset so split event sends PC's again
        break;
    }
  }
}


void rxMIDI3()
{

  if (midi3in == 0xFE || midi3in == 0xF8) return;
  if (midi3in == 0xF7) {
    sysExCnt3 = 0; return; //not sure..can't really combine sysex's so maybe just send through on same port out??
  }
  if (midi3in == 0xF0 || sysExCnt3) {
    sysExCnt3 = 1;
    return;
  }
  midiChannel3 = (rx3Buf[3] - 1);
  rx3Buf[0] &= 0xf0; //chop channel for now

  if (rx3Buf[0] == 0x90 && rx3Buf[2] == 0) {
    rx3Buf[0] = 0x80; rx3Buf[2] = 64;
  }
  if (rx3Buf[0] == 0xC0) {
    rx3Buf[2] = rx3Buf[1];
  }
  if ((rx3Buf[0] == 0x90 || rx3Buf[0] == 0x80 || rx3Buf[0] == 0xE0 ) && midiChannel3 == split3) { // is on split channel??
    split3handler();
  } else {
    if ((in3out1[midiChannel3] < 16)) { // this chann is assigned?
      byte csw = rx3Buf[0] | (in3out1[midiChannel3] & 0x0F);
      if ((rx3Buf[0] == 0xC0 && !(clk3[0] & 0x04)) || (rx3Buf[0] == 0xB0 && !(clk3[0] & 0x08))) {
        // don't send PC or CC
      } else {
        midiOut1(csw, rx3Buf[1], rx3Buf[2]);
      }
    }
    if ((in3out2[midiChannel3] < 16)) { // this chann is assigned?
      byte csw = rx3Buf[0] | (in3out2[midiChannel3] & 0x0F);
      if ((rx3Buf[0] == 0xC0 && !(clk3[1] & 0x04)) || (rx3Buf[0] == 0xB0 && !(clk3[1] & 0x08))) {
        // don't send PC or CC
      } else {
        midiOut2(csw, rx3Buf[1], rx3Buf[2]);
      }
    }
    if ((in3out3[midiChannel3] < 16)) { // this chann is assigned?
      byte csw = rx3Buf[0] | (in3out3[midiChannel3] & 0x0F);
      if ((rx3Buf[0] == 0xC0 && !(clk3[2] & 0x04)) || (rx3Buf[0] == 0xB0 && !(clk3[2] & 0x08))) {
        // don't send PC or CC
      } else {
        midiOut3(csw, rx3Buf[1], rx3Buf[2]);
      }
    }
    if ((in3out4[midiChannel3] < 16)) { // this chann is assigned?
      byte csw = rx3Buf[0] | (in3out4[midiChannel3] & 0x0F);
      if ((rx3Buf[0] == 0xC0 && !(clk3[3] & 0x04)) || (rx3Buf[0] == 0xB0 && !(clk3[3] & 0x08))) {
        // don't send PC or CC
      } else {
        midiOut4(csw, rx3Buf[1], rx3Buf[2]);
      }
    }
    if ((in3out5[midiChannel3] < 16)) { // this chann is assigned?
      byte csw = rx3Buf[0] | (in3out5[midiChannel3] & 0x0F);
      if ((rx3Buf[0] == 0xC0 && !(clk3[4] & 0x04)) || (rx3Buf[0] == 0xB0 && !(clk3[4] & 0x08))) {
        // don't send PC or CC
      } else {
        midiOut5(csw, rx3Buf[1], rx3Buf[2]);
      }
    }
  }
  analogWrite(IN_LED3, 100); inLED3 = 100;


  switch (midi3in) {
    case 0x90: //m++;break;//noteOn (or off)
    case 0x80: //m++;break;//noteOff
    case 0xA0: //key pressure ignored
    case 0xE0:
    case 0xF2:
    case 0xB0: p3++; break; // CC ignored
    case 0xC0: // PC is 2 byte
    case 0xD0: p3 += 2; break; // also 2 byte
      break;
    case 0xFA:
    case 0xFB:
    case 0xFC:
      wasClock3 = 0;
      if ((clk3[0] & 0x02)) { // send transport messages??
        out1circle[oc1] = midi3in; oc1++;
      }
      if ((clk3[1] & 0x02)) {
        out2circle[oc2] = midi3in; oc2++;
      }
      if ((clk3[2] & 0x02)) {
        out3circle[oc3] = midi3in; oc3++;
      }
      splitPC3 = 0; //reset so split event sends PC's again
      break;
  }
}

// ------------MIDI OUTS ---------------

void midiOut1(byte c, byte m, byte v) { // must handle 2 byte messages!
  if (m > 127)return; //stop PC=128 and maybe otehrs...
  if ((c & 0xF0) == 0x90) {
    for (byte i = 0; i < 255; i++) {
      if ((no1Note[i] & 0x80)) { // find opening
        //   Serial.print("non:");Serial.println(m);
        no1Chan[i] = c & 0x0F; no1Note[i] = m; break;
      }
    }
  }
  if ((c & 0xF0) == 0x80) no1remove(c, m);
  out1circle[oc1] = c; oc1++;
  if ((c & 0xF0) != 0xC0 && (c & 0xF0) != 0xD0) {
    out1circle[oc1] = m; oc1++;
  }
  out1circle[oc1] = v; oc1++;
  if ((c & 0xf0) != 0x80) { //don't show noteoffs
    analogWrite(OUT_LED1, v); outLED1 = v;
    // Serial.println(c,HEX);
  }
}

void midiOut2(byte c, byte m, byte v) { // must handle 2 byte messages!
  if (m > 127)return;
  if ((c & 0xF0) == 0x90) {
    for (byte i = 0; i < 255; i++) {
      if ((no2Note[i] & 0x80)) {
        no2Chan[i] = c & 0x0F; no2Note[i] = m; break;
      }
    }
  }
  if ((c & 0xF0) == 0x80) no2remove(c, m);
  out2circle[oc2] = c; oc2++;
  if ((c & 0xF0) != 0xC0 && (c & 0xF0) != 0xD0) {
    out2circle[oc2] = m; oc2++;
  }
  out2circle[oc2] = v; oc2++;
  if ((c & 0xf0) != 0x80) { //don't show noteoffs
    analogWrite(OUT_LED2, v); outLED2 = v;
  }
}
void midiOut3(byte c, byte m, byte v) { // must handle 2 byte messages!
  if (m > 127)return;
  if ((c & 0xF0) == 0x90) {
    for (byte i = 0; i < 255; i++) {
      if ((no3Note[i] & 0x80)) {
        no3Chan[i] = c & 0x0F; no3Note[i] = m; break;
      }
    }
  }
  if ((c & 0xF0) == 0x80) no3remove(c, m);
  out3circle[oc3] = c; oc3++;
  if ((c & 0xF0) != 0xC0 && (c & 0xF0) != 0xD0) {
    out3circle[oc3] = m; oc3++;
  }
  out3circle[oc3] = v; oc3++;
  if ((c & 0xf0) != 0x80) { //don't show noteoffs
    analogWrite(OUT_LED3, v); outLED3 = v;
  }
}

void midiOut4(byte c, byte m, byte v) { // must handle 2 byte messages!
  if (m > 127)return;
  if ((c & 0xF0) == 0x90) {
    for (byte i = 0; i < 255; i++) {
      if ((no4Note[i] & 0x80)) {
        no4Chan[i] = c & 0x0F; no4Note[i] = m; break;
      }
    }
  }
  if ((c & 0xF0) == 0x80) no4remove(c, m);
  out4circle[oc4] = c; oc4++;
  if ((c & 0xF0) != 0xC0 && (c & 0xF0) != 0xD0) {
    out4circle[oc4] = m; oc4++;
  }
  out4circle[oc4] = v; oc4++;
  if ((c & 0xf0) != 0x80) { //don't show noteoffs
    analogWrite(OUT_LED4, v); outLED4 = v;
  }
}

void midiOut5(byte c, byte m, byte v) { // must handle 2 byte messages!
  if (m > 127)return;
  if ((c & 0xF0) == 0x90) {
    for (byte i = 0; i < 255; i++) {
      if ((no5Note[i] & 0x80)) {
        no5Chan[i] = c & 0x0F; no5Note[i] = m; break;
      }
    }
  }
  if ((c & 0xF0) == 0x80) no5remove(c, m);
  out5circle[oc5] = c; oc5++;
  if ((c & 0xF0) != 0xC0 && (c & 0xF0) != 0xD0) {
    out5circle[oc5] = m; oc5++;
  }
  out5circle[oc5] = v; oc5++;
  if ((c & 0xf0) != 0x80) { //don't show noteoffs
    analogWrite(OUT_LED5, v); outLED5 = v;
  }
}

//void midiOut5(byte c, byte m, byte v) { // must handle 2 byte messages!
//  //  Serial.println("We got to here ");
//
//  if (m > 127)return;
//  if ((c & 0xF0) == 0x90) {
//    usbMIDI.send(c, m, v, 0, cable);
//    for (byte i = 0; i < 255; i++) {
//      if ((no5Note[i] & 0x80)) {
//        usbMIDI.send(c, m, v, 0, cable);
//        no5Chan[i] = c & 0x0F; no5Note[i] = m; break;
//      }
//    }
//  }
//  if ((c & 0xF0) == 0x80) no5remove(c, m);
//  usbMIDI.send(c, m, v, 0, cable);
//  if ((c & 0xF0) != 0xC0 && (c & 0xF0) != 0xD0) {
//    out5circle[oc5] = m; oc5++;
//  }
//  out5circle[oc5] = v; oc5++;
//  if ((c & 0xf0) != 0x80) { //don't show noteoffs
//    analogWrite(OUT_LED5, v); outLED5 = v;
//  }
//}

void midiOutF8in1() { //send F8's to which outs? **** but which in's also!!
  if (clk1[0]) {
    out1circle[oc1] = 0xF8; oc1++;
  }
  if (clk2[0]) {
    out2circle[oc2] = 0xF8; oc2++;
  }
  if (clk3[0]) {
    out3circle[oc3] = 0xF8; oc3++;
  }
  if (clk4[0]) {
    out4circle[oc4] = 0xF8; oc4++;
  }
  if (clk5[0]) {
    out5circle[oc5] = 0xF8; oc5++;
  }
}

void split1handler() {
  if (rx1Buf[0] != 0xE0) {
    splitPC1send();
    if (rx1Buf[1] < split1low + overLap[0]) {
      byte note = rx1Buf[1] + split1NO1; byte csw = rx1Buf[0] | (split1chan1 & 0x0f);
      while (note > 127)note += 12;
      if ((split1chan1 & 0x30) == 0x10) midiOut1(csw, note, rx1Buf[2]); //to which outs..
      if ((split1chan1 & 0x30) == 0x20) midiOut2(csw, note, rx1Buf[2]);
      if ((split1chan1 & 0x30) == 0x30) midiOut3(csw, note, rx1Buf[2]);
      if ((split1chan1 & 0x30) == 0x20) midiOut4(csw, note, rx1Buf[2]);
      if ((split1chan1 & 0x30) == 0x30) midiOut5(csw, note, rx1Buf[2]);
    }
    if (rx1Buf[1] >= split1low && rx1Buf[1] < split1hi + overLap[0]) {
      byte note = rx1Buf[1] + split1NO2 - split1low; byte csw = rx1Buf[0] | (split1chan2 & 0x0f);
      while (note > 127)note += 12;
      if ((split1chan2 & 0x30) == 0x10) midiOut1(csw, note, rx1Buf[2]);
      if ((split1chan2 & 0x30) == 0x20) midiOut2(csw, note, rx1Buf[2]);
      if ((split1chan2 & 0x30) == 0x30) midiOut3(csw, note, rx1Buf[2]);
      if ((split1chan2 & 0x30) == 0x20) midiOut4(csw, note, rx1Buf[2]);
      if ((split1chan2 & 0x30) == 0x30) midiOut5(csw, note, rx1Buf[2]);
    }
    if (rx1Buf[1] >= split1hi) {
      byte note = rx1Buf[1] + split1NO3 - split1hi; byte csw = rx1Buf[0] | (split1chan3 & 0x0f);
      while (note > 127)note += 12;
      if ((split1chan3 & 0x30) == 0x10) midiOut1(csw, note, rx1Buf[2]);
      if ((split1chan3 & 0x30) == 0x20) midiOut2(csw, note, rx1Buf[2]);
      if ((split1chan3 & 0x30) == 0x30) midiOut3(csw, note, rx1Buf[2]);
      if ((split1chan3 & 0x30) == 0x20) midiOut4(csw, note, rx1Buf[2]);
      if ((split1chan3 & 0x30) == 0x30) midiOut5(csw, note, rx1Buf[2]);
    }
  } else { // pitch wheel!! must send to all channels in split
    splitPW1send();
  }
}


void split2handler() {
  if (rx2Buf[0] != 0xE0) {
    splitPC2send();
    if (rx2Buf[1] < split2low + overLap[1]) {
      byte note = rx2Buf[1] + split2NO1; byte csw = rx2Buf[0] | (split2chan1 & 0x0f);
      while (note > 127)note += 12;
      if ((split2chan1 & 0x30) == 0x10) midiOut1(csw, note, rx2Buf[2]); //to which outs..
      if ((split2chan1 & 0x30) == 0x20) midiOut2(csw, note, rx2Buf[2]);
      if ((split2chan1 & 0x30) == 0x30) midiOut3(csw, note, rx2Buf[2]);
      if ((split2chan1 & 0x30) == 0x40) midiOut4(csw, note, rx2Buf[2]);
      if ((split2chan1 & 0x30) == 0x50) midiOut5(csw, note, rx2Buf[2]);
    }
    if (rx2Buf[1] >= split2low && rx2Buf[1] < split2hi + overLap[1]) {
      byte note = rx2Buf[1] + split2NO2 - split2low; byte csw = rx2Buf[0] | (split2chan2 & 0x0f);
      while (note > 127)note += 12;
      if ((split2chan2 & 0x30) == 0x10) midiOut1(csw, note, rx2Buf[2]);
      if ((split2chan2 & 0x30) == 0x20) midiOut2(csw, note, rx2Buf[2]);
      if ((split2chan2 & 0x30) == 0x30) midiOut3(csw, note, rx2Buf[2]);
      if ((split2chan2 & 0x30) == 0x40) midiOut4(csw, note, rx2Buf[2]);
      if ((split2chan2 & 0x30) == 0x50) midiOut5(csw, note, rx2Buf[2]);
    }
    if (rx2Buf[1] >= split2hi) {
      byte note = rx2Buf[1] + split2NO3 - split2hi; byte csw = rx2Buf[0] | (split2chan3 & 0x0f);
      while (note > 127)note += 12;
      if ((split2chan3 & 0x30) == 0x10) midiOut1(csw, note, rx2Buf[2]);
      if ((split2chan3 & 0x30) == 0x20) midiOut2(csw, note, rx2Buf[2]);
      if ((split2chan3 & 0x30) == 0x30) midiOut3(csw, note, rx2Buf[2]);
      if ((split2chan3 & 0x30) == 0x40) midiOut4(csw, note, rx2Buf[2]);
      if ((split2chan3 & 0x30) == 0x50) midiOut5(csw, note, rx2Buf[2]);
    }
  } else { // pitch wheel!! must send to all channels in split
    splitPW2send();
  }
}

void split3handler() {
  if (rx3Buf[0] != 0xE0) {
    splitPC3send();
    if (rx3Buf[1] < split3low + overLap[2]) {
      byte note = rx3Buf[1] + split3NO1; byte csw = rx3Buf[0] | (split3chan1 & 0x0f);
      while (note > 127)note += 12;
      if ((split3chan1 & 0x30) == 0x10) midiOut1(csw, note, rx3Buf[2]); //to which outs..
      if ((split3chan1 & 0x30) == 0x20) midiOut2(csw, note, rx3Buf[2]);
      if ((split3chan1 & 0x30) == 0x30) midiOut3(csw, note, rx3Buf[2]);
      if ((split3chan1 & 0x30) == 0x40) midiOut4(csw, note, rx3Buf[2]);
      if ((split3chan1 & 0x30) == 0x50) midiOut5(csw, note, rx3Buf[2]);
    }
    if (rx3Buf[1] >= split3low && rx3Buf[1] < split3hi + overLap[2]) {
      byte note = rx3Buf[1] + split3NO2 - split3low; byte csw = rx3Buf[0] | (split3chan2 & 0x0f);
      while (note > 127)note += 12;
      if ((split3chan2 & 0x30) == 0x10) midiOut1(csw, note, rx3Buf[2]);
      if ((split3chan2 & 0x30) == 0x20) midiOut2(csw, note, rx3Buf[2]);
      if ((split3chan2 & 0x30) == 0x30) midiOut3(csw, note, rx3Buf[2]);
      if ((split3chan2 & 0x30) == 0x40) midiOut4(csw, note, rx3Buf[2]);
      if ((split3chan2 & 0x30) == 0x50) midiOut5(csw, note, rx3Buf[2]);
    }
    if (rx3Buf[1] >= split3hi) {
      byte note = rx3Buf[1] + split3NO3 - split3hi; byte csw = rx3Buf[0] | (split3chan3 & 0x0f);
      while (note > 127)note += 12;
      if ((split3chan3 & 0x30) == 0x10) midiOut1(csw, note, rx3Buf[2]);
      if ((split3chan3 & 0x30) == 0x20) midiOut2(csw, note, rx3Buf[2]);
      if ((split3chan3 & 0x30) == 0x30) midiOut3(csw, note, rx3Buf[2]);
      if ((split3chan3 & 0x30) == 0x40) midiOut4(csw, note, rx3Buf[2]);
      if ((split3chan3 & 0x30) == 0x50) midiOut5(csw, note, rx3Buf[2]);
    }
  } else { // pitch wheel!! must send to all channels in split
    splitPW3send();
  }
}

void split4handler() {
  if (rx4Buf[0] != 0xE0) {
    splitPC4send();
    if (rx4Buf[1] < split4low + overLap[3]) {
      byte note = rx4Buf[1] + split4NO1; byte csw = rx4Buf[0] | (split4chan1 & 0x0f);
      while (note > 127)note += 12;
      if ((split4chan1 & 0x30) == 0x10) midiOut1(csw, note, rx4Buf[2]); //to which outs..
      if ((split4chan1 & 0x30) == 0x20) midiOut2(csw, note, rx4Buf[2]);
      if ((split4chan1 & 0x30) == 0x30) midiOut3(csw, note, rx4Buf[2]);
      if ((split4chan1 & 0x30) == 0x40) midiOut4(csw, note, rx4Buf[2]);
      if ((split4chan1 & 0x30) == 0x50) midiOut5(csw, note, rx4Buf[2]);
    }
    if (rx4Buf[1] >= split4low && rx4Buf[1] < split4hi + overLap[3]) {
      byte note = rx4Buf[1] + split4NO2 - split4low; byte csw = rx4Buf[0] | (split4chan2 & 0x0f);
      while (note > 127)note += 12;
      if ((split4chan2 & 0x30) == 0x10) midiOut1(csw, note, rx4Buf[2]);
      if ((split4chan2 & 0x30) == 0x20) midiOut2(csw, note, rx4Buf[2]);
      if ((split4chan2 & 0x30) == 0x30) midiOut3(csw, note, rx4Buf[2]);
      if ((split4chan2 & 0x30) == 0x40) midiOut4(csw, note, rx4Buf[2]);
      if ((split4chan2 & 0x30) == 0x50) midiOut5(csw, note, rx4Buf[2]);
    }
    if (rx4Buf[1] >= split4hi) {
      byte note = rx4Buf[1] + split4NO3 - split4hi; byte csw = rx4Buf[0] | (split4chan3 & 0x0f);
      while (note > 127)note += 12;
      if ((split4chan3 & 0x30) == 0x10) midiOut1(csw, note, rx4Buf[2]);
      if ((split4chan3 & 0x30) == 0x20) midiOut2(csw, note, rx4Buf[2]);
      if ((split4chan3 & 0x30) == 0x30) midiOut3(csw, note, rx4Buf[2]);
      if ((split4chan3 & 0x30) == 0x40) midiOut4(csw, note, rx4Buf[2]);
      if ((split4chan3 & 0x30) == 0x50) midiOut5(csw, note, rx4Buf[2]);
    }
  } else { // pitch wheel!! must send to all channels in split
    splitPW4send();
  }
}

void split5handler() {
  if (rx5Buf[0] != 0xE0) {
    splitPC5send();
    if (rx5Buf[1] < split5low + overLap[4]) {
      byte note = rx5Buf[1] + split5NO1; byte csw = rx5Buf[0] | (split5chan1 & 0x0f);
      while (note > 127)note += 12;
      if ((split5chan1 & 0x30) == 0x10) midiOut1(csw, note, rx5Buf[2]); //to which outs..
      if ((split5chan1 & 0x30) == 0x20) midiOut2(csw, note, rx5Buf[2]);
      if ((split5chan1 & 0x30) == 0x30) midiOut3(csw, note, rx5Buf[2]);
      if ((split5chan1 & 0x30) == 0x40) midiOut4(csw, note, rx5Buf[2]);
      if ((split5chan1 & 0x30) == 0x50) midiOut5(csw, note, rx5Buf[2]);
    }
    if (rx5Buf[1] >= split5low && rx5Buf[1] < split5hi + overLap[4]) {
      byte note = rx5Buf[1] + split5NO2 - split5low; byte csw = rx5Buf[0] | (split5chan2 & 0x0f);
      while (note > 127)note += 12;
      if ((split5chan1 & 0x30) == 0x10) midiOut1(csw, note, rx5Buf[2]); //to which outs..
      if ((split5chan1 & 0x30) == 0x20) midiOut2(csw, note, rx5Buf[2]);
      if ((split5chan1 & 0x30) == 0x30) midiOut3(csw, note, rx5Buf[2]);
      if ((split5chan1 & 0x30) == 0x40) midiOut4(csw, note, rx5Buf[2]);
      if ((split5chan1 & 0x30) == 0x50) midiOut5(csw, note, rx5Buf[2]);
    }
    if (rx5Buf[1] >= split5hi) {
      byte note = rx5Buf[1] + split5NO3 - split5hi; byte csw = rx5Buf[0] | (split5chan3 & 0x0f);
      while (note > 127)note += 12;
      if ((split5chan1 & 0x30) == 0x10) midiOut1(csw, note, rx5Buf[2]); //to which outs..
      if ((split5chan1 & 0x30) == 0x20) midiOut2(csw, note, rx5Buf[2]);
      if ((split5chan1 & 0x30) == 0x30) midiOut3(csw, note, rx5Buf[2]);
      if ((split5chan1 & 0x30) == 0x40) midiOut4(csw, note, rx5Buf[2]);
      if ((split5chan1 & 0x30) == 0x50) midiOut5(csw, note, rx5Buf[2]);
    }
  } else { // pitch wheel!! must send to all channels in split
    splitPW5send();
  }
}


void splitPC1send() {
  if (splitPC1 == 0) { //send Prog change on each active port for channels used in split
    byte csw = 0xC0 | (split1chan1 & 0x0f); if ((split1chan1 & 0x30) != 0) {
      switch ((split1chan1 & 0x30)) {
        case 0x10: midiOut1(csw, 0, split1PC1 ); break;
        case 0x20: midiOut2(csw, 0, split1PC1 ); break;
        case 0x30: midiOut3(csw, 0, split1PC1 ); break;
        case 0x40: midiOut4(csw, 0, split1PC1 ); break;
        case 0x50: midiOut5(csw, 0, split1PC1 ); break;
      }
    }
    csw = 0xC0 | (split1chan2 & 0x0f); if ((split1chan2 & 0x30) != 0) {
      switch ((split1chan2 & 0x30)) {
        case 0x10: midiOut1(csw, 0, split1PC2 ); break;
        case 0x20: midiOut2(csw, 0, split1PC2 ); break;
        case 0x30: midiOut3(csw, 0, split1PC2 ); break;
        case 0x40: midiOut4(csw, 0, split1PC2 ); break;
        case 0x50: midiOut5(csw, 0, split1PC2 ); break;
      }
    }
    csw = 0xC0 | (split1chan3 & 0x0f); if ((split1chan3 & 0x30) != 0) {
      switch ((split1chan3 & 0x30)) {
        case 0x10: midiOut1(csw, 0, split1PC3 ); break;
        case 0x20: midiOut2(csw, 0, split1PC3 ); break;
        case 0x30: midiOut3(csw, 0, split1PC3 ); break;
        case 0x40: midiOut4(csw, 0, split1PC3 ); break;
        case 0x50: midiOut5(csw, 0, split1PC3 ); break;
      }
    }
    splitPC1 = 1; //could also be re-armed from play/cont/stop commands?
  }
}

void splitPC2send() {
  if (splitPC2 == 0) { //send Prog change on each active port for channels used in split
    byte csw = 0xC0 | (split2chan1 & 0x0f); if ((split2chan1 & 0x30) != 0) {
      switch ((split2chan1 & 0x30)) {
        case 0x10: midiOut1(csw, 0, split2PC1 ); break;
        case 0x20: midiOut2(csw, 0, split2PC1 ); break;
        case 0x30: midiOut3(csw, 0, split2PC1 ); break;
        case 0x40: midiOut4(csw, 0, split2PC1 ); break;
        case 0x50: midiOut5(csw, 0, split2PC1 ); break;
      }
    }
    csw = 0xC0 | (split2chan2 & 0x0f); if ((split2chan2 & 0x30) != 0) {
      switch ((split2chan2 & 0x30)) {
        case 0x10: midiOut1(csw, 0, split2PC2 ); break;
        case 0x20: midiOut2(csw, 0, split2PC2 ); break;
        case 0x30: midiOut3(csw, 0, split2PC2 ); break;
        case 0x40: midiOut4(csw, 0, split2PC2 ); break;
        case 0x50: midiOut5(csw, 0, split2PC2 ); break;
      }
    }
    csw = 0xC0 | (split2chan3 & 0x0f); if ((split2chan3 & 0x30) != 0) {
      switch ((split2chan3 & 0x30)) {
        case 0x10: midiOut1(csw, 0, split2PC3 ); break;
        case 0x20: midiOut2(csw, 0, split2PC3 ); break;
        case 0x30: midiOut3(csw, 0, split2PC3 ); break;
        case 0x40: midiOut4(csw, 0, split2PC3 ); break;
        case 0x50: midiOut5(csw, 0, split2PC3 ); break;
      }
    }
    splitPC2 = 1; //could also be re-armed from play/cont/stop commands?
  }
}

void splitPC3send() {
  if (splitPC3 == 0) { //send Prog change on each active port for channels used in split
    byte csw = 0xC0 | (split3chan1 & 0x0f); if ((split3chan1 & 0x30) != 0) {
      switch ((split3chan1 & 0x30)) {
        case 0x10: midiOut1(csw, 0, split3PC1 ); break;
        case 0x20: midiOut2(csw, 0, split3PC1 ); break;
        case 0x30: midiOut3(csw, 0, split3PC1 ); break;
        case 0x40: midiOut4(csw, 0, split3PC1 ); break;
        case 0x50: midiOut5(csw, 0, split3PC1 ); break;
      }
    }
    csw = 0xC0 | (split3chan2 & 0x0f); if ((split3chan2 & 0x30) != 0) {
      switch ((split3chan2 & 0x30)) {
        case 0x10: midiOut1(csw, 0, split3PC2 ); break;
        case 0x20: midiOut2(csw, 0, split3PC2 ); break;
        case 0x30: midiOut3(csw, 0, split3PC2 ); break;
        case 0x40: midiOut4(csw, 0, split3PC2 ); break;
        case 0x50: midiOut5(csw, 0, split3PC2 ); break;
      }
    }
    csw = 0xC0 | (split3chan3 & 0x0f); if ((split3chan3 & 0x30) != 0) {
      switch ((split3chan3 & 0x30)) {
        case 0x10: midiOut1(csw, 0, split3PC3 ); break;
        case 0x20: midiOut2(csw, 0, split3PC3 ); break;
        case 0x30: midiOut3(csw, 0, split3PC3 ); break;
        case 0x40: midiOut4(csw, 0, split3PC3 ); break;
        case 0x50: midiOut5(csw, 0, split3PC3 ); break;
      }
    }
    splitPC3 = 1; //could also be re-armed from play/cont/stop commands?
  }
}

void splitPC4send() {
  if (splitPC4 == 0) { //send Prog change on each active port for channels used in split
    byte csw = 0xC0 | (split4chan1 & 0x0f); if ((split4chan1 & 0x30) != 0) {
      switch ((split4chan1 & 0x30)) {
        case 0x10: midiOut1(csw, 0, split4PC1 ); break;
        case 0x20: midiOut2(csw, 0, split4PC1 ); break;
        case 0x30: midiOut3(csw, 0, split4PC1 ); break;
        case 0x40: midiOut4(csw, 0, split4PC1 ); break;
        case 0x50: midiOut5(csw, 0, split4PC1 ); break;
      }
    }
    csw = 0xC0 | (split2chan2 & 0x0f); if ((split2chan2 & 0x30) != 0) {
      switch ((split2chan2 & 0x30)) {
        case 0x10: midiOut1(csw, 0, split4PC2 ); break;
        case 0x20: midiOut2(csw, 0, split4PC2 ); break;
        case 0x30: midiOut3(csw, 0, split4PC2 ); break;
        case 0x40: midiOut4(csw, 0, split4PC2 ); break;
        case 0x50: midiOut5(csw, 0, split4PC2 ); break;
      }
    }
    csw = 0xC0 | (split2chan3 & 0x0f); if ((split2chan3 & 0x30) != 0) {
      switch ((split2chan3 & 0x30)) {
        case 0x10: midiOut1(csw, 0, split4PC3 ); break;
        case 0x20: midiOut2(csw, 0, split4PC3 ); break;
        case 0x30: midiOut3(csw, 0, split4PC3 ); break;
        case 0x40: midiOut4(csw, 0, split4PC3 ); break;
        case 0x50: midiOut5(csw, 0, split4PC3 ); break;
      }
    }
    splitPC2 = 1; //could also be re-armed from play/cont/stop commands?
  }
}
void splitPC5send() {
  if (splitPC5 == 0) { //send Prog change on each active port for channels used in split
    byte csw = 0xC0 | (split5chan1 & 0x0f); if ((split5chan1 & 0x30) != 0) {
      switch ((split5chan1 & 0x30)) {
        case 0x10: midiOut1(csw, 0, split5PC1 ); break;
        case 0x20: midiOut2(csw, 0, split5PC1 ); break;
        case 0x30: midiOut3(csw, 0, split5PC1 ); break;
        case 0x40: midiOut4(csw, 0, split5PC1 ); break;
        case 0x50: midiOut5(csw, 0, split5PC1 ); break;
      }
    }
    csw = 0xC0 | (split5chan2 & 0x0f); if ((split5chan2 & 0x30) != 0) {
      switch ((split5chan2 & 0x30)) {
        case 0x10: midiOut1(csw, 0, split5PC2 ); break;
        case 0x20: midiOut2(csw, 0, split5PC2 ); break;
        case 0x30: midiOut3(csw, 0, split5PC2 ); break;
        case 0x40: midiOut4(csw, 0, split5PC2 ); break;
        case 0x50: midiOut5(csw, 0, split5PC2 ); break;
      }
    }
    csw = 0xC0 | (split5chan3 & 0x0f); if ((split5chan3 & 0x30) != 0) {
      switch ((split5chan3 & 0x30)) {
        case 0x10: midiOut1(csw, 0, split5PC3 ); break;
        case 0x20: midiOut2(csw, 0, split5PC3 ); break;
        case 0x30: midiOut3(csw, 0, split5PC3 ); break;
        case 0x40: midiOut4(csw, 0, split5PC3 ); break;
        case 0x50: midiOut5(csw, 0, split5PC3 ); break;
      }
    }
    splitPC3 = 1; //could also be re-armed from play/cont/stop commands?
  }
}

void splitPW1send() {
  byte csw = 0xE0 | (split1chan1 & 0x0f); if ((split1chan1 & 0x30) != 0) {
    switch ((split1chan1 & 0x30)) {
      case 0x10: midiOut1(csw, rx1Buf[1], rx1Buf[2]); break;
      case 0x20: midiOut2(csw, rx1Buf[1], rx1Buf[2]); break;
      case 0x30: midiOut3(csw, rx1Buf[1], rx1Buf[2]); break;
      case 0x40: midiOut4(csw, rx1Buf[1], rx1Buf[2]); break;
      case 0x50: midiOut5(csw, rx1Buf[1], rx1Buf[2]); break;
    }
  }
  csw = 0xE0 | (split1chan2 & 0x0f); if ((split1chan2 & 0x30) != 0) {
    switch ((split1chan2 & 0x30)) {
      case 0x10: midiOut1(csw, rx1Buf[1], rx1Buf[2]); break;
      case 0x20: midiOut2(csw, rx1Buf[1], rx1Buf[2]); break;
      case 0x30: midiOut3(csw, rx1Buf[1], rx1Buf[2]); break;
      case 0x40: midiOut4(csw, rx1Buf[1], rx1Buf[2]); break;
      case 0x50: midiOut5(csw, rx1Buf[1], rx1Buf[2]); break;
    }
  }
  csw = 0xE0 | (split1chan3 & 0x0f); if ((split1chan3 & 0x30) != 0) {
    switch ((split1chan3 & 0x30)) {
      case 0x10: midiOut1(csw, rx1Buf[1], rx1Buf[2] ); break;
      case 0x20: midiOut2(csw, rx1Buf[1], rx1Buf[2]); break;
      case 0x30: midiOut3(csw, rx1Buf[1], rx1Buf[2]); break;
      case 0x40: midiOut4(csw, rx1Buf[1], rx1Buf[2]); break;
      case 0x50: midiOut5(csw, rx1Buf[1], rx1Buf[2]); break;
    }
  }
}

void splitPW2send() {
  byte csw = 0xE0 | (split2chan1 & 0x0f); if ((split2chan1 & 0x30) != 0) {
    switch ((split2chan1 & 0x30)) {
      case 0x10: midiOut1(csw, rx2Buf[1], rx2Buf[2]); break;
      case 0x20: midiOut2(csw, rx2Buf[1], rx2Buf[2]); break;
      case 0x30: midiOut3(csw, rx2Buf[1], rx2Buf[2]); break;
      case 0x40: midiOut4(csw, rx2Buf[1], rx2Buf[2]); break;
      case 0x50: midiOut5(csw, rx2Buf[1], rx2Buf[2]); break;
    }
  }
  csw = 0xE0 | (split2chan2 & 0x0f); if ((split2chan2 & 0x30) != 0) {
    switch ((split2chan2 & 0x30)) {
      case 0x10: midiOut1(csw, rx2Buf[1], rx2Buf[2]); break;
      case 0x20: midiOut2(csw, rx2Buf[1], rx2Buf[2]); break;
      case 0x30: midiOut3(csw, rx2Buf[1], rx2Buf[2]); break;
      case 0x40: midiOut4(csw, rx2Buf[1], rx2Buf[2]); break;
      case 0x50: midiOut5(csw, rx2Buf[1], rx2Buf[2]); break;
    }
  }
  csw = 0xE0 | (split2chan3 & 0x0f); if ((split2chan3 & 0x30) != 0) {
    switch ((split2chan3 & 0x30)) {
      case 0x10: midiOut1(csw, rx2Buf[1], rx2Buf[2] ); break;
      case 0x20: midiOut2(csw, rx2Buf[1], rx2Buf[2]); break;
      case 0x30: midiOut3(csw, rx2Buf[1], rx2Buf[2]); break;
      case 0x40: midiOut4(csw, rx2Buf[1], rx2Buf[2]); break;
      case 0x50: midiOut5(csw, rx2Buf[1], rx2Buf[2]); break;
    }
  }
}

void splitPW3send() {
  byte csw = 0xE0 | (split3chan1 & 0x0f); if ((split3chan1 & 0x30) != 0) {
    switch ((split3chan1 & 0x30)) {
      case 0x10: midiOut1(csw, rx3Buf[1], rx3Buf[2]); break;
      case 0x20: midiOut2(csw, rx3Buf[1], rx3Buf[2]); break;
      case 0x30: midiOut3(csw, rx3Buf[1], rx3Buf[2]); break;
      case 0x40: midiOut4(csw, rx3Buf[1], rx3Buf[2]); break;
      case 0x50: midiOut5(csw, rx3Buf[1], rx3Buf[2]); break;
    }
  }
  csw = 0xE0 | (split3chan2 & 0x0f); if ((split3chan2 & 0x30) != 0) {
    switch ((split3chan2 & 0x30)) {
      case 0x10: midiOut1(csw, rx3Buf[1], rx3Buf[2]); break;
      case 0x20: midiOut2(csw, rx3Buf[1], rx3Buf[2]); break;
      case 0x30: midiOut3(csw, rx3Buf[1], rx3Buf[2]); break;
      case 0x40: midiOut4(csw, rx3Buf[1], rx3Buf[2]); break;
      case 0x50: midiOut5(csw, rx3Buf[1], rx3Buf[2]); break;
    }
  }
  csw = 0xE0 | (split3chan3 & 0x0f); if ((split3chan3 & 0x30) != 0) {
    switch ((split3chan3 & 0x30)) {
      case 0x10: midiOut1(csw, rx3Buf[1], rx3Buf[2] ); break;
      case 0x20: midiOut2(csw, rx3Buf[1], rx3Buf[2]); break;
      case 0x30: midiOut3(csw, rx3Buf[1], rx3Buf[2]); break;
      case 0x40: midiOut4(csw, rx3Buf[1], rx3Buf[2]); break;
      case 0x50: midiOut5(csw, rx3Buf[1], rx3Buf[2]); break;
    }
  }
}

void splitPW4send() {
  byte csw = 0xE0 | (split4chan1 & 0x0f); if ((split4chan1 & 0x30) != 0) {
    switch ((split4chan1 & 0x30)) {
      case 0x10: midiOut1(csw, rx4Buf[1], rx4Buf[2]); break;
      case 0x20: midiOut2(csw, rx4Buf[1], rx4Buf[2]); break;
      case 0x30: midiOut3(csw, rx4Buf[1], rx4Buf[2]); break;
      case 0x40: midiOut4(csw, rx4Buf[1], rx4Buf[2]); break;
      case 0x50: midiOut5(csw, rx4Buf[1], rx4Buf[2]); break;
    }
  }
  csw = 0xE0 | (split4chan2 & 0x0f); if ((split4chan2 & 0x30) != 0) {
    switch ((split4chan2 & 0x30)) {
      case 0x10: midiOut1(csw, rx4Buf[1], rx4Buf[2]); break;
      case 0x20: midiOut2(csw, rx4Buf[1], rx4Buf[2]); break;
      case 0x30: midiOut3(csw, rx4Buf[1], rx4Buf[2]); break;
      case 0x40: midiOut4(csw, rx4Buf[1], rx4Buf[2]); break;
      case 0x50: midiOut5(csw, rx4Buf[1], rx4Buf[2]); break;
    }
  }
  csw = 0xE0 | (split4chan3 & 0x0f); if ((split4chan3 & 0x30) != 0) {
    switch ((split4chan3 & 0x30)) {
      case 0x10: midiOut1(csw, rx4Buf[1], rx4Buf[2]); break;
      case 0x20: midiOut2(csw, rx4Buf[1], rx4Buf[2]); break;
      case 0x30: midiOut3(csw, rx4Buf[1], rx4Buf[2]); break;
      case 0x40: midiOut4(csw, rx4Buf[1], rx4Buf[2]); break;
      case 0x50: midiOut5(csw, rx4Buf[1], rx4Buf[2]); break;
    }
  }
}

void splitPW5send() {
  byte csw = 0xE0 | (split5chan1 & 0x0f); if ((split5chan1 & 0x30) != 0) {
    switch ((split5chan1 & 0x30)) {
      case 0x10: midiOut1(csw, rx5Buf[1], rx5Buf[2]); break;
      case 0x20: midiOut2(csw, rx5Buf[1], rx5Buf[2]); break;
      case 0x30: midiOut3(csw, rx5Buf[1], rx5Buf[2]); break;
      case 0x40: midiOut4(csw, rx5Buf[1], rx5Buf[2]); break;
      case 0x50: midiOut5(csw, rx5Buf[1], rx5Buf[2]); break;
    }
  }
  csw = 0xE0 | (split5chan2 & 0x0f); if ((split5chan2 & 0x30) != 0) {
    switch ((split5chan2 & 0x30)) {
      case 0x10: midiOut1(csw, rx5Buf[1], rx5Buf[2]); break;
      case 0x20: midiOut2(csw, rx5Buf[1], rx5Buf[2]); break;
      case 0x30: midiOut3(csw, rx5Buf[1], rx5Buf[2]); break;
      case 0x40: midiOut4(csw, rx5Buf[1], rx5Buf[2]); break;
      case 0x50: midiOut5(csw, rx5Buf[1], rx5Buf[2]); break;
    }
  }
  csw = 0xE0 | (split5chan3 & 0x0f); if ((split5chan3 & 0x30) != 0) {
    switch ((split3chan3 & 0x30)) {
      case 0x10: midiOut1(csw, rx5Buf[1], rx5Buf[2]); break;
      case 0x20: midiOut2(csw, rx5Buf[1], rx5Buf[2]); break;
      case 0x30: midiOut3(csw, rx5Buf[1], rx5Buf[2]); break;
      case 0x40: midiOut4(csw, rx5Buf[1], rx5Buf[2]); break;
      case 0x50: midiOut5(csw, rx5Buf[1], rx5Buf[2]); break;
    }
  }
}

void no1remove(byte c, byte n) {
  c &= 0x0F;
  for (byte i = 0; i < 255; i++) {
    if (!(no1Note[i] & 0x80)) {
      if (no1Note[i] == n && no1Chan[i] == c) {
        no1Note[i] |= 0x80; //preserve in case need in future
        break;
      }
    }
  }
}

void no2remove(byte c, byte n) {
  c &= 0x0F;
  for (byte i = 0; i < 255; i++) {
    if (!(no2Note[i] & 0x80)) {
      if (no2Note[i] == n && no2Chan[i] == c) {
        no2Note[i] |= 0x80; //preserve in case need in future
        break;
      }
    }
  }
}

void no3remove(byte c, byte n) {
  c &= 0x0F;
  for (byte i = 0; i < 255; i++) {
    if (!(no3Note[i] & 0x80)) {
      if (no3Note[i] == n && no3Chan[i] == c) {
        no3Note[i] |= 0x80; //preserve in case need in future
        break;
      }
    }
  }
}

void no4remove(byte c, byte n) {
  c &= 0x0F;
  for (byte i = 0; i < 255; i++) {
    if (!(no4Note[i] & 0x80)) {
      if (no4Note[i] == n && no4Chan[i] == c) {
        no4Note[i] |= 0x80; //preserve in case need in future
        break;
      }
    }
  }
}

void no5remove(byte c, byte n) {
  c &= 0x0F;
  for (byte i = 0; i < 255; i++) {
    if (!(no5Note[i] & 0x80)) {
      if (no5Note[i] == n && no5Chan[i] == c) {
        no5Note[i] |= 0x80; //preserve in case need in future
        break;
      }
    }
  }
}

void allNotesOff(byte c, byte o) { //called when config is changed. c is channel, if 16 then is all chans. o is output0-2, if 4 then all
  // most now use all of these at once in menus
  //Serial.print("ANO--");Serial.print(c);Serial.print(" o:");Serial.println(o);
  for (byte i = 0; i < 255; i++) {
    if (o == 0 || o == 4) {
      if (!(no1Note[i] & 0x80)) {
        if (no1Chan[i] == c || c == 16) {
          // Serial.print("1noff:");Serial.print(no1Chan[i] | 0x80,HEX);Serial.print(" # ");Serial.println(no1Note[i]);
          out1circle[oc1] = no1Chan[i] | 0x80; oc1++; out1circle[oc1] = no1Note[i]; oc1++; out1circle[oc1] = 0x40; oc1++;
          no1Note[i] |= 0x80; //preserve in case need in future
        }
      }
    }
    if (o == 1 || o == 4) {
      if (!(no2Note[i] & 0x80)) {
        if (no2Chan[i] == c || c == 16) {
          // Serial.print("2noff:");Serial.print(no2Chan[i] | 0x80,HEX);Serial.print(" # ");Serial.println(no2Note[i]);
          out2circle[oc2] = (no2Chan[i] | 0x80); oc2++; out2circle[oc2] = no2Note[i]; oc2++; out2circle[oc2] = 0x40; oc2++;
          no2Note[i] |= 0x80; //preserve in case need in future
        }
      }
    }
    if (o == 2 || o == 4) {
      if (!(no3Note[i] & 0x80)) {
        // Serial.print("3noff:");Serial.print(no3Chan[i] | 0x80,HEX);Serial.print(" # ");Serial.println(no3Note[i]);
        if (no3Chan[i] == c || c == 16) {
          out3circle[oc3] = no3Chan[i] | 0x80; oc3++; out3circle[oc3] = no3Note[i]; oc3++; out3circle[oc3] = 0x40; oc3++;
          no3Note[i] |= 0x80; //preserve in case need in future
        }
      }
    }
    if (o == 3 || o == 4) {
      if (!(no4Note[i] & 0x80)) {
        // Serial.print("4noff:");Serial.print(no4Chan[i] | 0x80,HEX);Serial.print(" # ");Serial.println(no4Note[i]);
        if (no4Chan[i] == c || c == 16) {
          out4circle[oc4] = no4Chan[i] | 0x80; oc4++; out4circle[oc4] = no4Note[i]; oc4++; out4circle[oc4] = 0x40; oc4++;
          no4Note[i] |= 0x80; //preserve in case need in future
        }
      }
    }
    if (o == 4 || o == 4) {
      if (!(no5Note[i] & 0x80)) {
        // Serial.print("5noff:");Serial.print(no5Chan[i] | 0x80,HEX);Serial.print(" # ");Serial.println(no5Note[i]);
        if (no5Chan[i] == c || c == 16) {
          out5circle[oc5] = no5Chan[i] | 0x80; oc5++; out5circle[oc5] = no5Note[i]; oc5++; out5circle[oc5] = 0x40; oc5++;
          no5Note[i] |= 0x80; //preserve in case need in future
        }
      }
    }
  }
}
