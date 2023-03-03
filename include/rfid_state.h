#ifndef rfid_state_H
#define rfid_state_H

#include <Arduino.h>

class rfid_state
{

    public :
        rfid_state();
        void Init_rfid();
        void read_rfid();

        String result_rfid="";
        


    private :


};
extern rfid_state rf_st;
#endif