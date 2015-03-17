################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CF/414/A.cpp \
../CF/414/B.cpp \
../CF/414/C.cpp \
../CF/414/D.cpp \
../CF/414/D2.cpp 

OBJS += \
./CF/414/A.o \
./CF/414/B.o \
./CF/414/C.o \
./CF/414/D.o \
./CF/414/D2.o 

CPP_DEPS += \
./CF/414/A.d \
./CF/414/B.d \
./CF/414/C.d \
./CF/414/D.d \
./CF/414/D2.d 


# Each subdirectory must supply rules for building sources it contributes
CF/414/%.o: ../CF/414/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


