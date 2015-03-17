################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CF/425/A.cpp \
../CF/425/B.cpp \
../CF/425/C.cpp \
../CF/425/D.cpp \
../CF/425/E.cpp 

OBJS += \
./CF/425/A.o \
./CF/425/B.o \
./CF/425/C.o \
./CF/425/D.o \
./CF/425/E.o 

CPP_DEPS += \
./CF/425/A.d \
./CF/425/B.d \
./CF/425/C.d \
./CF/425/D.d \
./CF/425/E.d 


# Each subdirectory must supply rules for building sources it contributes
CF/425/%.o: ../CF/425/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


