#include "DEV_Config.h"
#include "LTR390.h"

UDOUBLE UV,ALS;
void setup() {
  if(LTR390_Init() != 0){
      Serial.print("init err!!!");
      while(1);
  }
  LTR390_SetIntVal(5, 20);

  pinMode(8, INPUT);
  
}

void loop() {
    UV = LTR390_UVS();
    Serial.print("UV = ");
    Serial.println(UV);
     DEV_Delay_ms(500);
  if(digitalRead(8) == 1){
      Serial.println("INT");
  }
     
    /*ALS = LTR390_ALS();
    Serial.print("ALS = ");
    Serial.println(ALS);
    DEV_Delay_ms(500);*/
  
}
