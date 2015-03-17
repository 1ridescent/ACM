################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CF/518/D.cpp \
../CF/518/E.cpp \
../CF/518/F.cpp 

OBJS += \
./CF/518/D.o \
./CF/518/E.o \
./CF/518/F.o 

CPP_DEPS += \
./CF/518/D.d \
./CF/518/E.d \
./CF/518/F.d 


# Each subdirectory must supply rules for building sources it contributes
CF/518/%.o: ../CF/518/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


