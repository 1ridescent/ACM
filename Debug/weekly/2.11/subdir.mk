################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../weekly/2.11/C.cpp \
../weekly/2.11/D.cpp \
../weekly/2.11/E.cpp 

OBJS += \
./weekly/2.11/C.o \
./weekly/2.11/D.o \
./weekly/2.11/E.o 

CPP_DEPS += \
./weekly/2.11/C.d \
./weekly/2.11/D.d \
./weekly/2.11/E.d 


# Each subdirectory must supply rules for building sources it contributes
weekly/2.11/%.o: ../weekly/2.11/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


