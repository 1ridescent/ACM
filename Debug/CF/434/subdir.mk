################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CF/434/A.cpp \
../CF/434/B.cpp \
../CF/434/C.cpp 

OBJS += \
./CF/434/A.o \
./CF/434/B.o \
./CF/434/C.o 

CPP_DEPS += \
./CF/434/A.d \
./CF/434/B.d \
./CF/434/C.d 


# Each subdirectory must supply rules for building sources it contributes
CF/434/%.o: ../CF/434/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


