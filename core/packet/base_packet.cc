#include "base_packet.h"

Packet::Packet(){

}

Packet::~Packet(){
 
}

const byte Packet::head = 0x02;
const byte Packet::version[] = {0x30,0x18};
const byte Packet::end  = 0x03; 

