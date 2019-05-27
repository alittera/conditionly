
#ifndef ConditionlyDaikin_h
#define ConditionlyDaikin_h
#include <IRremote.h>

typedef unsigned char byte; 
#define ConditionlyDaikin_COMMAND_LENGTH 27
class ConditionlyDaikin
{
public:

	ConditionlyDaikin(PinName sendpin):_irsend(sendpin){

	    vFanTable[0]= 0x30;
	    vFanTable[1]= 0x40;
	    vFanTable[2]= 0x50;
	    vFanTable[3]= 0x60;
	    vFanTable[4]= 0x70;
	    vFanTable[5]= 0xa0;
	    vFanTable[6]= 0xb0;
	     
	    vModeTable[0]= 0x6;
	    vModeTable[0]= 0x3;
	    vModeTable[0]= 0x2;
	    vModeTable[0]= 0x4;
	    vModeTable[0]= 0x00;
	     
	    daikin[0]=0x11;
		daikin[1]=0xDA;
		daikin[2]=0x27;
		daikin[3]=0xF0;
		daikin[4]=0x00;
		daikin[5]=0x00;
		daikin[6]=0x00;
		daikin[7]=0x20;
		daikin[8]=0x11;
		daikin[9]=0xDA;
		daikin[10]=0x27;
		daikin[11]=0x00;
		daikin[12]=0x00;
		daikin[13]=0x41;
		daikin[14]=0x1E;
		daikin[15]=0x00;
		daikin[16]=0xB0;
		daikin[17]=0x00;
		daikin[18]=0x00;
		daikin[19]=0x00;
		daikin[20]=0x00;
		daikin[21]=0x00;
		daikin[22]=0x00;
		daikin[23]=0xC1;
		daikin[24]=0x80;
		daikin[25]=0x00;
		daikin[26]=0xE3;
     
     };

    void on();
    void off();
    void setDaikin();
    void setPower(uint8_t state);
    void setSwing_on();
    void setSwing_off();
    void setSwing(uint8_t state);
	void setSwingLR_on();
	void setSwingLR_off();
	void setSwingLR(uint8_t state);
    void setMode(uint8_t mode);//0 FAN, 1 COOL, 2 DRY, 3 HEAT,4 AUTO
    void setFan(uint8_t speed);// 0~4 speed,5 auto,6 moon
    void setTemp(uint8_t temp);//23 ~ 33
    void sendCommand();
    unsigned char * getDaikin();
    void description();
    //


private:
    //IRsend _irsend;
	unsigned char daikinHeader[8];

    unsigned char daikin[ConditionlyDaikin_COMMAND_LENGTH];
    
    byte vFanTable[7];

    byte vModeTable[5];
    
    uint8_t	irReceiveData[25];
    
    void checksum();

    void receivedIRUpdateToSendBuffer(uint8_t *recvData);
    

    
    IRsend _irsend;
    
};
#endif

