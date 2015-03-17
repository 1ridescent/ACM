################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CF/461/A.cpp \
../CF/461/B.cpp \
../CF/461/C.cpp \
../CF/461/D.cpp \
../CF/461/E.cpp 

OBJS += \
./CF/461/A.o \
./CF/461/B.o \
./CF/461/C.o \
./CF/461/D.o \
./CF/461/E.o 

CPP_DEPS += \
./CF/461/A.d \
./CF/461/B.d \
./CF/461/C.d \
./CF/461/D.d \
./CF/461/E.d 


# Each subdirectory must supply rules for building sources it contributes
CF/461/%.o: ../CF/461/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


