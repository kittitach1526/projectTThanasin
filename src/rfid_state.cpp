#include "rfid_state.h"
rfid_state rf_st;
#include <rdm6300.h>

#define RDM6300_RX_PIN  16
Rdm6300 rdm6300;
rfid_state::rfid_state()
{
    
}
void rfid_state::Init_rfid()
{
    rdm6300.begin(RDM6300_RX_PIN);
    Serial.println("Init rfid complete ");
}

void rfid_state::read_rfid()
{
    if(rdm6300.update())
    {
        result_rfid = String(rdm6300.get_tag_id());
    }
}
