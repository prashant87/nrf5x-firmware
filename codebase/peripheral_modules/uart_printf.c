/**
 *  uart_printf.c : UART Driver for sending printf messages
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

#include "nrf.h"
#include "uart_printf.h"
#include "hal_gpio.h"
#include "boards.h"
#include "nrf_util.h"
#include "tinyprintf.h"
#include <stdbool.h>

#if ISR_MANAGER == 1
#include "isr_manager.h"
#endif

#define UARTE_ID CONCAT_2(NRF_UARTE,UARTE_USED_UART_PRINTF)

/** Size of the PING & PONG buffer each to hold the data to be sent*/
#define BUFFER_SIZE     128

typedef enum
{
    PING,
    PONG
} uart_buffers;

typedef enum
{
    PING_DONE,
    PING_TX,
    PONG_DONE,
    PONG_TX,
} uart_tx_states;

typedef enum
{
    EMPTY,
    FILLING,
    FILLED
} uart_buffer_states;

static const struct buffer_state
{
    uart_tx_states DONE;
    uart_tx_states TX;
} BUF_STATE[2] = {{ PING_DONE, PING_TX },
                  { PONG_DONE, PONG_TX } };

struct uart_tx_buffer
{
    uint8_t __attribute__((aligned(32))) buf[BUFFER_SIZE];
    uint32_t count;
    uart_buffer_states state;
};

static struct uart_context
{
    volatile struct uart_tx_buffer tx_buf[2];
    volatile uart_tx_states tx_state;
} uart_ctx = { { { { 0 }, 0, EMPTY }, { { 0 }, 0, EMPTY } }, PING_DONE };

static void stop_uart(void)
{
    UARTE_ID->TASKS_STOPTX = 1;
}

static void start_uart_tx(uart_buffers tx_buf)
{
    UARTE_ID->EVENTS_ENDTX = 0;

    UARTE_ID->TXD.PTR = (uint32_t) uart_ctx.tx_buf[tx_buf].buf;
    UARTE_ID->TXD.MAXCNT = uart_ctx.tx_buf[tx_buf].count;

    UARTE_ID->TASKS_STARTTX = 1;
}

/**
 *  UARTE interrupt routine.
 */
#if ISR_MANAGER == 1
void uart_printf_uart_Handler (void)
#else
void UARTE0_UART0_IRQHandler(void)
#endif
{
    if (1 == UARTE_ID->EVENTS_ENDTX)
    {
#if ISR_MANAGER == 0
        UARTE_ID->EVENTS_ENDTX = 0;
        (void) UARTE_ID->EVENTS_ENDTX;
#endif
        uart_buffers current_buf = PONG, other_buf = PING;
        if (BUF_STATE[PING].TX == uart_ctx.tx_state)
        {
            current_buf = PING;
            other_buf = PONG;
        }   // Else state of PONG_TX is taken care of in initialization

        uart_ctx.tx_buf[current_buf].state = EMPTY;
        uart_ctx.tx_buf[current_buf].count = 0;

        if (FILLED == uart_ctx.tx_buf[other_buf].state)
        {
            start_uart_tx(other_buf);
            uart_ctx.tx_state = BUF_STATE[other_buf].TX;
        }
        else
        {
            uart_ctx.tx_state = BUF_STATE[current_buf].DONE;
            stop_uart();    //So that UARTE doesn't consume power
        }
    }
}

/**
 */
void printf_callback(void* str_end, char ch)
{
    uart_buffers current_buf = PONG, other_buf = PING;
    if ((BUF_STATE[PING].TX == uart_ctx.tx_state) || (BUF_STATE[PING].DONE == uart_ctx.tx_state))
    {
        current_buf = PING;
        other_buf = PONG;
    }

    //Callback informing the end of the printf string
    if (START_TX == ((uint32_t) str_end))
    {
        if (PING_DONE == uart_ctx.tx_state)
        {
            start_uart_tx(PONG);
            uart_ctx.tx_state = PONG_TX;
        }
        if (PONG_DONE == uart_ctx.tx_state)
        {
            start_uart_tx(PING);
            uart_ctx.tx_state = PING_TX;
        }
        uart_ctx.tx_buf[other_buf].state = FILLED;

    }
    else
    {
        // Check for exceeding the buffer size
        if (uart_ctx.tx_buf[other_buf].count < BUFFER_SIZE)
        {
            uart_ctx.tx_buf[other_buf].buf[uart_ctx.tx_buf[other_buf].count] = ch;
            uart_ctx.tx_buf[other_buf].count++;
            uart_ctx.tx_buf[other_buf].state = FILLING;
        }
        else
        {
            while (BUF_STATE[current_buf].TX == uart_ctx.tx_state)
            {
                //__WFI();
            }
            start_uart_tx(other_buf);
            uart_ctx.tx_buf[other_buf].state = FILLED;    // Not required, but just for completeness
            uart_ctx.tx_state = BUF_STATE[other_buf].TX;
        }
    }
}

void uart_printf_init(uart_printf_baud_t baud_rate)
{
    /* Configure TX and RX pins from board.h */
    hal_gpio_cfg_output(TX_PIN_NUMBER, 0);
    hal_gpio_cfg_input(RX_PIN_NUMBER, GPIO_PIN_CNF_PULL_Disabled);
    UARTE_ID->PSEL.TXD = TX_PIN_NUMBER;
    UARTE_ID->PSEL.RXD = RX_PIN_NUMBER;

    /* Configure CTS and RTS pins if HWFC is true in board.h */

#if HWFC
    {
        hal_gpio_cfg_output(RTS_PIN_NUMBER, 0);
        hal_gpio_cfg_input(CTS_PIN_NUMBER, GPIO_PIN_CNF_PULL_Disabled);
        UARTE_ID->PSEL.RTS = RTS_PIN_NUMBER;
        UARTE_ID->PSEL.CTS = CTS_PIN_NUMBER;
        UARTE_ID->CONFIG = (UARTE_CONFIG_HWFC_Enabled << UARTE_CONFIG_HWFC_Pos);
    }
#endif

    /* Configure other UART parameters, BAUD rate is defined in nrf52-uart.h    */
    UARTE_ID->BAUDRATE = (baud_rate << UARTE_BAUDRATE_BAUDRATE_Pos);
    UARTE_ID->ENABLE = (UARTE_ENABLE_ENABLE_Enabled << UARTE_ENABLE_ENABLE_Pos);

    //Send in any other value other than START_TX in first argument
    init_printf((void *) !(START_TX), printf_callback);

    // Enable UART TX End interrupt only
    UARTE_ID->INTENSET = (UARTE_INTENSET_ENDTX_Set << UARTE_INTENSET_ENDTX_Pos);

    NVIC_SetPriority(UARTE0_UART0_IRQn, APP_IRQ_PRIORITY_LOW);
    NVIC_EnableIRQ(UARTE0_UART0_IRQn);

}
/** @} */
