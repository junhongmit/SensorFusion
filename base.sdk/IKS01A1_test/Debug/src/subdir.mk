################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
LD_SRCS += \
../src/lscript.ld 

CC_SRCS += \
../src/main.cc 

C_SRCS += \
../src/HTS221.c \
../src/LIS3MDL.c \
../src/LPS25HB.c \
../src/LSM6DS0.c \
../src/myiic.c 

CC_DEPS += \
./src/main.d 

OBJS += \
./src/HTS221.o \
./src/LIS3MDL.o \
./src/LPS25HB.o \
./src/LSM6DS0.o \
./src/main.o \
./src/myiic.o 

C_DEPS += \
./src/HTS221.d \
./src/LIS3MDL.d \
./src/LPS25HB.d \
./src/LSM6DS0.d \
./src/myiic.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MicroBlaze g++ compiler'
	mb-g++ -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -I../../IKS01A1_test_bsp/iop_arduino_mb/include -mlittle-endian -mcpu=v10.0 -mxl-soft-mul -Wl,--no-relax -ffunction-sections -fdata-sections -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: MicroBlaze g++ compiler'
	mb-g++ -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -I../../IKS01A1_test_bsp/iop_arduino_mb/include -mlittle-endian -mcpu=v10.0 -mxl-soft-mul -Wl,--no-relax -ffunction-sections -fdata-sections -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


