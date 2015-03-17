################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CF/CERC14/e/chk.cpp \
../CF/CERC14/e/sol.cpp \
../CF/CERC14/e/sol2.cpp 

OBJS += \
./CF/CERC14/e/chk.o \
./CF/CERC14/e/sol.o \
./CF/CERC14/e/sol2.o 

CPP_DEPS += \
./CF/CERC14/e/chk.d \
./CF/CERC14/e/sol.d \
./CF/CERC14/e/sol2.d 


# Each subdirectory must supply rules for building sources it contributes
CF/CERC14/e/%.o: ../CF/CERC14/e/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


