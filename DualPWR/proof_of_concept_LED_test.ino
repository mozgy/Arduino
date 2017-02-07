/*
 *   DualPWR - PoC with LED for RC
 *     
 *   This code is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU Lesser General Public
 *   License as published by the Free Software Foundation; either
 *   version 2.1 of the License, or (at your option) any later version.
 *
 *   This code is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *   Lesser General Public License for more details.
 *
 *   Copyright (c) 2017. Mario Mikočević <mozgy>
 *
 */

#define LEDpin 4

#define inputPin_INT 3
#define outputPin_INT 4

unsigned long previousMillis_INT = 0;
const long interval_INT = 1500;
byte inputPreviousState_INT = HIGH;

unsigned long deBouncePeriod = 0;
const long deBounceCLK = 60;
byte deBounceState = HIGH;
boolean deBouncing = false;

void setup() {

  pinMode( inputPin_INT, INPUT );
  pinMode( outputPin_INT, OUTPUT );
  inputPreviousState_INT = digitalRead( inputPin_INT );

//  pinMode( LEDpin, OUTPUT );

}

void loop() {

  unsigned long currentMillis_INT = millis();
  byte inputState_INT = digitalRead( inputPin_INT );
  
  if ( inputState_INT != inputPreviousState_INT ) {
    if ( !deBouncing ) {
      deBouncing = true;
      deBounceState = HIGH;
      deBouncePeriod = 0;
      digitalWrite( outputPin_INT, HIGH );
      previousMillis_INT = currentMillis_INT;
    } else {
      previousMillis_INT = previousMillis_INT + deBouncePeriod;
      deBouncePeriod = 0;
    }
  }

  if ( currentMillis_INT - previousMillis_INT >= interval_INT ) {
    if ( inputState_INT == inputPreviousState_INT ) {
      deBouncing = false;
      deBouncePeriod = 0;
      digitalWrite( outputPin_INT, LOW );
    }
  }

  if ( deBouncing && ( currentMillis_INT - previousMillis_INT >= deBouncePeriod + deBounceCLK ) ) {
    deBounceState = !deBounceState;
    digitalWrite( outputPin_INT, deBounceState );
    deBouncePeriod = deBouncePeriod + deBounceCLK;
  }

  inputPreviousState_INT = inputState_INT;

//  digitalWrite( LEDpin, HIGH );
//  delay( 1000 );
//  digitalWrite( LEDpin, LOW );
//  delay( 1000 );
}
