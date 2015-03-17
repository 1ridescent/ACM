################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CF/464/A.cpp \
../CF/464/B.cpp \
../CF/464/C.cpp \
../CF/464/D.cpp 

OBJS += \
./CF/464/A.o \
./CF/464/B.o \
./CF/464/C.o \
./CF/464/D.o 

CPP_DEPS += \
./CF/464/A.d \
./CF/464/B.d \
./CF/464/C.d \
./CF/464/D.d 


# Each subdirectory must supply rules for building sources it contributes
CF/464/%.o: ../CF/464/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


