################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../annual/CJ141A/A.cpp \
../annual/CJ141A/B.cpp \
../annual/CJ141A/C-input.cpp \
../annual/CJ141A/C-random-gen.cpp \
../annual/CJ141A/C-random.cpp \
../annual/CJ141A/C-random2.cpp \
../annual/CJ141A/C-test-gen.cpp \
../annual/CJ141A/C-test.cpp \
../annual/CJ141A/C-test2.cpp \
../annual/CJ141A/C.cpp 

OBJS += \
./annual/CJ141A/A.o \
./annual/CJ141A/B.o \
./annual/CJ141A/C-input.o \
./annual/CJ141A/C-random-gen.o \
./annual/CJ141A/C-random.o \
./annual/CJ141A/C-random2.o \
./annual/CJ141A/C-test-gen.o \
./annual/CJ141A/C-test.o \
./annual/CJ141A/C-test2.o \
./annual/CJ141A/C.o 

CPP_DEPS += \
./annual/CJ141A/A.d \
./annual/CJ141A/B.d \
./annual/CJ141A/C-input.d \
./annual/CJ141A/C-random-gen.d \
./annual/CJ141A/C-random.d \
./annual/CJ141A/C-random2.d \
./annual/CJ141A/C-test-gen.d \
./annual/CJ141A/C-test.d \
./annual/CJ141A/C-test2.d \
./annual/CJ141A/C.d 


# Each subdirectory must supply rules for building sources it contributes
annual/CJ141A/%.o: ../annual/CJ141A/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


