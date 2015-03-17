################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CF/516/A.cpp \
../CF/516/B.cpp \
../CF/516/C.cpp \
../CF/516/D.cpp 

OBJS += \
./CF/516/A.o \
./CF/516/B.o \
./CF/516/C.o \
./CF/516/D.o 

CPP_DEPS += \
./CF/516/A.d \
./CF/516/B.d \
./CF/516/C.d \
./CF/516/D.d 


# Each subdirectory must supply rules for building sources it contributes
CF/516/%.o: ../CF/516/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


