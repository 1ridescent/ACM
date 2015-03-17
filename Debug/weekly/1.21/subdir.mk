################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../weekly/1.21/A.cpp \
../weekly/1.21/E.cpp 

OBJS += \
./weekly/1.21/A.o \
./weekly/1.21/E.o 

CPP_DEPS += \
./weekly/1.21/A.d \
./weekly/1.21/E.d 


# Each subdirectory must supply rules for building sources it contributes
weekly/1.21/%.o: ../weekly/1.21/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


