################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CF/489/E.cpp \
../CF/489/F.cpp 

OBJS += \
./CF/489/E.o \
./CF/489/F.o 

CPP_DEPS += \
./CF/489/E.d \
./CF/489/F.d 


# Each subdirectory must supply rules for building sources it contributes
CF/489/%.o: ../CF/489/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


