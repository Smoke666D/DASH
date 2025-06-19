################################################################################
# MRS Version: 2.1.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Debug/debug.c 

C_DEPS += \
./Debug/debug.d 

OBJS += \
./Debug/debug.o 



# Each subdirectory must supply rules for building sources it contributes
Debug/%.o: ../Debug/%.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -g -I"c:/MRS_DATA/workspace/DASH/Debug" -I"c:/MRS_DATA/workspace/DASH/CANopenNode" -I"c:/MRS_DATA/workspace/DASH/CANopenNode/301" -I"c:/MRS_DATA/workspace/DASH/CANopenNode/303" -I"c:/MRS_DATA/workspace/DASH/CANopenNode/304" -I"c:/MRS_DATA/workspace/DASH/CANopenNode/305" -I"c:/MRS_DATA/workspace/DASH/CANopenNode/309" -I"c:/MRS_DATA/workspace/DASH/CANopenNode/keypad" -I"c:/MRS_DATA/workspace/DASH/Core" -I"c:/MRS_DATA/workspace/DASH/User" -I"c:/MRS_DATA/workspace/DASH/Peripheral/inc" -I"c:/MRS_DATA/workspace/DASH/FreeRTOS" -I"c:/MRS_DATA/workspace/DASH/FreeRTOS/include" -I"c:/MRS_DATA/workspace/DASH/FreeRTOS/portable" -I"c:/MRS_DATA/workspace/DASH/FreeRTOS/portable/Common" -I"c:/MRS_DATA/workspace/DASH/FreeRTOS/portable/GCC/RISC-V" -I"c:/MRS_DATA/workspace/DASH/FreeRTOS/portable/GCC/RISC-V/chip_specific_extensions/RV32I_PFIC_no_extensions" -I"c:/MRS_DATA/workspace/DASH/FreeRTOS/portable/MemMang" -I"c:/MRS_DATA/workspace/DASH/DRIVER" -I"c:/MRS_DATA/workspace/DASH/LIB" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
