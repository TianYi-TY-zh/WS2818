/**
 *******************************************************************************
 * @file      : ws2812.cpp
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
 /* Includes ------------------------------------------------------------------*/
#include "ws2812.h"
/* Private macro -------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void WS2812::Set_LEDColor(uint16_t LedId, RGBColor_TypeDef Color)
{
 if (LedId >= led_num_)
 {
  while (true);
 }
 RGB_Data[LedId].G = Color.G;
 RGB_Data[LedId].R = Color.R;
 RGB_Data[LedId].B = Color.B;
}

void WS2812::Init(SPI_HandleTypeDef* _hspi, uint32_t _led_num)
{
 spi_instance_ = _hspi;
 led_num_ = _led_num;
 RGB_Data = (RGBColor_TypeDef*)calloc(sizeof(RGBColor_TypeDef),led_num_);
}

/**
  * @brief			SPI发送控制ws2812
  */
void WS2812::Send(uint8_t *_rx_buffer)
{
 // 判断上次DMA有没有传输完成
 // while(HAL_DMA_GetState(dma_instance_) != HAL_DMA_STATE_READY);
 // 发送一个24bit的RGB数据
 HAL_SPI_Transmit(spi_instance_, _rx_buffer, 24,100);
}

/**
  * @brief			控制WS2812
  * @param[in]		待发送缓存
  */
void WS2812::RGB_Reflash(void)
{
 static uint8_t RGB_BUFFER[24]={0};
 uint8_t dat_b,dat_r,dat_g;
 // 将数组颜色转化为24个要发送的字节数据
 for (uint16_t i = 0; i < led_num_; i++) {
  dat_g = RGB_Data[i].G;
  dat_r = RGB_Data[i].R;
  dat_b = RGB_Data[i].B;
  for (uint16_t j = 0; j < 8; j++) {
   RGB_BUFFER[7-j] =code[dat_g & 0x01];
   RGB_BUFFER[15-j]=code[dat_r & 0x01];
   RGB_BUFFER[23-j]=code[dat_b & 0x01];
   dat_g >>=1;
   dat_r >>=1;
   dat_b >>=1;
  }
  WS2812::Send(RGB_BUFFER);
 }

}