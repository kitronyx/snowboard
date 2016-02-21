/*
 Snowforce.cpp
 Copyright (c) 2014 Kitronyx http://www.kitronyx.com
 GPL V3.0
*/

#include "Snowforce.h"

void Snowforce::begin(void)
{
    for (int i = 0; i < 180; i++) data[i] = 0x00;
}

void Snowforce::read(byte * force)
{
    // configuration
    byte snowforceaddress = 0x14;
    int npacket = 6;
    unsigned int lenpacket = 32;
    int ndata = 30;
    // variables
    int packet_index_snowforce = 0;
    int packet_index = 0;
    int data_index = 0;
    byte current_data;

    // Get six packet with 32 byte size
    Wire.requestFrom(snowforceaddress, lenpacket);

    packet_index_snowforce = Wire.read();
    data_index = Wire.read();

    if (packet_index_snowforce != packet_index) packet_index = packet_index_snowforce;

    for (int j = 0; j < ndata; j++)
    {
        current_data = Wire.read();
        data[data_index + j] = current_data;
    }

    packet_index++;
    if (packet_index == npacket) packet_index = 0;

    for (int i = packet_index; i < npacket; i++)
    {
        Wire.requestFrom(snowforceaddress, lenpacket);

        packet_index_snowforce = Wire.read();
        data_index = Wire.read();

        // error handling - check packet index.
        if (packet_index_snowforce != packet_index)
        {
        }

        for (int j = 0; j < ndata; j++)
        {
            current_data = Wire.read();
            data[data_index + j] = current_data;
        }

        packet_index++;
        if (packet_index == npacket) packet_index = 0;
    }
    
    // deliver data to host.
    for (int i = 0; i < 160; i++) force[i] = data[i];
}