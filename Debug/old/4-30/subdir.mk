################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../old/4-30/A.cpp \
../old/4-30/B.cpp \
../old/4-30/C.cpp \
../old/4-30/E.cpp \
../old/4-30/F.cpp 

OBJS += \
./old/4-30/A.o \
./old/4-30/B.o \
./old/4-30/C.o \
./old/4-30/E.o \
./old/4-30/F.o 

CPP_DEPS += \
./old/4-30/A.d \
./old/4-30/B.d \
./old/4-30/C.d \
./old/4-30/E.d \
./old/4-30/F.d 


# Each subdirectory must supply rules for building sources it contributes
old/4-30/%.o: ../old/4-30/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


