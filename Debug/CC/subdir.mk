################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CC/C1.cpp \
../CC/COUNTARI.cpp \
../CC/COUNTARI2.cpp \
../CC/FARASA.cpp \
../CC/GERALD07.cpp \
../CC/MARCHA3.cpp \
../CC/MARCHA6.cpp \
../CC/PRIMEDST.cpp \
../CC/test.cpp \
../CC/test2.cpp 

OBJS += \
./CC/C1.o \
./CC/COUNTARI.o \
./CC/COUNTARI2.o \
./CC/FARASA.o \
./CC/GERALD07.o \
./CC/MARCHA3.o \
./CC/MARCHA6.o \
./CC/PRIMEDST.o \
./CC/test.o \
./CC/test2.o 

CPP_DEPS += \
./CC/C1.d \
./CC/COUNTARI.d \
./CC/COUNTARI2.d \
./CC/FARASA.d \
./CC/GERALD07.d \
./CC/MARCHA3.d \
./CC/MARCHA6.d \
./CC/PRIMEDST.d \
./CC/test.d \
./CC/test2.d 


# Each subdirectory must supply rules for building sources it contributes
CC/%.o: ../CC/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


