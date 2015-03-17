################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../weekly/1.28/C.cpp \
../weekly/1.28/E.cpp 

OBJS += \
./weekly/1.28/C.o \
./weekly/1.28/E.o 

CPP_DEPS += \
./weekly/1.28/C.d \
./weekly/1.28/E.d 


# Each subdirectory must supply rules for building sources it contributes
weekly/1.28/%.o: ../weekly/1.28/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


