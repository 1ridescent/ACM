################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../annual/FBHC15/A.cpp \
../annual/FBHC15/B.cpp \
../annual/FBHC15/C.cpp 

OBJS += \
./annual/FBHC15/A.o \
./annual/FBHC15/B.o \
./annual/FBHC15/C.o 

CPP_DEPS += \
./annual/FBHC15/A.d \
./annual/FBHC15/B.d \
./annual/FBHC15/C.d 


# Each subdirectory must supply rules for building sources it contributes
annual/FBHC15/%.o: ../annual/FBHC15/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


