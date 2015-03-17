################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../SGU/128.cpp \
../SGU/137.cpp \
../SGU/138.cpp \
../SGU/140.cpp \
../SGU/141.cpp \
../SGU/145.cpp \
../SGU/153.cpp \
../SGU/156.cpp \
../SGU/158.cpp \
../SGU/159.cpp \
../SGU/164.cpp \
../SGU/165.cpp \
../SGU/167.cpp \
../SGU/171.cpp \
../SGU/176.cpp \
../SGU/200.cpp 

OBJS += \
./SGU/128.o \
./SGU/137.o \
./SGU/138.o \
./SGU/140.o \
./SGU/141.o \
./SGU/145.o \
./SGU/153.o \
./SGU/156.o \
./SGU/158.o \
./SGU/159.o \
./SGU/164.o \
./SGU/165.o \
./SGU/167.o \
./SGU/171.o \
./SGU/176.o \
./SGU/200.o 

CPP_DEPS += \
./SGU/128.d \
./SGU/137.d \
./SGU/138.d \
./SGU/140.d \
./SGU/141.d \
./SGU/145.d \
./SGU/153.d \
./SGU/156.d \
./SGU/158.d \
./SGU/159.d \
./SGU/164.d \
./SGU/165.d \
./SGU/167.d \
./SGU/171.d \
./SGU/176.d \
./SGU/200.d 


# Each subdirectory must supply rules for building sources it contributes
SGU/%.o: ../SGU/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


