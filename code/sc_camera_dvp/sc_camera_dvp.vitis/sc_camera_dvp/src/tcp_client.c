#include "tcp_client.h"

static tcp_pcb *c_pcb;
static uint8_t send_buf[TCP_SEND_BUFSIZE];


/**
 * @brief 初始化 TCP 客户端
 * @return *
*/
void tcp_client_init()
{
	err_t err;
	struct tcp_pcb* pcb;
	ip_addr_t remote_addr;
    // 为服务器绑定 IP
    err = inet_aton(TCP_SERVER_IP_ADDRESS, &remote_addr);
	if(!err) 
    {
		xil_printf("[ERROR] Invalid Server IP address: %d\r\n", err); return;
	}
	// 创建客户端句柄
	pcb = tcp_new_ip_type(IPADDR_TYPE_ANY);
	if(!pcb) 
    {
		xil_printf("[ERROR] Error in PCB creation. out of memory\r\n"); return;
	}
    // 连接服务器
	err = tcp_connect(pcb, &remote_addr, TCP_CONN_PORT, NULL);
	if(err) 
    {
		xil_printf("[ERROR] Error on tcp_connect: %d\r\n", err);
		tcp_client_close(pcb);
		return;
	}
    // 初始化发送缓冲区
    memset(send_buf, 0, TCP_SEND_BUFSIZE);
	return;
}


/**
 * @brief TCP 发送数据
 * @param data  待发送的数据
 * @param size  待发送的长度（字节）
 * @return 实际发送的字节数
*/
uint32_t tcp_client_send(uint8_t* data, uint32_t size)
{
	if((c_pcb == NULL) || (size == 0)) 
    {
		return -1;
	}

    uint32_t totalSendBytes = 0;
    uint32_t singleSendBytes = 0;
    while(totalSendBytes < size)
    {
        singleSendBytes = (size - totalSendBytes > TCP_SEND_BUFSIZE) ? TCP_SEND_BUFSIZE : (size - totalSendBytes);
        memcpy(send_buf, data, singleSendBytes);
        if((tcp_write(c_pcb, send_buf, singleSendBytes, TCP_WRITE_FLAG_COPY | TCP_WRITE_FLAG_MORE) != ERR_OK) || (tcp_output(c_pcb) != ERR_OK))
        {
            return totalSendBytes;
        }
        totalSendBytes += singleSendBytes;
    }
	return totalSendBytes;
}


/**
 * @brief 关闭 TCP 连接
 * @return *
*/
void tcp_client_close()
{
	if (c_pcb != NULL) 
    {
		tcp_sent(c_pcb, NULL);
		tcp_err(c_pcb, NULL);
		if (tcp_close(c_pcb) != ERR_OK) 
        {
			tcp_abort(c_pcb);
		}
	}
}
