################################################################################
# MRS Version: 1.9.2
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HWLIB/hw_lib_adc.c \
../HWLIB/hw_lib_din.c 

OBJS += \
./HWLIB/hw_lib_adc.o \
./HWLIB/hw_lib_din.o 

C_DEPS += \
./HWLIB/hw_lib_adc.d \
./HWLIB/hw_lib_din.d 


# Each subdirectory must supply rules for building sources it contributes
HWLIB/%.o: ../HWLIB/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused  -g -I"C:\Users\i.dymov\Documents\SYSTEM_LIB\HAL_LIB" -I"C:\MRS_DATA\workspace\DASH\HAL_DRIVER" -I"C:\MRS_DATA\workspace\DASH\Debug" -I"C:\MRS_DATA\workspace\DASH\HWLIB" -I"C:\MRS_DATA\workspace\DASH\HAL" -I"C:\MRS_DATA\workspace\DASH\CANopenNode" -I"C:\MRS_DATA\workspace\DASH\CANopenNode\301" -I"C:\MRS_DATA\workspace\DASH\CANopenNode\303" -I"C:\MRS_DATA\workspace\DASH\CANopenNode\304" -I"C:\MRS_DATA\workspace\DASH\CANopenNode\305" -I"C:\MRS_DATA\workspace\DASH\CANopenNode\309" -I"C:\MRS_DATA\workspace\DASH\CANopenNode\keypad" -I"C:\MRS_DATA\workspace\DASH\Core" -I"C:\MRS_DATA\workspace\DASH\User" -I"C:\MRS_DATA\workspace\DASH\Peripheral\inc" -I"C:\MRS_DATA\workspace\DASH\FreeRTOS" -I"C:\MRS_DATA\workspace\DASH\FreeRTOS\include" -I"C:\MRS_DATA\workspace\DASH\FreeRTOS\portable" -I"C:\MRS_DATA\workspace\DASH\FreeRTOS\portable\Common" -I"C:\MRS_DATA\workspace\DASH\FreeRTOS\portable\GCC\RISC-V" -I"C:\MRS_DATA\workspace\DASH\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -I"C:\MRS_DATA\workspace\DASH\FreeRTOS\portable\MemMang" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

