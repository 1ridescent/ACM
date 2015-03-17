################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CF/491/B.cpp \
../CF/491/C.cpp 

OBJS += \
./CF/491/B.o \
./CF/491/C.o 

CPP_DEPS += \
./CF/491/B.d \
./CF/491/C.d 


# Each subdirectory must supply rules for building sources it contributes
CF/491/%.o: ../CF/491/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


