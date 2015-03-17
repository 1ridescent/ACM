################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CF/506/A.cpp \
../CF/506/B.cpp \
../CF/506/C.cpp \
../CF/506/D.cpp 

OBJS += \
./CF/506/A.o \
./CF/506/B.o \
./CF/506/C.o \
./CF/506/D.o 

CPP_DEPS += \
./CF/506/A.d \
./CF/506/B.d \
./CF/506/C.d \
./CF/506/D.d 


# Each subdirectory must supply rules for building sources it contributes
CF/506/%.o: ../CF/506/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


