################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CF/moscow14/C.cpp \
../CF/moscow14/F.cpp \
../CF/moscow14/I.cpp \
../CF/moscow14/I0.cpp \
../CF/moscow14/J.cpp \
../CF/moscow14/test.cpp 

OBJS += \
./CF/moscow14/C.o \
./CF/moscow14/F.o \
./CF/moscow14/I.o \
./CF/moscow14/I0.o \
./CF/moscow14/J.o \
./CF/moscow14/test.o 

CPP_DEPS += \
./CF/moscow14/C.d \
./CF/moscow14/F.d \
./CF/moscow14/I.d \
./CF/moscow14/I0.d \
./CF/moscow14/J.d \
./CF/moscow14/test.d 


# Each subdirectory must supply rules for building sources it contributes
CF/moscow14/%.o: ../CF/moscow14/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


