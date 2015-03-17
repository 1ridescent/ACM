################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CF/504/A.cpp \
../CF/504/B.cpp \
../CF/504/C.cpp 

OBJS += \
./CF/504/A.o \
./CF/504/B.o \
./CF/504/C.o 

CPP_DEPS += \
./CF/504/A.d \
./CF/504/B.d \
./CF/504/C.d 


# Each subdirectory must supply rules for building sources it contributes
CF/504/%.o: ../CF/504/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


