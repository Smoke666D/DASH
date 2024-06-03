################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/hal_adc.c \
../HAL/hal_can.c \
../HAL/hal_dma.c \
../HAL/hal_gpio.c \
../HAL/hal_i2c.c \
../HAL/hal_rtc.c \
../HAL/hal_spi.c \
../HAL/hal_timers.c \
../HAL/hal_wdt.c 

OBJS += \
./HAL/hal_adc.o \
./HAL/hal_can.o \
./HAL/hal_dma.o \
./HAL/hal_gpio.o \
./HAL/hal_i2c.o \
./HAL/hal_rtc.o \
./HAL/hal_spi.o \
./HAL/hal_timers.o \
./HAL/hal_wdt.o 

C_DEPS += \
./HAL/hal_adc.d \
./HAL/hal_can.d \
./HAL/hal_dma.d \
./HAL/hal_gpio.d \
./HAL/hal_i2c.d \
./HAL/hal_rtc.d \
./HAL/hal_spi.d \
./HAL/hal_timers.d \
./HAL/hal_wdt.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/%.o: ../HAL/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -O1 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused  -g -I"C:\MRS_DATA\workspace\DASH\Drivers" -I"C:\MRS_DATA\workspace\DASH\Debug" -I"C:\MRS_DATA\workspace\DASH\HWLIB" -I"C:\MRS_DATA\workspace\DASH\CANopenNode" -I"C:\MRS_DATA\workspace\DASH\CANopenNode\301" -I"C:\MRS_DATA\workspace\DASH\CANopenNode\303" -I"C:\MRS_DATA\workspace\DASH\CANopenNode\304" -I"C:\MRS_DATA\workspace\DASH\CANopenNode\305" -I"C:\MRS_DATA\workspace\DASH\CANopenNode\309" -I"C:\MRS_DATA\workspace\DASH\CANopenNode\keypad" -I"C:\MRS_DATA\workspace\DASH\Core" -I"C:\MRS_DATA\workspace\DASH\User" -I"C:\MRS_DATA\workspace\DASH\Peripheral\inc" -I"C:\MRS_DATA\workspace\DASH\FreeRTOS" -I"C:\MRS_DATA\workspace\DASH\FreeRTOS\include" -I"C:\MRS_DATA\workspace\DASH\FreeRTOS\portable" -I"C:\MRS_DATA\workspace\DASH\FreeRTOS\portable\Common" -I"C:\MRS_DATA\workspace\DASH\FreeRTOS\portable\GCC\RISC-V" -I"C:\MRS_DATA\workspace\DASH\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -I"C:\MRS_DATA\workspace\DASH\FreeRTOS\portable\MemMang" -I"C:\MRS_DATA\workspace\DASH\HAL" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

