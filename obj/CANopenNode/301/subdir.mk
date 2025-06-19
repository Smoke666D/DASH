################################################################################
# MRS Version: 2.1.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CANopenNode/301/CO_Emergency.c \
../CANopenNode/301/CO_HBconsumer.c \
../CANopenNode/301/CO_NMT_Heartbeat.c \
../CANopenNode/301/CO_Node_Guarding.c \
../CANopenNode/301/CO_ODinterface.c \
../CANopenNode/301/CO_PDO.c \
../CANopenNode/301/CO_SDOclient.c \
../CANopenNode/301/CO_SDOserver.c \
../CANopenNode/301/CO_SYNC.c \
../CANopenNode/301/CO_TIME.c \
../CANopenNode/301/CO_fifo.c \
../CANopenNode/301/crc16-ccitt.c 

C_DEPS += \
./CANopenNode/301/CO_Emergency.d \
./CANopenNode/301/CO_HBconsumer.d \
./CANopenNode/301/CO_NMT_Heartbeat.d \
./CANopenNode/301/CO_Node_Guarding.d \
./CANopenNode/301/CO_ODinterface.d \
./CANopenNode/301/CO_PDO.d \
./CANopenNode/301/CO_SDOclient.d \
./CANopenNode/301/CO_SDOserver.d \
./CANopenNode/301/CO_SYNC.d \
./CANopenNode/301/CO_TIME.d \
./CANopenNode/301/CO_fifo.d \
./CANopenNode/301/crc16-ccitt.d 

OBJS += \
./CANopenNode/301/CO_Emergency.o \
./CANopenNode/301/CO_HBconsumer.o \
./CANopenNode/301/CO_NMT_Heartbeat.o \
./CANopenNode/301/CO_Node_Guarding.o \
./CANopenNode/301/CO_ODinterface.o \
./CANopenNode/301/CO_PDO.o \
./CANopenNode/301/CO_SDOclient.o \
./CANopenNode/301/CO_SDOserver.o \
./CANopenNode/301/CO_SYNC.o \
./CANopenNode/301/CO_TIME.o \
./CANopenNode/301/CO_fifo.o \
./CANopenNode/301/crc16-ccitt.o 



# Each subdirectory must supply rules for building sources it contributes
CANopenNode/301/%.o: ../CANopenNode/301/%.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -g -I"c:/MRS_DATA/workspace/DASH/Debug" -I"c:/MRS_DATA/workspace/DASH/CANopenNode" -I"c:/MRS_DATA/workspace/DASH/CANopenNode/301" -I"c:/MRS_DATA/workspace/DASH/CANopenNode/303" -I"c:/MRS_DATA/workspace/DASH/CANopenNode/304" -I"c:/MRS_DATA/workspace/DASH/CANopenNode/305" -I"c:/MRS_DATA/workspace/DASH/CANopenNode/309" -I"c:/MRS_DATA/workspace/DASH/CANopenNode/keypad" -I"c:/MRS_DATA/workspace/DASH/Core" -I"c:/MRS_DATA/workspace/DASH/User" -I"c:/MRS_DATA/workspace/DASH/Peripheral/inc" -I"c:/MRS_DATA/workspace/DASH/FreeRTOS" -I"c:/MRS_DATA/workspace/DASH/FreeRTOS/include" -I"c:/MRS_DATA/workspace/DASH/FreeRTOS/portable" -I"c:/MRS_DATA/workspace/DASH/FreeRTOS/portable/Common" -I"c:/MRS_DATA/workspace/DASH/FreeRTOS/portable/GCC/RISC-V" -I"c:/MRS_DATA/workspace/DASH/FreeRTOS/portable/GCC/RISC-V/chip_specific_extensions/RV32I_PFIC_no_extensions" -I"c:/MRS_DATA/workspace/DASH/FreeRTOS/portable/MemMang" -I"c:/Users/i.dymov/Documents/SYSTEM_LIB/HAL_LIB" -I"c:/MRS_DATA/workspace/DASH/DRIVER" -I"c:/MRS_DATA/workspace/DASH/LIB" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
