################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CF/412/D.cpp \
../CF/412/E.cpp 

OBJS += \
./CF/412/D.o \
./CF/412/E.o 

CPP_DEPS += \
./CF/412/D.d \
./CF/412/E.d 


# Each subdirectory must supply rules for building sources it contributes
CF/412/%.o: ../CF/412/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


