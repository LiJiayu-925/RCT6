# STM32F103RCT6 最小系统板示例工程

基于 STM32F103RCT6 最小系统板的 Keil MDK 工程，演示基本的片上外设使用方法。

## 硬件平台

| 参数 | 值 |
|------|-----|
| 芯片 | STM32F103RCT6 |
| 内核 | ARM Cortex-M3 |
| 主频 | 72 MHz（HSE 8 MHz × PLL ×9） |
| Flash | 256 KB |
| SRAM | 48 KB |
| 封装 | LQFP-64 |

## 工程结构

```
RCT6/
├── CORE/                          # CMSIS 内核文件
│   ├── core_cm3.h                 # Cortex-M3 内核访问层头文件
│   └── startup_stm32f10x_hd.s    # 启动文件（高密度型）
├── USER/                          # 用户应用文件
│   ├── main.c                     # 主程序
│   ├── stm32f10x.h                # STM32F10x 外设寄存器定义
│   ├── stm32f10x_it.c/h           # 中断服务函数
│   ├── system_stm32f10x.c/h       # 系统时钟初始化（72 MHz）
├── SYSTEM/                        # 系统支持库
│   ├── delay/delay.c/h            # SysTick 延时函数
│   ├── sys/sys.c/h                # NVIC 配置
│   └── usart/usart.c/h            # USART1 串口驱动（printf 重定向）
├── HARDWARE/
│   └── LED/led.c/h                # LED 驱动（PA8、PD2）
├── OBJ/                           # 编译输出目录（自动生成，不入库）
└── RCT6.uvprojx                   # Keil MDK 工程文件
```

## 功能说明

| 功能 | 引脚 | 说明 |
|------|------|------|
| LED0 | PA8 | 低电平点亮，与 LED1 交替闪烁（500 ms） |
| LED1 | PD2 | 低电平点亮，与 LED0 交替闪烁（500 ms） |
| USART1 TX | PA9 | 115200 8N1，每次翻转后打印闪烁计数 |
| USART1 RX | PA10 | 预留接收 |

## 时钟配置

```
HSE（8 MHz 晶振）→ PLL ×9 → SYSCLK = 72 MHz
                                ├── AHB  (HCLK)  = 72 MHz
                                ├── APB2 (PCLK2) = 72 MHz
                                └── APB1 (PCLK1) = 36 MHz（÷2）
```

## 如何编译与下载

1. 安装 **Keil MDK-ARM**（建议 V5.30+）及 **STM32F1xx 器件支持包**（Keil.STM32F1xx_DFP）。
2. 双击打开 `RCT6.uvprojx`。
3. 点击 **Build (F7)** 编译工程，输出文件位于 `OBJ/` 目录。
4. 通过 ST-Link / J-Link 连接目标板，点击 **Download (F8)** 烧写固件。
5. 可选：使用 USB-UART 适配器连接 PA9（TX），打开串口助手（115200 baud），查看运行日志。

## 注意事项

- 工程已启用 **MicroLIB**（`useUlib=1`），`printf` 通过 `fputc` 重定向至 USART1。
- 如使用内部 RC 振荡器（无外部晶振），需修改 `system_stm32f10x.c` 中的时钟配置，改用 HSI。
- LED 为**低电平有效**，根据实际电路修改 `led.h` 中的宏定义。
