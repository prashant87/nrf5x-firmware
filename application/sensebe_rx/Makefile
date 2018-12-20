
BOARD           := BOARD_SENSEBE_RX_REV1
SLNO            := 682073614
BLE_REQD        := BLE_STACK_SUPPORT_REQD
PINRESET_REQD   := CONFIG_GPIO_AS_PINRESET
DEBUGGER        := BMP
LOGGER          := LOG_UART_PRINTF
FW_VER_VAL      := 0
MS_TIMER_FREQ   := 32768
SD_USED         := s112
SD_VER          := 6.0.0

SDK_DIR         = ../../SDK_components
DOC_DIR         = ../../doc
PLATFORM_DIR    = ../../platform
CODEBASE_DIR    = ../../codebase

INCLUDEDIRS	= .
INCLUDEDIRS	+= $(PLATFORM_DIR)
ifneq ($(SD_USED_LC),blank)
INCLUDEDIRS += $(SDK_DIR)/softdevice/$(SD_USED)/headers
endif
INCLUDEDIRS += $(CODEBASE_DIR)/hal
INCLUDEDIRS += $(CODEBASE_DIR)/segger_rtt
INCLUDEDIRS += $(CODEBASE_DIR)/sd_assist
INCLUDEDIRS += $(CODEBASE_DIR)/peripheral_modules
INCLUDEDIRS += $(CODEBASE_DIR)/util
INCLUDEDIRS += ./led_sequences

C_SRC_DIRS = .
C_SRC_DIRS += $(CODEBASE_DIR)/segger_rtt
C_SRC_DIRS += $(CODEBASE_DIR)/hal
C_SRC_DIRS += $(CODEBASE_DIR)/sd_assist
C_SRC_DIRS += $(CODEBASE_DIR)/peripheral_modules
C_SRC_DIRS += $(CODEBASE_DIR)/util
C_SRC_DIRS += ./led_sequences

C_SRC = main.c
C_SRC += nrf_assert.c app_error.c
C_SRC += hal_clocks.c ms_timer.c
ifeq ($(LOGGER), LOG_SEGGER_RTT)
C_SRC += SEGGER_RTT.c SEGGER_RTT_printf.c
else ifeq ($(LOGGER), LOG_UART_DMA_PRINTF)
C_SRC += uart_printf.c tinyprintf.c
else ifeq ($(LOGGER), LOG_UART_PRINTF)
C_SRC += hal_uart.c tinyprintf.c
else
endif
C_SRC += hal_wdt.c
C_SRC += nrf_util.c irq_msg_util.c
C_SRC += device_tick.c
C_SRC += evt_sd_handler.c
C_SRC += button_ui.c
C_SRC += simple_adc.c
C_SRC += sensebe_ble.c
C_SRC += hal_pwm.c
C_SRC += dev_id_fw_ver.c
C_SRC += out_pattern_gen.c
C_SRC += sensebe_rx_detect.c
C_SRC += led_ui.c
C_SRC += led_seq.c
C_SRC += ir_detect.c
#Gets the name of the application folder
APPLN = $(shell basename $(PWD))

CFLAGS_APP = -DDEBUG
CFLAGS_APP += -D$(BLE_REQD)
CFLAGS_APP += -D$(PINRESET_REQD)
CFLAGS_APP += -D$(LOGGER)
CFLAGS_APP += -DFW_VER=$(FW_VER_VAL)
CFLAGS_APP += -DMS_TIMER_FREQ=$(MS_TIMER_FREQ)

#Lower case of BOARD
BOARD_HEADER  = $(shell echo $(BOARD) | tr A-Z a-z)
include $(PLATFORM_DIR)/Makefile.$(BOARD_HEADER)

include ../Makefile.common