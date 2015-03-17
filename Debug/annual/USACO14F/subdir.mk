################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../annual/USACO14F/censor.cpp \
../annual/USACO14F/fencing.cpp \
../annual/USACO14F/hopscotch.cpp 

OBJS += \
./annual/USACO14F/censor.o \
./annual/USACO14F/fencing.o \
./annual/USACO14F/hopscotch.o 

CPP_DEPS += \
./annual/USACO14F/censor.d \
./annual/USACO14F/fencing.d \
./annual/USACO14F/hopscotch.d 


# Each subdirectory must supply rules for building sources it contributes
annual/USACO14F/%.o: ../annual/USACO14F/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


