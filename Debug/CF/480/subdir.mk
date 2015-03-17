################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CF/480/A.cpp \
../CF/480/B.cpp \
../CF/480/C.cpp \
../CF/480/D.cpp 

OBJS += \
./CF/480/A.o \
./CF/480/B.o \
./CF/480/C.o \
./CF/480/D.o 

CPP_DEPS += \
./CF/480/A.d \
./CF/480/B.d \
./CF/480/C.d \
./CF/480/D.d 


# Each subdirectory must supply rules for building sources it contributes
CF/480/%.o: ../CF/480/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


