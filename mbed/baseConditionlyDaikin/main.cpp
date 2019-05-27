
#include "mbed.h"
#include "ConditionlyDaikin/ConditionlyDaikin.h"
Serial pc(USBTX, USBRX); 


int main() {
    

    ConditionlyDaikin irdaikin(D13);
    
  
    pc.baud(9600);
    
    while(1) {
        pc.printf("Sending... \n");
        
        irdaikin.on();
        irdaikin.setFan(6);//FAN speed to MAX
        irdaikin.setTemp(22);
        
        irdaikin.setSwingLR_on();
        irdaikin.setSwing_on();
        irdaikin.sendCommand();
        
        wait(2);

    }
}