#include "global.h"


/************************************** DMA ´«Êä»º³åÇø **************************************/
// TODO https://image.krins.cloud/202312202000235.jpg
volatile u32 RxCount;
volatile u32 RxIndex;
volatile u32 TxIndex;
volatile u32 RxLastIndex;
volatile u32 RxBuffer[RX_BUFFER_NUMS][RX_BUFFER_SIZE];
volatile u32 RxBufferFrameStart[RX_BUFFER_NUMS];
volatile u32 EthBuffer[RX_BUFFER_SIZE];
/******************************************************************************************/