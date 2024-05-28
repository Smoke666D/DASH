################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CANopenNode/301/CO_Emergency.c \
../CANopenNode/301/CO_HBconsumer.c \
../CANopenNode/301/CO_NMT_Heartbeat.c \
../CANopenNode/301/CO_ODinterface.c \
../CANopenNode/301/CO_PDO.c \
../CANopenNode/301/CO_SDOclient.c \
../CANopenNode/301/CO_SDOserver.c \
../CANopenNode/301/CO_SYNC.c \
../CANopenNode/301/CO_TIME.c \
../CANopenNode/301/CO_fifo.c \
../CANopenNode/301/crc16-ccitt.c 

OBJS += \
./CANopenNode/301/CO_Emergency.o \
./CANopenNode/301/CO_HBconsumer.o \
./CANopenNode/301/CO_NMT_Heartbeat.o \
./CANopenNode/301/CO_ODinterface.o \
./CANopenNode/301/CO_PDO.o \
./CANopenNode/301/CO_SDOclient.o \
./CANopenNode/301/CO_SDOserver.o \
./CANopenNode/301/CO_SYNC.o \
./CANopenNode/301/CO_TIME.o \
./CANopenNode/301/CO_fifo.o \
./CANopenNode/301/crc16-ccitt.o 

C_DEPS += \
./CANopenNode/301/CO_Emergency.d \
./CANopenNode/301/CO_HBconsumer.d \
./CANopenNode/301/CO_NMT_Heartbeat.d \
./CANopenNode/301/CO_ODinterface.d \
./CANopenNode/301/CO_PDO.d \
./CANopenNode/301/CO_SDOclient.d \
./CANopenNode/301/CO_SDOserver.d \
./CANopenNode/301/CO_SYNC.d \
./CANopenNode/301/CO_TIME.d \
./CANopenNode/301/CO_fifo.d \
./CANopenNode/301/crc16-ccitt.d 


# Each subdirectory must supply rules for building sources it contributes
CANopenNode/301/%.o: ../CANopenNode/301/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused  -g -I"C:\MRS_DATA\workspace\DASH\Drivers" -I"C:\MRS_DATA\workspace\DASH\Debug" -I"C:\MRS_DATA\workspace\DASH\HWLIB" -I"C:\MRS_DATA\workspace\DASH\HAL" -I"C:\MRS_DATA\workspace\DASH\CANopenNode" -I"C:\MRS_DATA\workspace\DASH\CANopenNode\301" -I"C:\MRS_DATA\workspace\DASH\CANopenNode\303" -I"C:\MRS_DATA\workspace\DASH\CANopenNode\304" -I"C:\MRS_DATA\workspace\DASH\CANopenNode\305" -I"C:\MRS_DATA\workspace\DASH\CANopenNode\309" -I"C:\MRS_DATA\workspace\DASH\CANopenNode\keypad" -I"C:\MRS_DATA\workspace\DASH\Core" -I"C:\MRS_DATA\workspace\DASH\User" -I"C:\MRS_DATA\workspace\DASH\Peripheral\inc" -I"C:\MRS_DATA\workspace\DASH\FreeRTOS" -I"C:\MRS_DATA\workspace\DASH\FreeRTOS\include" -I"C:\MRS_DATA\workspace\DASH\FreeRTOS\portable" -I"C:\MRS_DATA\workspace\DASH\FreeRTOS\portable\Common" -I"C:\MRS_DATA\workspace\DASH\FreeRTOS\portable\GCC\RISC-V" -I"C:\MRS_DATA\workspace\DASH\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -I"C:\MRS_DATA\workspace\DASH\FreeRTOS\portable\MemMang" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

