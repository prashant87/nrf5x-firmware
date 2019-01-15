/* 
 * File:   sensebe_rx_detect.h
 * Copyright (c) 2018 Appiko
 * Created on 29 October, 2018, 12:23 PM
 * Author:  Tejas Vasekar (https://github.com/tejas-tj)
 * All rights reserved.
 * 
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


#ifndef SENSEBE_RX_DETECT_H
#define SENSEBE_RX_DETECT_H

#include "ms_timer.h"
#include "sensebe_ble.h"

#ifdef __cplusplus
extern "C" {
#endif
    
#define SENSEBE_TIMER_MODE_MS_TIMER MS_TIMER3
    
#define SENSEBE_OPERATION_MS_TIMER MS_TIMER2

/** Structure containing all the values required for sensebe_rx_detect module */
typedef struct 
{
    /** Pin number for Enable pin on TSSP module */
    uint32_t rx_en_pin;
    /** Pin number for Out pin on TSSP module */
    uint32_t rx_out_pin;
    /** Pin number for Focus pin */
    uint32_t focus_pin_no;
    /** Pin number for Trigger pin */
    uint32_t trigger_pin_no;
    /** Pin number for Photodiode */
    uint32_t photodiode_pin;
    /** sensebe_config_t pointer which points to default configuration */
    sensebe_config_t * init_sensebe_config;
}sensebe_rx_detect_config_t;

/**
 * @brief Function to initialize the Rx detect module
 * @param sensebe_rx_detect_config COnfiguration required for sensbe_rx_detect module
 * @ref sensebe_rx_detect_config_t
 */    
void sensebe_rx_detect_init (sensebe_rx_detect_config_t * sensebe_rx_detect_config);

/**
 * @brief Function to enable detection for SenseBe Rx
 */
void sensebe_rx_detect_start (void);

/**
 * @brief Function to disable detection for SenseBe Rx
 */
void sensebe_rx_detect_stop (void);

/**
 * @brief Function to handle add tick event.
 * 
 * @param interval Ticks since the last occurance of add tick event.
 */
void sensebe_rx_detect_add_ticks (uint32_t interval);

/**
 * @brief Function to update SenseBe Rx configuration to config received over BLE
 * 
 * @param sensebe_config Pointer to the Configuration received over BLE
 */
void sensebe_rx_detect_update_config (sensebe_config_t * update_sensebe_config);

/**
 * @brief Function to get last config which is being used.
 * @return Configuration pointer to the configuration which is being used.
 */
sensebe_config_t * sensebe_rx_detect_last_config ();
#ifdef __cplusplus
}
#endif

#endif /* SENSEBE_RX_DETECT_H */

