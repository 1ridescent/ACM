################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../weekly/giants/C.cpp \
../weekly/giants/F.cpp \
../weekly/giants/J.cpp \
../weekly/giants/K.cpp 

OBJS += \
./weekly/giants/C.o \
./weekly/giants/F.o \
./weekly/giants/J.o \
./weekly/giants/K.o 

CPP_DEPS += \
./weekly/giants/C.d \
./weekly/giants/F.d \
./weekly/giants/J.d \
./weekly/giants/K.d 


# Each subdirectory must supply rules for building sources it contributes
weekly/giants/%.o: ../weekly/giants/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


