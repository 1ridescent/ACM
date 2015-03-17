################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../weekly/10.1/D.cpp \
../weekly/10.1/H.cpp \
../weekly/10.1/I.cpp 

OBJS += \
./weekly/10.1/D.o \
./weekly/10.1/H.o \
./weekly/10.1/I.o 

CPP_DEPS += \
./weekly/10.1/D.d \
./weekly/10.1/H.d \
./weekly/10.1/I.d 


# Each subdirectory must supply rules for building sources it contributes
weekly/10.1/%.o: ../weekly/10.1/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


