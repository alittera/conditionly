
#include <ConditionlyDaikin.h>
#include <IRremote.h>
#include "MbedJSONValue.h"



void ConditionlyDaikin::on()
{
    daikin[13] |= 0x01;
    checksum();
}

unsigned char * ConditionlyDaikin::getDaikin()
{
    return daikin;
}

void ConditionlyDaikin::off()
{
    daikin[13] &= 0xFE;
    checksum();
}

void ConditionlyDaikin::setPower(uint8_t state)
{
    if (state == 0) {
        off();
    }else {
        on();
    }
}


void ConditionlyDaikin::setSwing_on()
{
    daikin[16] |=0x0f;
    checksum();
}

void ConditionlyDaikin::setSwing_off()
{
    daikin[16] &=0xf0;
    checksum();
}

void ConditionlyDaikin::setSwing(uint8_t state)
{
    if (state == 0) {
        setSwing_off();
    }else {
        setSwing_on();
    }
}

void ConditionlyDaikin::setSwingLR_on()
{
    daikin[17] = daikin[17] | 0x0F;
    checksum();
}

void ConditionlyDaikin::setSwingLR_off()
{
    daikin[17] = daikin[17] & 0xF0;
    checksum();
}

void ConditionlyDaikin::setSwingLR(uint8_t state)
{
    if (state == 0) {
        setSwingLR_off();
    }else {
        setSwingLR_on();
    }
}

void ConditionlyDaikin::setMode(uint8_t mode)
{
    uint8_t trmode = vModeTable[mode];
    if (mode>=0 && mode <=4)
    {
        daikin[13] = (trmode << 4) | (daikin[13] & 0x01);
        checksum();
    }
}

// 0~4 speed,5 auto,6 moon
void ConditionlyDaikin::setFan(uint8_t speed)
{
    uint8_t fan = vFanTable[speed];
    if (speed>=0 && speed <=6)
    {
        daikin[16] &= 0x0f;
        daikin[16] |= fan;
        checksum();
    }
}



void ConditionlyDaikin::setTemp(uint8_t temp)
{
    if (temp >= 18 && temp<=32)
    {
        daikin[14] = (temp)*2;
        checksum();
    }
}

void ConditionlyDaikin::sendCommand()
{
      checksum();
      _irsend.sendDaikin(daikin, 8,0);
      wait_ms(29);
      _irsend.sendDaikin(daikin, 19,8);
}
//



//private function
void ConditionlyDaikin::checksum()
{
    uint8_t sum = 0;
    uint8_t i;


    for(i = 0; i <= 6; i++){
        sum += daikin[i];
    }

        daikin[7] = sum &0xFF;

        sum=0;
    for(i = 8; i <= 25; i++){
        sum += daikin[i];
        }

        daikin[26] = sum &0xFF;


}

void ConditionlyDaikin::sendFromJson(const  char * json )
{
    
    MbedJSONValue command;
 
    parse(command, json);

   
    uint8_t power = (uint8_t) command["power"].get<int>();
    uint8_t temp = (uint8_t) command["temp"].get<int>();
    uint8_t mode = (uint8_t) command["mode"].get<int>();
    uint8_t fan = (uint8_t) command["fan"].get<int>();
    uint8_t swing = (uint8_t) command["swing"].get<int>();
    uint8_t swingLR = (uint8_t) command["swingLR"].get<int>();
    
    

    
    setPower(power);
    
    setTemp(temp);
    setMode(mode);
    setFan(fan);
    
    setSwing(swing);
    setSwingLR(swingLR);

    checksum();
    sendCommand();
}


