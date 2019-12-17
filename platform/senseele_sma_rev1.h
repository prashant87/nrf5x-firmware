/**
 *  senseele_sma_rev1.h : SenseEle SMA Rev1 board definitions
 *  Copyright (C) 2019  Appiko
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

/**
 * @addtogroup group_platform
 * @{
 *
 * @defgroup board_senseele_sma_rev1 Appiko SenseEle SMA unit revision 1
 * @brief Board definitions for the 1st revision of the SenseEle 
 * @{
 */


#ifndef PLATFORM_SENSEELE_SMA_REV1_H_
#define PLATFORM_SENSEELE_SMA_REV1_H_

/** @anchor senseele_sma_rev1_serial
 * @name Serial port definitions for SenseEle SMA Rev1
 * @{*/
#define TEST_LED       22 //original RX
#define RX_PIN_NUMBER       19
#define TX_PIN_NUMBER       20
//#define TX_PIN_NUMBER       06 //bluey
//#define TX_PIN_NUMBER       02 //bluey_rx
#define HWFC                false
#define RTS_PIN_NUMBER      23
#define CTS_PIN_NUMBER      24
/** @} */

/** @anchor senseele_sma_rev1_spi
 * @name SPI definitions for SenseEle SMA Rev1
 * @{
 */
#define MISO_PIN            04
#define MOSI_PIN            06
#define SCLK_PIN            05
#define CSN_PIN             02
/** @} */

/** @anchor senseele_sma_rev1_ccgpio
 * @name GPIO definitions connected to CC112x's GPIOs
 * @{
 */
//#define CC_GPIO2            26    //bluey  
#define CC_GPIO2            07       
#define CC_GPIO0            03      
#define CC_GPIO3            08       
/** @} */

/** @anchor senseele_sma_rev1_i2c
 * @name I2C definitions for SenseEle SMA Rev1
 * @{
 */
#define SDA_PIN             12
#define SCK_PIN             13
/** @} */

/** @anchor senseele_sma_rev1_halleffect
 * @name Hall effect sensor definition for SenseEle SMA Rev1
 * @{
 */
//#define HALL_EFFECT_PIN     27 //Bluey
#define HALL_EFFECT_PIN     11
/** @} */

/** @anchor senseele_sma_rev1_tcxo_en
 * @name Temp Compensated XOSC definitions for SenseEle SMA Rev1
 * @{
 */
#define TCXO_EN_PIN         16
/** @} */

/** @anchor senseele_sma_rev1_int
 * @name Interrupt pin for Accelerometer
 * @{
 */
#define ACCE_INT_PIN        14
/** @} */

/** @anchor senseele_sma_rev1_cc_reset
 * @name Reset Pin fpr CC112x for SenseEle Rev1
 * @{
 */
#define CC_RESET_PIN        09
/** @} */

///Bool define if the circuitry is present for the internal DC-DC of nRF52
#define DC_DC_CIRCUITRY     false

///Bool define if a NFC Antenna circuitry is present
#define NFC_CIRCUITRY       false

///Bool define if the 32 kHz crystal is present for the LFCLK
#define LFCLK_XTAL_PRESENT  true

///Bool define if a crystal is present for the HFCLK
#define HFCLK_XTAL_PRESENT  true

/** Low frequency clock source used when initializing the SoftDevice */
#define BOARD_LFCLKSRC_STRUCT  {.source        = NRF_CLOCK_LF_SRC_XTAL,            \
                                    .rc_ctiv       = 0,                                \
                                    .rc_temp_ctiv  = 0,                                \
                                    .accuracy = NRF_CLOCK_LF_ACCURACY_20_PPM}

#define BOARD_LFCLKSRC         NRF_CLOCK_LFCLK_Xtal

#endif /* PLATFORM_SENSEBE_RX_REV3_H_ */
/**
 * @}
 * @}
 */
