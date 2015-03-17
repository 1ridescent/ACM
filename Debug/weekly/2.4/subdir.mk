################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../weekly/2.4/A.cpp \
../weekly/2.4/B.cpp \
../weekly/2.4/C.cpp \
../weekly/2.4/D.cpp \
../weekly/2.4/E.cpp 

OBJS += \
./weekly/2.4/A.o \
./weekly/2.4/B.o \
./weekly/2.4/C.o \
./weekly/2.4/D.o \
./weekly/2.4/E.o 

CPP_DEPS += \
./weekly/2.4/A.d \
./weekly/2.4/B.d \
./weekly/2.4/C.d \
./weekly/2.4/D.d \
./weekly/2.4/E.d 


# Each subdirectory must supply rules for building sources it contributes
weekly/2.4/%.o: ../weekly/2.4/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


