################################################################################
# MRS Version: 1.9.2
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS/portable/MemMang/heap_4.c 

OBJS += \
./FreeRTOS/portable/MemMang/heap_4.o 

C_DEPS += \
./FreeRTOS/portable/MemMang/heap_4.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/portable/MemMang/%.o: ../FreeRTOS/portable/MemMang/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused  -g -I"C:\MRS_DATA\workspace\DASH\HAL_DRIVER" -I"C:\MRS_DATA\workspace\DASH\Debug" -I"C:\MRS_DATA\workspace\DASH\HAL" -I"C:\MRS_DATA\workspace\DASH\CANopenNode" -I"C:\MRS_DATA\workspace\DASH\CANopenNode\301" -I"C:\MRS_DATA\workspace\DASH\CANopenNode\303" -I"C:\MRS_DATA\workspace\DASH\CANopenNode\304" -I"C:\MRS_DATA\workspace\DASH\CANopenNode\305" -I"C:\MRS_DATA\workspace\DASH\CANopenNode\309" -I"C:\MRS_DATA\workspace\DASH\CANopenNode\keypad" -I"C:\MRS_DATA\workspace\DASH\Core" -I"C:\MRS_DATA\workspace\DASH\User" -I"C:\MRS_DATA\workspace\DASH\Peripheral\inc" -I"C:\MRS_DATA\workspace\DASH\FreeRTOS" -I"C:\MRS_DATA\workspace\DASH\FreeRTOS\include" -I"C:\MRS_DATA\workspace\DASH\FreeRTOS\portable" -I"C:\MRS_DATA\workspace\DASH\FreeRTOS\portable\Common" -I"C:\MRS_DATA\workspace\DASH\FreeRTOS\portable\GCC\RISC-V" -I"C:\MRS_DATA\workspace\DASH\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -I"C:\MRS_DATA\workspace\DASH\FreeRTOS\portable\MemMang" -I"C:\Users\i.dymov\Documents\SYSTEM_LIB\HAL_LIB" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

