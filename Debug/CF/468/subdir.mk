################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CF/468/A.cpp \
../CF/468/B.cpp \
../CF/468/D.cpp 

OBJS += \
./CF/468/A.o \
./CF/468/B.o \
./CF/468/D.o 

CPP_DEPS += \
./CF/468/A.d \
./CF/468/B.d \
./CF/468/D.d 


# Each subdirectory must supply rules for building sources it contributes
CF/468/%.o: ../CF/468/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


