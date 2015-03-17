################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CF/498/A.cpp \
../CF/498/B.cpp \
../CF/498/C.cpp \
../CF/498/D.cpp 

OBJS += \
./CF/498/A.o \
./CF/498/B.o \
./CF/498/C.o \
./CF/498/D.o 

CPP_DEPS += \
./CF/498/A.d \
./CF/498/B.d \
./CF/498/C.d \
./CF/498/D.d 


# Each subdirectory must supply rules for building sources it contributes
CF/498/%.o: ../CF/498/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


