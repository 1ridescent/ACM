################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CF/CERC14/A.cpp \
../CF/CERC14/E.cpp \
../CF/CERC14/E2.cpp \
../CF/CERC14/H.cpp \
../CF/CERC14/J.cpp \
../CF/CERC14/K.cpp \
../CF/CERC14/L.cpp 

OBJS += \
./CF/CERC14/A.o \
./CF/CERC14/E.o \
./CF/CERC14/E2.o \
./CF/CERC14/H.o \
./CF/CERC14/J.o \
./CF/CERC14/K.o \
./CF/CERC14/L.o 

CPP_DEPS += \
./CF/CERC14/A.d \
./CF/CERC14/E.d \
./CF/CERC14/E2.d \
./CF/CERC14/H.d \
./CF/CERC14/J.d \
./CF/CERC14/K.d \
./CF/CERC14/L.d 


# Each subdirectory must supply rules for building sources it contributes
CF/CERC14/%.o: ../CF/CERC14/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


