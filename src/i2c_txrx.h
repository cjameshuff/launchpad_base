
#ifndef I2C_TXRX_H
#define I2C_TXRX_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

// Perform partial transactions
// if start == true, send a start for the first byte.
// if stop == true, send a stop for the last byte.
// MAP_I2CMasterSlaveAddrSet() must be called at some point before these functions
int I2C_Tx(uint32_t i2cBase, const uint8_t * txData, size_t txSize, bool start, bool stop);
int I2C_Rx(uint32_t i2cBase, uint8_t * rxData, size_t rxSize, bool start, bool stop);

// Write txSize bytes from txData and read rxSize bytes into rxData.
// If txSize = 0 and rxSize > 0, a simple read-only transaction is done.
// If txSize > 0 and rxSize = 0, a simple write-only transaction is done.
// If txSize > 0 and rxSize > 0, the read is done following the write with a repeated start,
// without stopping the transaction.
// rxData or txData may be NULL if not used.
// rxData or txData may reference the same memory, in which case the received data
// will overwrite the transmitted data.
int I2C_TxRx(uint32_t i2cBase, uint8_t addr, const uint8_t * txData, size_t txSize, uint8_t * rxData, size_t rxSize);

#ifdef __cplusplus
}
#endif

#endif // I2C_TXRX_H
