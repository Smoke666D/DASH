################################################################################
# MRS Version: 2.1.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/CanOpenNode.c \
../User/DataModel.c \
../User/ch32v20x_it.c \
../User/dash_draw.c \
../User/init.c \
../User/inputs.c \
../User/led.c \
../User/main.c \
../User/process.c \
../User/system_ch32v20x.c \
../User/system_init.c 

C_DEPS += \
./User/CanOpenNode.d \
./User/DataModel.d \
./User/ch32v20x_it.d \
./User/dash_draw.d \
./User/init.d \
./User/inputs.d \
./User/led.d \
./User/main.d \
./User/process.d \
./User/system_ch32v20x.d \
./User/system_init.d 

OBJS += \
./User/CanOpenNode.o \
./User/DataModel.o \
./User/ch32v20x_it.o \
./User/dash_draw.o \
./User/init.o \
./User/inputs.o \
./User/led.o \
./User/main.o \
./User/process.o \
./User/system_ch32v20x.o \
./User/system_init.o 



# Each subdirectory must supply rules for building sources it contributes
User/%.o: ../User/%.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -g -I"c:/MRS_DATA/workspace/DASH/Debug" -I"c:/MRS_DATA/workspace/DASH/CANopenNode" -I"c:/MRS_DATA/workspace/DASH/CANopenNode/301" -I"c:/MRS_DATA/workspace/DASH/CANopenNode/303" -I"c:/MRS_DATA/workspace/DASH/CANopenNode/304" -I"c:/MRS_DATA/workspace/DASH/CANopenNode/305" -I"c:/MRS_DATA/workspace/DASH/CANopenNode/309" -I"c:/MRS_DATA/workspace/DASH/CANopenNode/keypad" -I"c:/MRS_DATA/workspace/DASH/Core" -I"c:/MRS_DATA/workspace/DASH/User" -I"c:/MRS_DATA/workspace/DASH/Peripheral/inc" -I"c:/MRS_DATA/workspace/DASH/FreeRTOS" -I"c:/MRS_DATA/workspace/DASH/FreeRTOS/include" -I"c:/MRS_DATA/workspace/DASH/FreeRTOS/portable" -I"c:/MRS_DATA/workspace/DASH/FreeRTOS/portable/Common" -I"c:/MRS_DATA/workspace/DASH/FreeRTOS/portable/GCC/RISC-V" -I"c:/MRS_DATA/workspace/DASH/FreeRTOS/portable/GCC/RISC-V/chip_specific_extensions/RV32I_PFIC_no_extensions" -I"c:/MRS_DATA/workspace/DASH/FreeRTOS/portable/MemMang" -I"c:/Users/i.dymov/Documents/SYSTEM_LIB/HAL_LIB" -I"c:/MRS_DATA/workspace/DASH/DRIVER" -I"c:/MRS_DATA/workspace/DASH/LIB" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
