#include <DS1085.h>

DS1085 fSynth(0xB0);

void setup(){
  Serial.begin(9600);
  fSynth.begin();
}

void loop(){
  test();
  delay(10000);
}

void test(){
  Serial.print("DAC: 0x");
  Serial.println(fSynth.getDAC(),HEX);
  
  Serial.print("OFFSET: 0x");
  Serial.println(fSynth.getOFFSET(),HEX);
  
  Serial.print("OFFSET (Relative): ");
  Serial.println(fSynth.get_Relative_OFFSET());
  
  Serial.print("MUX: 0x");
  Serial.println(fSynth.getMUX(),HEX);
  
  Serial.print("==> DIV1 : 0b");
  Serial.println(fSynth.getDIV1(),BIN);
  
  Serial.print("==> PS0 : 0b");
  Serial.println(fSynth.getPS0(),BIN);
  
  Serial.print("==> PS1 : 0b");
  Serial.println(fSynth.getPS1(),BIN);
  
  Serial.print("DIV: 0x");
  Serial.println(fSynth.getDIV(),HEX);
  
  Serial.print("ADDR: 0x");
  Serial.println(fSynth.getADDR(),HEX);
  
  Serial.print("RANGE: 0x");
  Serial.println(fSynth.getRANGE(),HEX);
  
  Serial.println("");
  Serial.println("");
  Serial.println("");
}
