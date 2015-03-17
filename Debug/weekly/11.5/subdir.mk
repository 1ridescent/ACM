################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../weekly/11.5/E.cpp \
../weekly/11.5/F.cpp \
../weekly/11.5/I.cpp 

OBJS += \
./weekly/11.5/E.o \
./weekly/11.5/F.o \
./weekly/11.5/I.o 

CPP_DEPS += \
./weekly/11.5/E.d \
./weekly/11.5/F.d \
./weekly/11.5/I.d 


# Each subdirectory must supply rules for building sources it contributes
weekly/11.5/%.o: ../weekly/11.5/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


