################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CF/100625/B.cpp \
../CF/100625/G.cpp 

OBJS += \
./CF/100625/B.o \
./CF/100625/G.o 

CPP_DEPS += \
./CF/100625/B.d \
./CF/100625/G.d 


# Each subdirectory must supply rules for building sources it contributes
CF/100625/%.o: ../CF/100625/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


