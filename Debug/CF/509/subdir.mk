################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CF/509/D.cpp \
../CF/509/F.cpp 

OBJS += \
./CF/509/D.o \
./CF/509/F.o 

CPP_DEPS += \
./CF/509/D.d \
./CF/509/F.d 


# Each subdirectory must supply rules for building sources it contributes
CF/509/%.o: ../CF/509/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


