################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CF/407/A.cpp \
../CF/407/B.cpp \
../CF/407/C.cpp \
../CF/407/D.cpp \
../CF/407/E.cpp 

OBJS += \
./CF/407/A.o \
./CF/407/B.o \
./CF/407/C.o \
./CF/407/D.o \
./CF/407/E.o 

CPP_DEPS += \
./CF/407/A.d \
./CF/407/B.d \
./CF/407/C.d \
./CF/407/D.d \
./CF/407/E.d 


# Each subdirectory must supply rules for building sources it contributes
CF/407/%.o: ../CF/407/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


