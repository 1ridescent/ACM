################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CF/100570/A.cpp \
../CF/100570/B.cpp \
../CF/100570/C.cpp \
../CF/100570/D.cpp \
../CF/100570/E.cpp \
../CF/100570/F.cpp 

OBJS += \
./CF/100570/A.o \
./CF/100570/B.o \
./CF/100570/C.o \
./CF/100570/D.o \
./CF/100570/E.o \
./CF/100570/F.o 

CPP_DEPS += \
./CF/100570/A.d \
./CF/100570/B.d \
./CF/100570/C.d \
./CF/100570/D.d \
./CF/100570/E.d \
./CF/100570/F.d 


# Each subdirectory must supply rules for building sources it contributes
CF/100570/%.o: ../CF/100570/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


