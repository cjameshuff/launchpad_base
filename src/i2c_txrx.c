

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_i2c.h"

#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/i2c.h"

#include "i2c_txrx.h"

// *****************************************************************************

static void I2C_Wait(uint32_t i2cBase) {
    while(MAP_I2CMasterBusy(i2cBase))
        {;}
}

// Some examples used code similar to the following for no apparent reason
/*static void I2C_Wait(uint32_t i2cBase) {
    while(MAP_I2CMasterIntStatus(i2cBase, false) == 0)
        {;}
    
    if(MAP_I2CMasterErr(i2cBase) != I2C_MASTER_ERR_NONE) {
        MAP_I2CMasterIntClear(i2cBase);
        return;
    }
    
    while(MAP_I2CMasterIntStatus(i2cBase, false))
        MAP_I2CMasterIntClear(i2cBase);
}*/

// *****************************************************************************

int I2C_Tx(uint32_t i2cBase, const uint8_t * txData, size_t txSize, bool start, bool stop)
{
    // Clear read bit in slave address
    HWREG(i2cBase + I2C_O_MSA) &= ~0x01;
    if(txSize == 1 && start && stop)
    {
        // Start and stop on single byte transaction
        MAP_I2CMasterDataPut(i2cBase, *txData++);
        MAP_I2CMasterControl(i2cBase, I2C_MASTER_CMD_SINGLE_SEND);
        I2C_Wait(i2cBase);
        if(MAP_I2CMasterErr(i2cBase) != I2C_MASTER_ERR_NONE)
            goto tx_error;
    }
    else
    {
        // Multiple bytes to transmit, or transaction continues from previous and/or into subsequent one.
        // Reserve last byte if stopping
        const uint8_t * txBodyEnd = (stop)? (txData + txSize - 1) : (txData + txSize);
        if(start)
        {
            MAP_I2CMasterDataPut(i2cBase, *txData++);
            MAP_I2CMasterControl(i2cBase, I2C_MASTER_CMD_BURST_SEND_START);
            I2C_Wait(i2cBase);
            if(MAP_I2CMasterErr(i2cBase) != I2C_MASTER_ERR_NONE)
                goto tx_error;
        }
        
        // Send body (do nothing if single byte and stopping)
        while(txData != txBodyEnd)
        {
            MAP_I2CMasterDataPut(i2cBase, *txData++);
            MAP_I2CMasterControl(i2cBase, I2C_MASTER_CMD_BURST_SEND_CONT);
            I2C_Wait(i2cBase);
            if(MAP_I2CMasterErr(i2cBase) != I2C_MASTER_ERR_NONE)
                goto tx_error;
        }
        
        if(stop)
        {
            MAP_I2CMasterDataPut(i2cBase, *txData++);
            MAP_I2CMasterControl(i2cBase, I2C_MASTER_CMD_BURST_SEND_FINISH);
            I2C_Wait(i2cBase);
            if(MAP_I2CMasterErr(i2cBase) != I2C_MASTER_ERR_NONE)
                goto tx_error;
        }
    }
    
    return 0;
tx_error:
    MAP_I2CMasterControl(i2cBase, I2C_MASTER_CMD_BURST_SEND_ERROR_STOP);
    I2C_Wait(i2cBase);
    return -1;
}

// *****************************************************************************
int I2C_Rx(uint32_t i2cBase, uint8_t * rxData, size_t rxSize, bool start, bool stop)
{
    // Set read bit in slave address
    HWREG(i2cBase + I2C_O_MSA) |= 0x01;
    if(rxSize == 1 && start && stop)
    {
        // Start and stop on single byte transaction
        MAP_I2CMasterControl(i2cBase, I2C_MASTER_CMD_SINGLE_RECEIVE);
        I2C_Wait(i2cBase);
        if(MAP_I2CMasterErr(i2cBase) != I2C_MASTER_ERR_NONE)
            goto rx_error;
        *rxData++ = MAP_I2CMasterDataGet(i2cBase);
    }
    else
    {
        // Multiple bytes to receive, or transaction continues from previous and/or into subsequent one.
        // Reserve last byte if stopping
        const uint8_t * rxBodyEnd = (stop)? (rxData + rxSize - 1) : (rxData + rxSize);
        if(start)
        {
            MAP_I2CMasterControl(i2cBase, I2C_MASTER_CMD_BURST_RECEIVE_START);
            I2C_Wait(i2cBase);
            if(MAP_I2CMasterErr(i2cBase) != I2C_MASTER_ERR_NONE)
                goto rx_error;
            *rxData++ = MAP_I2CMasterDataGet(i2cBase);
        }
        
        // Send body (do nothing if single byte and stopping)
        while(rxData != rxBodyEnd)
        {
            MAP_I2CMasterControl(i2cBase, I2C_MASTER_CMD_BURST_RECEIVE_CONT);
            I2C_Wait(i2cBase);
            if(MAP_I2CMasterErr(i2cBase) != I2C_MASTER_ERR_NONE)
                goto rx_error;
            *rxData++ = MAP_I2CMasterDataGet(i2cBase);
        }
        
        if(stop)
        {
            MAP_I2CMasterControl(i2cBase, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
            I2C_Wait(i2cBase);
            if(MAP_I2CMasterErr(i2cBase) != I2C_MASTER_ERR_NONE)
                goto rx_error;
            *rxData++ = MAP_I2CMasterDataGet(i2cBase);
        }
    }
    
    return 0;
    
rx_error:
    MAP_I2CMasterControl(i2cBase, I2C_MASTER_CMD_BURST_RECEIVE_ERROR_STOP);
    I2C_Wait(i2cBase);
    return -1;
}

// *****************************************************************************

int I2C_TxRx(uint32_t i2cBase, uint8_t addr, const uint8_t * txData, size_t txSize, uint8_t * rxData, size_t rxSize)
{
    if(txSize != 0)
    {
        // Start transaction, end if no data to receive
        MAP_I2CMasterSlaveAddrSet(i2cBase, addr, false);
        if(I2C_Tx(i2cBase, txData, txSize, true, rxData == 0))
            return -1;
    } // if(txData)
    
    if(rxSize != 0)
    {
        // Send start (repeated start if data was transmitted), end after reception
        MAP_I2CMasterSlaveAddrSet(i2cBase, addr, true);
        if(I2C_Rx(i2cBase, rxData, rxSize, true, true))
            return -1;
    } // if(rxData)
    
    return 0;
}

// *****************************************************************************

