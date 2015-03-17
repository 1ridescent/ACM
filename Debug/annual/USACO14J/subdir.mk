################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../annual/USACO14J/cowrect.cpp \
../annual/USACO14J/grass.cpp \
../annual/USACO14J/movie.cpp 

OBJS += \
./annual/USACO14J/cowrect.o \
./annual/USACO14J/grass.o \
./annual/USACO14J/movie.o 

CPP_DEPS += \
./annual/USACO14J/cowrect.d \
./annual/USACO14J/grass.d \
./annual/USACO14J/movie.d 


# Each subdirectory must supply rules for building sources it contributes
annual/USACO14J/%.o: ../annual/USACO14J/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


