/*
 * Copyright (C) 2016 - 2019 Xilinx, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 */

#include <stdio.h>
#include <string.h>

#include "lwip/sockets.h"
#include "netif/xadapter.h"
#include "lwipopts.h"
#include "xil_printf.h"
#include "FreeRTOS.h"
#include "task.h"
#include "dma_intr.h"
#include "open_image.h"
#include "vofa_plus.h"

#define THREAD_STACKSIZE 2048

extern u32 RxBufferPtrReceiveIndex;                                              // 接收缓存索引
extern u32 RxBufferPtrTransmitIndex;                                             // 发送缓存索引
extern u32 RxBufferPtrLastReceiveIndex;                                          // 上一个接收缓存索引
extern u32 RxBufferPtr[RX_BUFFER_NUMS];                                   		 // 帧缓冲区
extern u32 RxBufferFrameStartAddrPtr[RX_BUFFER_NUMS];
extern u32 EthTransmitCachePtr;

/*
 * Max number of telnet connections that this application can serve.
 * The existing implementation does not support closing of an existing telnet.
 * Once a telnet connection is made, it stays for ever.
 */
#define MAX_CONNECTIONS 8
int new_sd[MAX_CONNECTIONS];
int connection_index;

u16_t echo_port = 7;

void print_echo_app_header()
{
    xil_printf("%20s %6d %s\r\n", "echo server",
                        echo_port,
                        "$ telnet <board_ip> 7");

}

/* thread spawned for each connection */
void process_echo_request(void *p)
{
	int sd = *(int *)p;

	while(1)
	{
		if(RxBufferPtrTransmitIndex != RxBufferPtrLastReceiveIndex)
		{
			// 更新缓冲区相关索引
			RxBufferPtrTransmitIndex = RxBufferPtrLastReceiveIndex;
			if(RxBufferFrameStartAddrPtr[RxBufferPtrTransmitIndex] != RX_BUFFER_INVALID)
			{
				memcpy((u8*)EthTransmitCachePtr, "image:0,307200,640,480,24\n", 26);
				memcpy((u8*)(EthTransmitCachePtr + 26), (u8*)(RxBufferPtr[RxBufferPtrTransmitIndex] + RxBufferFrameStartAddrPtr[RxBufferPtrTransmitIndex]), FRAME_SIZE);
				memcpy((u8*)(EthTransmitCachePtr + 26 + FRAME_SIZE), (u8*)"\n", 1);
				write(sd, (u8*)EthTransmitCachePtr, 26 + FRAME_SIZE + 1);
			}
		}
	}

	close(sd);
	vTaskDelete(NULL);
}

void upper_transmit_thread()
{
	int sock;
	int size;

	struct sockaddr_in address, remote;

	memset(&address, 0, sizeof(address));

	if ((sock = lwip_socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return;

	address.sin_family = AF_INET;
	address.sin_port = htons(echo_port);
	address.sin_addr.s_addr = INADDR_ANY;

	if (lwip_bind(sock, (struct sockaddr *)&address, sizeof (address)) < 0)
		return;

	lwip_listen(sock, 0);

	size = sizeof(remote);

	while (1) {
		if ((new_sd[connection_index] = lwip_accept(sock, (struct sockaddr *)&remote, (socklen_t *)&size)) > 0) {
			sys_thread_new("echos", process_echo_request,
				(void*)&(new_sd[connection_index]),
				THREAD_STACKSIZE,
				DEFAULT_THREAD_PRIO);
			if (++connection_index>= MAX_CONNECTIONS) {
				break;
			}
		}
	}
	xil_printf("Maximum number of connections reached, No further connections will be accepted\r\n");
	vTaskSuspend(NULL);
}
