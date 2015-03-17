################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CF/458/A.cpp \
../CF/458/B.cpp \
../CF/458/C.cpp \
../CF/458/D.cpp 

OBJS += \
./CF/458/A.o \
./CF/458/B.o \
./CF/458/C.o \
./CF/458/D.o 

CPP_DEPS += \
./CF/458/A.d \
./CF/458/B.d \
./CF/458/C.d \
./CF/458/D.d 


# Each subdirectory must supply rules for building sources it contributes
CF/458/%.o: ../CF/458/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


