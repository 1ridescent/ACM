################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CF/NEERC14/B.cpp \
../CF/NEERC14/H.cpp \
../CF/NEERC14/I.cpp \
../CF/NEERC14/K.cpp 

OBJS += \
./CF/NEERC14/B.o \
./CF/NEERC14/H.o \
./CF/NEERC14/I.o \
./CF/NEERC14/K.o 

CPP_DEPS += \
./CF/NEERC14/B.d \
./CF/NEERC14/H.d \
./CF/NEERC14/I.d \
./CF/NEERC14/K.d 


# Each subdirectory must supply rules for building sources it contributes
CF/NEERC14/%.o: ../CF/NEERC14/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


