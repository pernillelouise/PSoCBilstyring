#ifndef slave_H

#include "Project.h"    

#define slave_H
#define I2Cadress // mangler adr
#define maxSize 4

// Initialize initReceiveData to slaveWriteBuffer with a size of MaxSize (4)
void initReceiveData();
void receiveData(uint8* buffer);

// Receive data will make the device listen to the I2C network
// If a match occurs it will compare the commandtype with known values,
// and process the data accordingly.
// The received data will be saved into the buffer.
void receiveData(uint8* buffer);
  //int  bytecnt=0;  
uint8 wrbuf[maxSize];
//uint8 userarray[bytecnt];
#endif


    
    
    
    