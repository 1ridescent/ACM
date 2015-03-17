################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../weekly/9.3/A.cpp \
../weekly/9.3/B.cpp \
../weekly/9.3/C.cpp \
../weekly/9.3/C2.cpp \
../weekly/9.3/D.cpp \
../weekly/9.3/E.cpp \
../weekly/9.3/F.cpp \
../weekly/9.3/G.cpp \
../weekly/9.3/H.cpp 

OBJS += \
./weekly/9.3/A.o \
./weekly/9.3/B.o \
./weekly/9.3/C.o \
./weekly/9.3/C2.o \
./weekly/9.3/D.o \
./weekly/9.3/E.o \
./weekly/9.3/F.o \
./weekly/9.3/G.o \
./weekly/9.3/H.o 

CPP_DEPS += \
./weekly/9.3/A.d \
./weekly/9.3/B.d \
./weekly/9.3/C.d \
./weekly/9.3/C2.d \
./weekly/9.3/D.d \
./weekly/9.3/E.d \
./weekly/9.3/F.d \
./weekly/9.3/G.d \
./weekly/9.3/H.d 


# Each subdirectory must supply rules for building sources it contributes
weekly/9.3/%.o: ../weekly/9.3/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


