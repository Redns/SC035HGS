#include "global.h"

/* DMA 相关全局变量 */
u32 RxBufferReceiveCount;
u32 RxBufferPtrReceiveIndex;
u32 RxBufferPtrTransmitIndex;
u32 RxBufferPtrLastReceiveIndex;
u32 RxBufferPtr[RX_BUFFER_NUMS];
u32 RxBufferFrameStartAddrPtr[RX_BUFFER_NUMS];
u32 EthTransmitCachePtr;
