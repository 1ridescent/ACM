################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../weekly/10.29/E.cpp \
../weekly/10.29/F.cpp \
../weekly/10.29/F2.cpp \
../weekly/10.29/H.cpp 

OBJS += \
./weekly/10.29/E.o \
./weekly/10.29/F.o \
./weekly/10.29/F2.o \
./weekly/10.29/H.o 

CPP_DEPS += \
./weekly/10.29/E.d \
./weekly/10.29/F.d \
./weekly/10.29/F2.d \
./weekly/10.29/H.d 


# Each subdirectory must supply rules for building sources it contributes
weekly/10.29/%.o: ../weekly/10.29/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


