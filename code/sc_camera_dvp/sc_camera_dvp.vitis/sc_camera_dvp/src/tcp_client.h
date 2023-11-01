#ifndef __TCP_CLIENT_H_
#define __TCP_CLIENT_H_

#include "lwipopts.h"
#include "lwip/ip_addr.h"
#include "lwip/err.h"
#include "lwip/tcp.h"
#include "lwip/inet.h"
#include "xil_printf.h"
#include "platform.h"

#define TCP_SERVER_IP_ADDRESS   "192.168.1.100"         // 服务器 IP 地址
#define TCP_CONN_PORT           5001                    // 服务器端口号
#define TCP_SEND_BUFSIZE        5 * TCP_MSS             // 发送缓冲区大小（字节）

typedef struct tcp_pcb tcp_pcb;

void tcp_client_init();
uint32_t tcp_client_send(uint8_t* data, uint32_t size);
void tcp_client_close();

#endif
