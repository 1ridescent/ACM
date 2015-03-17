################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CF/513/A.cpp \
../CF/513/B.cpp \
../CF/513/C.cpp \
../CF/513/D.cpp \
../CF/513/E.cpp 

OBJS += \
./CF/513/A.o \
./CF/513/B.o \
./CF/513/C.o \
./CF/513/D.o \
./CF/513/E.o 

CPP_DEPS += \
./CF/513/A.d \
./CF/513/B.d \
./CF/513/C.d \
./CF/513/D.d \
./CF/513/E.d 


# Each subdirectory must supply rules for building sources it contributes
CF/513/%.o: ../CF/513/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


