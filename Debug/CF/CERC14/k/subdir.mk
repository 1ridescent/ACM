################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CF/CERC14/k/sol.cpp \
../CF/CERC14/k/sol2.cpp \
../CF/CERC14/k/sol3.cpp 

OBJS += \
./CF/CERC14/k/sol.o \
./CF/CERC14/k/sol2.o \
./CF/CERC14/k/sol3.o 

CPP_DEPS += \
./CF/CERC14/k/sol.d \
./CF/CERC14/k/sol2.d \
./CF/CERC14/k/sol3.d 


# Each subdirectory must supply rules for building sources it contributes
CF/CERC14/k/%.o: ../CF/CERC14/k/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


