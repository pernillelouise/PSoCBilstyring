#include "I2Cslave.h"
#include "Project.h"


    
void initReceiveData()
{
    //Set slave write buffer
    I2C_1_I2CSlaveInitWriteBuf(wrbuf,maxSize);
}

void receiveData(uint8* userarray)
{ 
    if (I2C_1_I2CSlaveStatus() == I2C_1_I2C_SSTAT_WR_CMPLT)
    {
        int i; 
        int  bytecnt=I2C_1_I2CSlaveGetWriteBufSize();
        for(i = 0; i<bytecnt; i++)
        {
            //Saves data from the I2C slave buffer into the userarray
            userarray[i] = (int)wrbuf[i];
        }
        
        I2C_1_I2CSlaveClearReadBuf();
        I2C_1_I2CSlaveClearWriteBuf();
    }
    I2C_1_I2CSlaveClearReadStatus();
}



