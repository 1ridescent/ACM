################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CF/453/A.cpp \
../CF/453/B.cpp \
../CF/453/C.cpp \
../CF/453/D.cpp \
../CF/453/D2.cpp \
../CF/453/E.cpp 

OBJS += \
./CF/453/A.o \
./CF/453/B.o \
./CF/453/C.o \
./CF/453/D.o \
./CF/453/D2.o \
./CF/453/E.o 

CPP_DEPS += \
./CF/453/A.d \
./CF/453/B.d \
./CF/453/C.d \
./CF/453/D.d \
./CF/453/D2.d \
./CF/453/E.d 


# Each subdirectory must supply rules for building sources it contributes
CF/453/%.o: ../CF/453/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


