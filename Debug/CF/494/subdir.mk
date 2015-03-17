################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CF/494/A.cpp \
../CF/494/B.cpp \
../CF/494/C.cpp \
../CF/494/D.cpp 

OBJS += \
./CF/494/A.o \
./CF/494/B.o \
./CF/494/C.o \
./CF/494/D.o 

CPP_DEPS += \
./CF/494/A.d \
./CF/494/B.d \
./CF/494/C.d \
./CF/494/D.d 


# Each subdirectory must supply rules for building sources it contributes
CF/494/%.o: ../CF/494/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


