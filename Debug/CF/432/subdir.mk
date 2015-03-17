################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CF/432/A.cpp \
../CF/432/B.cpp \
../CF/432/C.cpp \
../CF/432/D.cpp \
../CF/432/E.cpp 

OBJS += \
./CF/432/A.o \
./CF/432/B.o \
./CF/432/C.o \
./CF/432/D.o \
./CF/432/E.o 

CPP_DEPS += \
./CF/432/A.d \
./CF/432/B.d \
./CF/432/C.d \
./CF/432/D.d \
./CF/432/E.d 


# Each subdirectory must supply rules for building sources it contributes
CF/432/%.o: ../CF/432/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


