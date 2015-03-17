################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../weekly/9.17/A.cpp \
../weekly/9.17/B.cpp \
../weekly/9.17/C.cpp \
../weekly/9.17/C2.cpp \
../weekly/9.17/D.cpp \
../weekly/9.17/E.cpp \
../weekly/9.17/F.cpp \
../weekly/9.17/F2.cpp \
../weekly/9.17/G.cpp \
../weekly/9.17/H.cpp \
../weekly/9.17/I.cpp \
../weekly/9.17/cowfamily.cpp \
../weekly/9.17/test.cpp 

OBJS += \
./weekly/9.17/A.o \
./weekly/9.17/B.o \
./weekly/9.17/C.o \
./weekly/9.17/C2.o \
./weekly/9.17/D.o \
./weekly/9.17/E.o \
./weekly/9.17/F.o \
./weekly/9.17/F2.o \
./weekly/9.17/G.o \
./weekly/9.17/H.o \
./weekly/9.17/I.o \
./weekly/9.17/cowfamily.o \
./weekly/9.17/test.o 

CPP_DEPS += \
./weekly/9.17/A.d \
./weekly/9.17/B.d \
./weekly/9.17/C.d \
./weekly/9.17/C2.d \
./weekly/9.17/D.d \
./weekly/9.17/E.d \
./weekly/9.17/F.d \
./weekly/9.17/F2.d \
./weekly/9.17/G.d \
./weekly/9.17/H.d \
./weekly/9.17/I.d \
./weekly/9.17/cowfamily.d \
./weekly/9.17/test.d 


# Each subdirectory must supply rules for building sources it contributes
weekly/9.17/%.o: ../weekly/9.17/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


