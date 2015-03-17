################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CF/438/A.cpp \
../CF/438/B.cpp \
../CF/438/B2.cpp \
../CF/438/C.cpp 

OBJS += \
./CF/438/A.o \
./CF/438/B.o \
./CF/438/B2.o \
./CF/438/C.o 

CPP_DEPS += \
./CF/438/A.d \
./CF/438/B.d \
./CF/438/B2.d \
./CF/438/C.d 


# Each subdirectory must supply rules for building sources it contributes
CF/438/%.o: ../CF/438/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


