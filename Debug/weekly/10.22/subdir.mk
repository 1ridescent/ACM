################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../weekly/10.22/A.cpp \
../weekly/10.22/D.cpp \
../weekly/10.22/E.cpp \
../weekly/10.22/F.cpp \
../weekly/10.22/G.cpp \
../weekly/10.22/H.cpp \
../weekly/10.22/M.cpp 

OBJS += \
./weekly/10.22/A.o \
./weekly/10.22/D.o \
./weekly/10.22/E.o \
./weekly/10.22/F.o \
./weekly/10.22/G.o \
./weekly/10.22/H.o \
./weekly/10.22/M.o 

CPP_DEPS += \
./weekly/10.22/A.d \
./weekly/10.22/D.d \
./weekly/10.22/E.d \
./weekly/10.22/F.d \
./weekly/10.22/G.d \
./weekly/10.22/H.d \
./weekly/10.22/M.d 


# Each subdirectory must supply rules for building sources it contributes
weekly/10.22/%.o: ../weekly/10.22/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


