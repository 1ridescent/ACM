################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CF/100162/B.cpp \
../CF/100162/E.cpp \
../CF/100162/G.cpp \
../CF/100162/J.cpp 

OBJS += \
./CF/100162/B.o \
./CF/100162/E.o \
./CF/100162/G.o \
./CF/100162/J.o 

CPP_DEPS += \
./CF/100162/B.d \
./CF/100162/E.d \
./CF/100162/G.d \
./CF/100162/J.d 


# Each subdirectory must supply rules for building sources it contributes
CF/100162/%.o: ../CF/100162/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


