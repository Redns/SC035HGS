# 0 设计目标

使用 FPGA 驱动 `SC035HGS`、`SC031HGS` 图像传感器，要求如下

- 支持 `DVP`、`LVDS` 接口输出
- 输出 `640×480@(15-60)fps`、`800×600@(15-60)fps`，至少支持 `640×480@(15-30)fps`、`800×600@(15-30)fps`
- 支持 `RGB565` 和 `灰度图像` 输出
- 接口（DVP、LVDS）、帧数据（640×480、800×600）、输出格式（RGB565、灰度）均需要支持一键切换
- 图像输出缓冲区使能可控

# 1 SC035HGS

## 1.1 概述

- 有效像素阵列：640H×480V

- 最大图像传输速率

  - Linear

    640×480@10bit 180fps

  - HDR

    640×480@10bit 90fps (KPC on)

    640×480@10bit 180fps (KPC off)

- 输出接口

  - 12/10/8-bit DVP
  - 12/10/8-bit lane MIPI
  - 12/10/8-bit lane LVDS

- 输出格式

  - RAW MONO
  - RAW RGB

- 支持高动态模式（HDR）

- 支持自动曝光/外部控制曝光（多 sensor 同步）

- 15.5x 模拟增益，8x 数字增益

## 1.2 引脚定义

![image-20231019094419219](https://image.krins.cloud/202310190944360.png)

上图插排俯视图引脚定义如下

|      左       |      右      |
| :-----------: | :----------: |
|      3V3      |     GND      |
|   Y4（V18）   |  Y3（W18）   |
|   Y5（U17）   |  Y2（U19）   |
|   Y6（W15）   | PCLK（U14）  |
|   Y7（U15）   |     DGND     |
|   Y8（P20）   | MCLK（Y14）  |
|   Y9（T20）   |  DOVDD 1.8V  |
| DVDD 1.5V（） | HREF（N18）  |
|  PWDN（U20）  | VSYNC（N20） |
|   RESET（）   | SIO_C（R17） |
| AVDD 2.8V（） | SIO_D（W20） |
|    GND（）    |      NC      |

# 2 驱动设计

## 2.1 基本框架

## 2.2 XSCT 串口打印

打开 `BSP` 设置，点击右侧 **Modify BSP Settings** 修改设置

![image-20231103095703689](https://image.krins.cloud/202311030957851.png)

修改 stdin/stdout 为 **ps7_coresight_comp_0**，点击 OK 重新编译 platform project 即可

> ZYNQ 不同系列选项可能不同，选择带有 coresight 的选项即可

![image-20231103095853377](https://image.krins.cloud/202311030958464.png)

然后使用调试器连接主机和 `ZYNQ` 板卡，在开始页面的 **Xilinx Design Tools** 应用组件中找到并打开 **Xilinx Software Command Line Tool**

![image-20231103094052900](https://image.krins.cloud/202311030940054.png)

使用 **connect** 命令连接板卡

![image-20231103094238469](https://image.krins.cloud/202311030942519.png)

使用 **targets** 命令查看板卡可调试的所有目标，下图示例中 **APU** 位于 `PS` 部分，**xc7z100** 位于 `PL` 部分

> 有关 PS、PL、ARM、APU 等概念的解析[参见](https://blog.csdn.net/the_time_runner/article/details/103153261)

![image-20231103094354078](https://image.krins.cloud/202311030943120.png)

使用 **target** 命令选择要连接的目标，这里选择 **ARM Cortex-A9 MPCore #0**

![image-20231103095013727](https://image.krins.cloud/202311030950779.png)

使用 **jtagterminal** 命令打开终端

![image-20231103095119051](https://image.krins.cloud/202311030951087.png)

此后所有打印信息都会在终端中显示

```c
xil_printf("[INFO] Init camera sc035hgs...\n");
```

![image-20231103100404305](https://image.krins.cloud/202311031004369.png)

