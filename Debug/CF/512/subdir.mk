################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CF/512/A.cpp \
../CF/512/B.cpp \
../CF/512/C.cpp \
../CF/512/D.cpp \
../CF/512/E.cpp \
../CF/512/wtf.cpp 

OBJS += \
./CF/512/A.o \
./CF/512/B.o \
./CF/512/C.o \
./CF/512/D.o \
./CF/512/E.o \
./CF/512/wtf.o 

CPP_DEPS += \
./CF/512/A.d \
./CF/512/B.d \
./CF/512/C.d \
./CF/512/D.d \
./CF/512/E.d \
./CF/512/wtf.d 


# Each subdirectory must supply rules for building sources it contributes
CF/512/%.o: ../CF/512/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


