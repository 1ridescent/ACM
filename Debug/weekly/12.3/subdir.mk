################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../weekly/12.3/A.cpp \
../weekly/12.3/C.cpp \
../weekly/12.3/D.cpp \
../weekly/12.3/E.cpp \
../weekly/12.3/F.cpp \
../weekly/12.3/G.cpp \
../weekly/12.3/G2.cpp \
../weekly/12.3/I.cpp 

OBJS += \
./weekly/12.3/A.o \
./weekly/12.3/C.o \
./weekly/12.3/D.o \
./weekly/12.3/E.o \
./weekly/12.3/F.o \
./weekly/12.3/G.o \
./weekly/12.3/G2.o \
./weekly/12.3/I.o 

CPP_DEPS += \
./weekly/12.3/A.d \
./weekly/12.3/C.d \
./weekly/12.3/D.d \
./weekly/12.3/E.d \
./weekly/12.3/F.d \
./weekly/12.3/G.d \
./weekly/12.3/G2.d \
./weekly/12.3/I.d 


# Each subdirectory must supply rules for building sources it contributes
weekly/12.3/%.o: ../weekly/12.3/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


