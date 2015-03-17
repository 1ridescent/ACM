################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../annual/FBHC153/A.cpp \
../annual/FBHC153/B.cpp \
../annual/FBHC153/C.cpp 

OBJS += \
./annual/FBHC153/A.o \
./annual/FBHC153/B.o \
./annual/FBHC153/C.o 

CPP_DEPS += \
./annual/FBHC153/A.d \
./annual/FBHC153/B.d \
./annual/FBHC153/C.d 


# Each subdirectory must supply rules for building sources it contributes
annual/FBHC153/%.o: ../annual/FBHC153/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


