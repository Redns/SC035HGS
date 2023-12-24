#include "global.h"


/* DMA */
// TODO https://image.krins.cloud/202312202000235.jpg
volatile s32 RxCount;
volatile s32 RxIndex;
volatile s32 TxIndex;
volatile s32 RxLastIndex;

volatile u32 RxBufferPtr[RX_BUFFER_NUMS];
volatile u32 RxBufferFrameAddr[RX_BUFFER_NUMS];

volatile u32 EthTxBufferPtr;