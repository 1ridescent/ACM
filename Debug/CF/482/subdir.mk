################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CF/482/A.cpp \
../CF/482/B.cpp \
../CF/482/C.cpp \
../CF/482/D.cpp 

OBJS += \
./CF/482/A.o \
./CF/482/B.o \
./CF/482/C.o \
./CF/482/D.o 

CPP_DEPS += \
./CF/482/A.d \
./CF/482/B.d \
./CF/482/C.d \
./CF/482/D.d 


# Each subdirectory must supply rules for building sources it contributes
CF/482/%.o: ../CF/482/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


