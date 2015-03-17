################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../weekly/9.27/A.cpp \
../weekly/9.27/A2.cpp \
../weekly/9.27/B.cpp \
../weekly/9.27/C.cpp \
../weekly/9.27/D.cpp \
../weekly/9.27/E.cpp \
../weekly/9.27/G.cpp \
../weekly/9.27/J.cpp 

OBJS += \
./weekly/9.27/A.o \
./weekly/9.27/A2.o \
./weekly/9.27/B.o \
./weekly/9.27/C.o \
./weekly/9.27/D.o \
./weekly/9.27/E.o \
./weekly/9.27/G.o \
./weekly/9.27/J.o 

CPP_DEPS += \
./weekly/9.27/A.d \
./weekly/9.27/A2.d \
./weekly/9.27/B.d \
./weekly/9.27/C.d \
./weekly/9.27/D.d \
./weekly/9.27/E.d \
./weekly/9.27/G.d \
./weekly/9.27/J.d 


# Each subdirectory must supply rules for building sources it contributes
weekly/9.27/%.o: ../weekly/9.27/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


