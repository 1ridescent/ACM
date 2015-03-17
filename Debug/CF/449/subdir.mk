################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CF/449/A.cpp \
../CF/449/A2.cpp \
../CF/449/B.cpp \
../CF/449/C.cpp \
../CF/449/D.cpp \
../CF/449/E.cpp 

OBJS += \
./CF/449/A.o \
./CF/449/A2.o \
./CF/449/B.o \
./CF/449/C.o \
./CF/449/D.o \
./CF/449/E.o 

CPP_DEPS += \
./CF/449/A.d \
./CF/449/A2.d \
./CF/449/B.d \
./CF/449/C.d \
./CF/449/D.d \
./CF/449/E.d 


# Each subdirectory must supply rules for building sources it contributes
CF/449/%.o: ../CF/449/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


