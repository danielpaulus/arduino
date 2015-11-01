// receiver.pde
//
// Simple example of how to use VirtualWire to receive messages
// Implements a simplex (one-way) receiver with an Rx-B1 module
//
// See VirtualWire.h for detailed API docs
// Author: Mike McCauley (mikem@airspayce.com)
// Copyright (C) 2008 Mike McCauley
// $Id: receiver.pde,v 1.3 2009/03/30 00:07:24 mikem Exp $

#include <VirtualWire.h>

const int led_pin = 7;

const int receive_pin = 8;

const boolean debug=false;
void setup()
{
    delay(1000);
    if (debug){
    Serial.begin(9600);	// Debugging only
    Serial.println("setup");
    }
    // Initialise the IO and ISR

    vw_set_rx_pin(receive_pin);

    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(1000);	 // Bits per sec

    vw_rx_start();       // Start the receiver PLL running

    pinMode(led_pin, OUTPUT);
        pinMode(13, OUTPUT);
}

void loop()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;

    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
	int i;
        digitalWrite(13, HIGH);
        digitalWrite(led_pin, HIGH); // Flash a light to show received good message
	// Message with a good checksum received, dump it.
if (debug)	{Serial.println("ping");}
	delay(1000);

        digitalWrite(led_pin, LOW);
        	if (debug) {Serial.print("off");}
    }
}
