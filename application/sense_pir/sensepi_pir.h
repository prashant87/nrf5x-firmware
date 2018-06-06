/* 
 * File:   sensepi_pir.h
 * Copyright (c) 2018 Appiko
 * Created on 1 June, 2018, 3:32 PM
 * Author: Tejas Vasekar (https://github.com/tejas-tj)
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE
 */
#ifndef SENSEPI_PIR_H
#define SENSEPI_PIR_H

#include "sensepi_ble.h"
#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

/**Strcture to configure SensePi_PIR module*/
typedef struct{
    sensepi_config * config_sensepi; ///Configuration received from mobile app
    uint32_t pir_sense_signal_input; ///Pin number for PIR signal output
    uint32_t pir_sense_offset_input; ///Pin number for PIR offset output
    uint32_t led_sense_out_pin;      ///Pin number for LED driving pin.
    uint32_t led_sense_analog_in_pin;///Pin number for light sensing.
    uint32_t led_sense_off_val;      ///Value at which LED is off.

}sensepi_pir_config_t;

/**Enum with all the substate for SENSING state*/
typedef enum
{
    PIR_DETECTING,
    PIR_ENABLED,
    PIR_DISABLED,
    PIR_WAIT_LED,
}sensepi_pir_substate;

/**
 * @brief Function to initiate SensePi_PIR module
 * @param config strcture pointer of configuration for which we need to
 * configure the SensePi_PIR module
 */
void sensepi_pir_init(sensepi_pir_config_t * config_sensepi_pir);

/**
 * @brief Function to start PIR sensing
 */
void sensepi_pir_start();

/**
 * @brief Function to stop PIR sensing
 */
void sensepi_pir_stop();

/**
 * @brief Function to update the configuration at every instance when it is
 * changed in the program. 
 * @param update_config configuration to which module needs to be updated.
 */
void sensepi_pir_update(sensepi_config * update_config);

/**
 * @brief Function to enable LED sensing with proper parameters.
 * @param led_conf
 */
void sensepi_pir_led_sense_conf(sensepi_pir_config_t * led_conf);

void sensepi_pir_add_tick(uint32_t intervel);

#ifdef __cplusplus
}
#endif

#endif /* SENSEPI_PIR_H */

