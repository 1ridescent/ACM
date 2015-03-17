################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CF/500/A.cpp \
../CF/500/B.cpp \
../CF/500/C.cpp \
../CF/500/D.cpp \
../CF/500/E.cpp \
../CF/500/F.cpp \
../CF/500/test.cpp \
../CF/500/test2.cpp 

OBJS += \
./CF/500/A.o \
./CF/500/B.o \
./CF/500/C.o \
./CF/500/D.o \
./CF/500/E.o \
./CF/500/F.o \
./CF/500/test.o \
./CF/500/test2.o 

CPP_DEPS += \
./CF/500/A.d \
./CF/500/B.d \
./CF/500/C.d \
./CF/500/D.d \
./CF/500/E.d \
./CF/500/F.d \
./CF/500/test.d \
./CF/500/test2.d 


# Each subdirectory must supply rules for building sources it contributes
CF/500/%.o: ../CF/500/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


