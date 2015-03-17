################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CF/521/A.cpp \
../CF/521/B.cpp \
../CF/521/C.cpp \
../CF/521/D.cpp \
../CF/521/E.cpp 

OBJS += \
./CF/521/A.o \
./CF/521/B.o \
./CF/521/C.o \
./CF/521/D.o \
./CF/521/E.o 

CPP_DEPS += \
./CF/521/A.d \
./CF/521/B.d \
./CF/521/C.d \
./CF/521/D.d \
./CF/521/E.d 


# Each subdirectory must supply rules for building sources it contributes
CF/521/%.o: ../CF/521/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


