################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../weekly/2.25/D.cpp \
../weekly/2.25/D0.cpp \
../weekly/2.25/E.cpp 

OBJS += \
./weekly/2.25/D.o \
./weekly/2.25/D0.o \
./weekly/2.25/E.o 

CPP_DEPS += \
./weekly/2.25/D.d \
./weekly/2.25/D0.d \
./weekly/2.25/E.d 


# Each subdirectory must supply rules for building sources it contributes
weekly/2.25/%.o: ../weekly/2.25/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


