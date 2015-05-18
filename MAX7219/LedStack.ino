#include "LedControl.h"

/*
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 
 maximum of 8 MAX72XX
 */
LedControl lc=LedControl(12,11,10,6);

unsigned long delaytime=2;
int devices=lc.getDeviceCount();

int address;
int row;
int col;
boolean light;

void setup() {
    //we have to init all devices in a loop
  for(int address=0;address<devices;address++) {
    /*The MAX72XX is in power-saving mode on startup*/
    lc.shutdown(address,false);
    /* Set the brightness to a medium values */
    lc.setIntensity(address,8);
    /* and clear the display */
    lc.clearDisplay(address);
  }
}

/* 
 This function will light up every Led on the matrix.
 The led will blink along with the row-number.
 row number 4 (index==3) will blink 4 times etc.
 */
void single() {
  for(int address=0;address<devices;address++) {
    for(int row=0;row<8;row++) {
      for(int col=0;col<8;col++) {
        delay(delaytime);
        lc.setLed(address,row,col,true);
        delay(delaytime);
        for(int i=0;i<col;i++) {
          lc.setLed(address,row,col,false);
          delay(delaytime);
          lc.setLed(address,row,col,true);
          delay(delaytime);
        }
      }
    }
  }
}

void loopONEa() {
  for(int row=0;row<8;row++) {
    for(int col=0;col<8;col++) {
      for(int address=0;address<devices;address++) {
//        delay(delaytime);
        lc.setLed(address,row,col,true);
        delay(delaytime);
        lc.setLed(address,row,col,false);
//        delay(delaytime);
      }
    }
  }
}

void loopONEb() {
  for(int row=0;row<8;row++) {
    for(int address=0;address<devices;address++) {
      for(int col=0;col<8;col++) {
        delay(delaytime);
        lc.setLed(address,row,col,true);
        delay(2*delaytime);
        lc.setLed(address,row,col,false);
//        delay(delaytime);
      }
    }
  }
}

void noise() {
  for(int i=0;i<4000;i++) {
    address=random(devices);
    row=random(8);
    col=random(8);
    if( random(4) < 3 ) {
      light=false;
    } else {
      light=true;
    }
    lc.setLed(address,row,col,light);
    delay(delaytime);
  }
}

void go(int x, int y) {
  switch(x) {
    case -1:
      row++;
      if( row > 7 ) { row=7; }
    break;
    case 1:
      row--;
      if( row < 0 ) { row=0; }
    break;
  }
  switch(y) {
    case -1:
      col++;
      if( col > 7 ) {
        address++;
        col=0;
        if( address >= devices ) {
          address=devices-1;
          col=7;
        }
      }
    break;
    case 1:
      col--;
      if( col < 0 ) {
        address--;
        col=7;
        if( address < 0 ) {
          address=0;
          col=0;
        }
      }
    break;
  }
}

void dir_go(int dir) {
  switch( dir ) {
    case 0:
      go(1, 0);
    break;
    case 1:
      go(1, 1);
    break;
    case 2:
      go(0, 1);
    break;
    case 3:
      go(-1, 1);
    break;
    case 4:
      go(-1, 0);
    break;
    case 5:
      go(-1, -1);
    break;
    case 6:
      go(0, -1);
    break;
    case 7:
      go(1, -1);
    break;
    default:
    break;
  }
}

void snake() {
  int dir;

  address=random(devices);
  row=4;
  col=4;
  light=true;
  
  for(int i=0;i<500;i++) {
    lc.setLed(address,row,col,light);
    delay(6*delaytime);
    dir=random(8);
    dir_go( dir );
  }
}

void snake2() {
  int dir=4;

  address=random(devices);
  row=random(8);
  col=random(8);
  light=true;
  
  for(int i=0;i<800;i++) {
    lc.setLed(address,row,col,light);
    delay(6*delaytime);
    switch( random(3) ) {
      case 0:
        dir--;
        if( dir < 0 ) { dir=7; }
      break;
      case 1:
      break;
      case 2:
        dir++;
        if( dir > 7 ) { dir=0; }
      break;
      default:
      break;
    }
    dir_go( dir );
  }
}

void loop() {
//  single();
//  loopONEa();
  loopONEb();
  snake();
  noise();
  loopONEb();
  snake2();
  noise();
}
