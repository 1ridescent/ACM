################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../annual/CJ14/A.cpp \
../annual/CJ14/B.cpp \
../annual/CJ14/B2.cpp \
../annual/CJ14/C.cpp 

OBJS += \
./annual/CJ14/A.o \
./annual/CJ14/B.o \
./annual/CJ14/B2.o \
./annual/CJ14/C.o 

CPP_DEPS += \
./annual/CJ14/A.d \
./annual/CJ14/B.d \
./annual/CJ14/B2.d \
./annual/CJ14/C.d 


# Each subdirectory must supply rules for building sources it contributes
annual/CJ14/%.o: ../annual/CJ14/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


