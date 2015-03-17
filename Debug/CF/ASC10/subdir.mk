################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CF/ASC10/A.cpp \
../CF/ASC10/C.cpp \
../CF/ASC10/C2.cpp \
../CF/ASC10/D.cpp \
../CF/ASC10/E.cpp \
../CF/ASC10/F.cpp \
../CF/ASC10/G.cpp \
../CF/ASC10/I.cpp \
../CF/ASC10/J.cpp \
../CF/ASC10/K.cpp 

OBJS += \
./CF/ASC10/A.o \
./CF/ASC10/C.o \
./CF/ASC10/C2.o \
./CF/ASC10/D.o \
./CF/ASC10/E.o \
./CF/ASC10/F.o \
./CF/ASC10/G.o \
./CF/ASC10/I.o \
./CF/ASC10/J.o \
./CF/ASC10/K.o 

CPP_DEPS += \
./CF/ASC10/A.d \
./CF/ASC10/C.d \
./CF/ASC10/C2.d \
./CF/ASC10/D.d \
./CF/ASC10/E.d \
./CF/ASC10/F.d \
./CF/ASC10/G.d \
./CF/ASC10/I.d \
./CF/ASC10/J.d \
./CF/ASC10/K.d 


# Each subdirectory must supply rules for building sources it contributes
CF/ASC10/%.o: ../CF/ASC10/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


