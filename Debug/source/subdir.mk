################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/MazeGame.c \
../source/accelerometer.c \
../source/main.c 

S_SRCS += \
../source/function.s 

C_DEPS += \
./source/MazeGame.d \
./source/accelerometer.d \
./source/main.d 

OBJS += \
./source/MazeGame.o \
./source/accelerometer.o \
./source/function.o \
./source/main.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -DCPU_MK66FN2M0VMD18 -DCPU_MK66FN2M0VMD18_cm4 -DPRINTF_ADVANCED_ENABLE=1 -DFRDM_K66F -DFREEDOM -DMCUXPRESSO_SDK -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"C:\Users\masum\Documents\MCUXpressoIDE_11.10.0_3148\workspace20\project-main\MazeGameFinal\source" -I"C:\Users\masum\Documents\MCUXpressoIDE_11.10.0_3148\workspace20\project-main\MazeGameFinal\utilities" -I"C:\Users\masum\Documents\MCUXpressoIDE_11.10.0_3148\workspace20\project-main\MazeGameFinal\drivers" -I"C:\Users\masum\Documents\MCUXpressoIDE_11.10.0_3148\workspace20\project-main\MazeGameFinal\device" -I"C:\Users\masum\Documents\MCUXpressoIDE_11.10.0_3148\workspace20\project-main\MazeGameFinal\component\uart" -I"C:\Users\masum\Documents\MCUXpressoIDE_11.10.0_3148\workspace20\project-main\MazeGameFinal\component\lists" -I"C:\Users\masum\Documents\MCUXpressoIDE_11.10.0_3148\workspace20\project-main\MazeGameFinal\CMSIS" -I"C:\Users\masum\Documents\MCUXpressoIDE_11.10.0_3148\workspace20\project-main\MazeGameFinal\board" -I"C:\Users\masum\Documents\MCUXpressoIDE_11.10.0_3148\workspace20\project-main\MazeGameFinal\frdmk66f\driver_examples\i2c\read_accel_value_transfer" -O0 -fno-common -g3 -gdwarf-4 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/%.o: ../source/%.s source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU Assembler'
	arm-none-eabi-gcc -c -x assembler-with-cpp -D__REDLIB__ -I"C:\Users\masum\Documents\MCUXpressoIDE_11.10.0_3148\workspace20\project-main\MazeGameFinal\source" -g3 -gdwarf-4 -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -specs=redlib.specs -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/MazeGame.d ./source/MazeGame.o ./source/accelerometer.d ./source/accelerometer.o ./source/function.o ./source/main.d ./source/main.o

.PHONY: clean-source

