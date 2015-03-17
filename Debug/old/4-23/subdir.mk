################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../old/4-23/A.cpp \
../old/4-23/B.cpp \
../old/4-23/C.cpp \
../old/4-23/C2.cpp \
../old/4-23/D.cpp 

OBJS += \
./old/4-23/A.o \
./old/4-23/B.o \
./old/4-23/C.o \
./old/4-23/C2.o \
./old/4-23/D.o 

CPP_DEPS += \
./old/4-23/A.d \
./old/4-23/B.d \
./old/4-23/C.d \
./old/4-23/C2.d \
./old/4-23/D.d 


# Each subdirectory must supply rules for building sources it contributes
old/4-23/%.o: ../old/4-23/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


