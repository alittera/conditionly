

#include "IRremote.h"
#include "IRremoteInt.h"

//==============================================================================
//
//
//                              DAIKIN LITTERA
//
//
//==============================================================================





#define DYIRDAIKIN_FREQUENCY    38

//DAIKIN
#define DYIRDAIKIN_HDR_MARK     3600 //DAIKIN_ZERO_MARK*8
#define DYIRDAIKIN_HDR_SPACE    1600 //DAIKIN_ZERO_MARK*4
#define DYIRDAIKIN_ONE_SPACE    1300
#define DYIRDAIKIN_ONE_MARK     400
#define DYIRDAIKIN_ZERO_MARK    400
#define DYIRDAIKIN_ZERO_SPACE   428


// IR detector output is active low
#define MARK  0
#define SPACE 1

//+=============================================================================
//


void  IRsend::daikinWarm ()
{
    _pwm.write(0.5);
    IRsend::custom_delay_usec(100);
    _pwm.write(0.0);
    IRsend::custom_delay_usec(5);
}


void IRsend::sendDaikin(unsigned char buf[], int len, int start) {
    int data2;

    daikinWarm();

    enableIROut(DYIRDAIKIN_FREQUENCY);
    mark(DYIRDAIKIN_HDR_MARK);
    space(DYIRDAIKIN_HDR_SPACE);

    for (int i = start; i < start+len; i++) {
        data2=buf[i];

        for (int j = 0; j < 8; j++) {
            if ((1 << j & data2)) {
                mark(DYIRDAIKIN_ONE_MARK);
                space(DYIRDAIKIN_ONE_SPACE);
            }
            else {
                mark(DYIRDAIKIN_ZERO_MARK);
                space(DYIRDAIKIN_ZERO_SPACE);

            }
        }

    }
    mark(DYIRDAIKIN_ONE_MARK);
    space(DYIRDAIKIN_ZERO_SPACE);
}

//+=============================================================================


