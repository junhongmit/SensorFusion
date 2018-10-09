################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
LD_SRCS += \
../src/lscript.ld 

C_SRCS += \
../src/HTS221.c \
../src/LIS3MDL.c \
../src/LPS25HB.c \
../src/LSM6DS0.c \
../src/arduino_IKS01A1.c \
../src/myiic.c 

OBJS += \
./src/HTS221.o \
./src/LIS3MDL.o \
./src/LPS25HB.o \
./src/LSM6DS0.o \
./src/arduino_IKS01A1.o \
./src/myiic.o 

C_DEPS += \
./src/HTS221.d \
./src/LIS3MDL.d \
./src/LPS25HB.d \
./src/LSM6DS0.d \
./src/arduino_IKS01A1.d \
./src/myiic.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MicroBlaze gcc compiler'
	mb-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -I../../IKS01A1_test_bsp/iop3_mb/include -mlittle-endian -mcpu=v9.6 -mxl-soft-mul -Wl,--no-relax -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


