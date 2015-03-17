################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CF/477/A.cpp \
../CF/477/B.cpp \
../CF/477/C.cpp \
../CF/477/D.cpp 

OBJS += \
./CF/477/A.o \
./CF/477/B.o \
./CF/477/C.o \
./CF/477/D.o 

CPP_DEPS += \
./CF/477/A.d \
./CF/477/B.d \
./CF/477/C.d \
./CF/477/D.d 


# Each subdirectory must supply rules for building sources it contributes
CF/477/%.o: ../CF/477/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


