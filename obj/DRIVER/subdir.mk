################################################################################
# MRS Version: 2.1.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DRIVER/hal_adc_ch32.c \
../DRIVER/hal_can_ch32.c \
../DRIVER/hal_dma_ch32.c \
../DRIVER/hal_flash_ch32.c \
../DRIVER/hal_gpio_ch32.c \
../DRIVER/hal_i2c_ch32.c \
../DRIVER/hal_irq.c \
../DRIVER/hal_rtc_ch32.c \
../DRIVER/hal_spi_ch32.c \
../DRIVER/hal_timers_ch32.c \
../DRIVER/hal_wdt_ch32.c 

C_DEPS += \
./DRIVER/hal_adc_ch32.d \
./DRIVER/hal_can_ch32.d \
./DRIVER/hal_dma_ch32.d \
./DRIVER/hal_flash_ch32.d \
./DRIVER/hal_gpio_ch32.d \
./DRIVER/hal_i2c_ch32.d \
./DRIVER/hal_irq.d \
./DRIVER/hal_rtc_ch32.d \
./DRIVER/hal_spi_ch32.d \
./DRIVER/hal_timers_ch32.d \
./DRIVER/hal_wdt_ch32.d 

OBJS += \
./DRIVER/hal_adc_ch32.o \
./DRIVER/hal_can_ch32.o \
./DRIVER/hal_dma_ch32.o \
./DRIVER/hal_flash_ch32.o \
./DRIVER/hal_gpio_ch32.o \
./DRIVER/hal_i2c_ch32.o \
./DRIVER/hal_irq.o \
./DRIVER/hal_rtc_ch32.o \
./DRIVER/hal_spi_ch32.o \
./DRIVER/hal_timers_ch32.o \
./DRIVER/hal_wdt_ch32.o 



# Each subdirectory must supply rules for building sources it contributes
DRIVER/%.o: ../DRIVER/%.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -g -I"c:/MRS_DATA/workspace/DASH/Debug" -I"c:/MRS_DATA/workspace/DASH/CANopenNode" -I"c:/MRS_DATA/workspace/DASH/CANopenNode/301" -I"c:/MRS_DATA/workspace/DASH/CANopenNode/303" -I"c:/MRS_DATA/workspace/DASH/CANopenNode/304" -I"c:/MRS_DATA/workspace/DASH/CANopenNode/305" -I"c:/MRS_DATA/workspace/DASH/CANopenNode/309" -I"c:/MRS_DATA/workspace/DASH/CANopenNode/keypad" -I"c:/MRS_DATA/workspace/DASH/Core" -I"c:/MRS_DATA/workspace/DASH/User" -I"c:/MRS_DATA/workspace/DASH/Peripheral/inc" -I"c:/MRS_DATA/workspace/DASH/FreeRTOS" -I"c:/MRS_DATA/workspace/DASH/FreeRTOS/include" -I"c:/MRS_DATA/workspace/DASH/FreeRTOS/portable" -I"c:/MRS_DATA/workspace/DASH/FreeRTOS/portable/Common" -I"c:/MRS_DATA/workspace/DASH/FreeRTOS/portable/GCC/RISC-V" -I"c:/MRS_DATA/workspace/DASH/FreeRTOS/portable/GCC/RISC-V/chip_specific_extensions/RV32I_PFIC_no_extensions" -I"c:/MRS_DATA/workspace/DASH/FreeRTOS/portable/MemMang" -I"c:/MRS_DATA/workspace/DASH/DRIVER" -I"c:/MRS_DATA/workspace/DASH/LIB" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
