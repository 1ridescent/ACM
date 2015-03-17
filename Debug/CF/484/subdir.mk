################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CF/484/A.cpp \
../CF/484/B.cpp \
../CF/484/C.cpp \
../CF/484/D.cpp \
../CF/484/E.cpp \
../CF/484/E2.cpp \
../CF/484/test.cpp 

OBJS += \
./CF/484/A.o \
./CF/484/B.o \
./CF/484/C.o \
./CF/484/D.o \
./CF/484/E.o \
./CF/484/E2.o \
./CF/484/test.o 

CPP_DEPS += \
./CF/484/A.d \
./CF/484/B.d \
./CF/484/C.d \
./CF/484/D.d \
./CF/484/E.d \
./CF/484/E2.d \
./CF/484/test.d 


# Each subdirectory must supply rules for building sources it contributes
CF/484/%.o: ../CF/484/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


