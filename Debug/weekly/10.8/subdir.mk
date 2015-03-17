################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../weekly/10.8/D.cpp \
../weekly/10.8/E.cpp \
../weekly/10.8/F.cpp \
../weekly/10.8/H.cpp 

OBJS += \
./weekly/10.8/D.o \
./weekly/10.8/E.o \
./weekly/10.8/F.o \
./weekly/10.8/H.o 

CPP_DEPS += \
./weekly/10.8/D.d \
./weekly/10.8/E.d \
./weekly/10.8/F.d \
./weekly/10.8/H.d 


# Each subdirectory must supply rules for building sources it contributes
weekly/10.8/%.o: ../weekly/10.8/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


