/**
 *******************************************************************************
 * @file      : ws2812.h
 * @brief     :
 * @history   :
 *  Version     Date               Author             Note
 *  V0.9.0      24-4-9         Huang Huichuan     1. <note>
 *******************************************************************************
 * @attention :
 *******************************************************************************
 *  Copyright (c) 2024 Reborn Team, University of Science and Technology Beijing.
 *  All Rights Reserved.
 *******************************************************************************
 */
 /* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ws2812_H_
#define __ws2812_H_

#ifdef __cplusplus

/* Includes ------------------------------------------------------------------*/
#include "spi.h"
/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef struct {
 uint8_t R;
 uint8_t G;
 uint8_t B;
}RGBColor_TypeDef;	//颜色结构体

class WS2812
{
 private:
 uint16_t led_num_;
 SPI_HandleTypeDef *spi_instance_;
 //颜色缓存
 RGBColor_TypeDef *RGB_Data;
 void Send(uint8_t *_rx_buffer);
public:
 void Init(SPI_HandleTypeDef *_hspi,uint32_t _led_num);
 void Set_LEDColor(uint16_t LedId, RGBColor_TypeDef Color);
 void RGB_Reflash(void);
};
/* Exported constants --------------------------------------------------------*/
// 模拟bit码: 0b1100000逻辑0, 0b11111000为逻辑1
//WS2812工作在800khz 需要自己对逻辑
//这个模拟Bit的SPI主频在8Mhz
const uint8_t code[]={0b1100000,0b11111000};
// 常见颜色定义
const RGBColor_TypeDef RED = {255, 0, 0};
const RGBColor_TypeDef BLUE = {0, 0, 255};
/* Exported variables --------------------------------------------------------*/
/* Exported function prototypes ----------------------------------------------*/

#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported function prototypes ----------------------------------------------*/

#ifdef  __cplusplus
}
#endif

#endif /* __ws2812_H_ */