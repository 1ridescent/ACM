################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../weekly/9.10/A.cpp \
../weekly/9.10/B.cpp \
../weekly/9.10/C.cpp \
../weekly/9.10/D.cpp \
../weekly/9.10/E.cpp \
../weekly/9.10/F.cpp \
../weekly/9.10/G.cpp \
../weekly/9.10/H.cpp \
../weekly/9.10/I.cpp 

OBJS += \
./weekly/9.10/A.o \
./weekly/9.10/B.o \
./weekly/9.10/C.o \
./weekly/9.10/D.o \
./weekly/9.10/E.o \
./weekly/9.10/F.o \
./weekly/9.10/G.o \
./weekly/9.10/H.o \
./weekly/9.10/I.o 

CPP_DEPS += \
./weekly/9.10/A.d \
./weekly/9.10/B.d \
./weekly/9.10/C.d \
./weekly/9.10/D.d \
./weekly/9.10/E.d \
./weekly/9.10/F.d \
./weekly/9.10/G.d \
./weekly/9.10/H.d \
./weekly/9.10/I.d 


# Each subdirectory must supply rules for building sources it contributes
weekly/9.10/%.o: ../weekly/9.10/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


