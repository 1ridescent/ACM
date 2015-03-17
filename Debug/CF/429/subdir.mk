################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CF/429/A.cpp \
../CF/429/B.cpp \
../CF/429/C.cpp \
../CF/429/D.cpp \
../CF/429/D2.cpp \
../CF/429/D3.cpp \
../CF/429/D4.cpp \
../CF/429/D5.cpp \
../CF/429/D6.cpp \
../CF/429/E.cpp \
../CF/429/test.cpp \
../CF/429/test2.cpp 

OBJS += \
./CF/429/A.o \
./CF/429/B.o \
./CF/429/C.o \
./CF/429/D.o \
./CF/429/D2.o \
./CF/429/D3.o \
./CF/429/D4.o \
./CF/429/D5.o \
./CF/429/D6.o \
./CF/429/E.o \
./CF/429/test.o \
./CF/429/test2.o 

CPP_DEPS += \
./CF/429/A.d \
./CF/429/B.d \
./CF/429/C.d \
./CF/429/D.d \
./CF/429/D2.d \
./CF/429/D3.d \
./CF/429/D4.d \
./CF/429/D5.d \
./CF/429/D6.d \
./CF/429/E.d \
./CF/429/test.d \
./CF/429/test2.d 


# Each subdirectory must supply rules for building sources it contributes
CF/429/%.o: ../CF/429/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


