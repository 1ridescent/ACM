################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../old/abovemed.cpp \
../old/baleshare.cpp \
../old/betterbettor.cpp \
../old/binsudoku.cpp \
../old/boxes.cpp \
../old/brokenmonitor.cpp \
../old/cardgame.cpp \
../old/cowphoto.cpp \
../old/cowphoto2.cpp \
../old/cowrun.cpp \
../old/cowspots.cpp \
../old/cycleperms.cpp \
../old/darkside.cpp \
../old/darkside0.cpp \
../old/digits.cpp \
../old/elephantmkt.cpp \
../old/elephantmkt2.cpp \
../old/escapefarm.cpp \
../old/fast_suffix_array.cpp \
../old/formula1.cpp \
../old/gamecombos.cpp \
../old/hackercity.cpp \
../old/haybales.cpp \
../old/haystack.cpp \
../old/hyperrect.cpp \
../old/liar.cpp \
../old/liar0.cpp \
../old/manacher.cpp \
../old/maxrandwalk.cpp \
../old/mittens.cpp \
../old/moosick.cpp \
../old/numpaths.cpp \
../old/numsets.cpp \
../old/pollution.cpp \
../old/roadblock.cpp \
../old/simplify.cpp \
../old/skicourse.cpp \
../old/skirating.cpp \
../old/splay_tree.cpp \
../old/sqrt.cpp \
../old/steeplechase.cpp \
../old/subway.cpp \
../old/suffix_array.cpp \
../old/suffix_array2.cpp \
../old/summerreading.cpp \
../old/test.cpp \
../old/topkelts.cpp \
../old/treasures.cpp \
../old/treequeries.cpp \
../old/treequeries2.cpp \
../old/umbrellas.cpp \
../old/vendingmachine.cpp \
../old/zeronine.cpp 

OBJS += \
./old/abovemed.o \
./old/baleshare.o \
./old/betterbettor.o \
./old/binsudoku.o \
./old/boxes.o \
./old/brokenmonitor.o \
./old/cardgame.o \
./old/cowphoto.o \
./old/cowphoto2.o \
./old/cowrun.o \
./old/cowspots.o \
./old/cycleperms.o \
./old/darkside.o \
./old/darkside0.o \
./old/digits.o \
./old/elephantmkt.o \
./old/elephantmkt2.o \
./old/escapefarm.o \
./old/fast_suffix_array.o \
./old/formula1.o \
./old/gamecombos.o \
./old/hackercity.o \
./old/haybales.o \
./old/haystack.o \
./old/hyperrect.o \
./old/liar.o \
./old/liar0.o \
./old/manacher.o \
./old/maxrandwalk.o \
./old/mittens.o \
./old/moosick.o \
./old/numpaths.o \
./old/numsets.o \
./old/pollution.o \
./old/roadblock.o \
./old/simplify.o \
./old/skicourse.o \
./old/skirating.o \
./old/splay_tree.o \
./old/sqrt.o \
./old/steeplechase.o \
./old/subway.o \
./old/suffix_array.o \
./old/suffix_array2.o \
./old/summerreading.o \
./old/test.o \
./old/topkelts.o \
./old/treasures.o \
./old/treequeries.o \
./old/treequeries2.o \
./old/umbrellas.o \
./old/vendingmachine.o \
./old/zeronine.o 

CPP_DEPS += \
./old/abovemed.d \
./old/baleshare.d \
./old/betterbettor.d \
./old/binsudoku.d \
./old/boxes.d \
./old/brokenmonitor.d \
./old/cardgame.d \
./old/cowphoto.d \
./old/cowphoto2.d \
./old/cowrun.d \
./old/cowspots.d \
./old/cycleperms.d \
./old/darkside.d \
./old/darkside0.d \
./old/digits.d \
./old/elephantmkt.d \
./old/elephantmkt2.d \
./old/escapefarm.d \
./old/fast_suffix_array.d \
./old/formula1.d \
./old/gamecombos.d \
./old/hackercity.d \
./old/haybales.d \
./old/haystack.d \
./old/hyperrect.d \
./old/liar.d \
./old/liar0.d \
./old/manacher.d \
./old/maxrandwalk.d \
./old/mittens.d \
./old/moosick.d \
./old/numpaths.d \
./old/numsets.d \
./old/pollution.d \
./old/roadblock.d \
./old/simplify.d \
./old/skicourse.d \
./old/skirating.d \
./old/splay_tree.d \
./old/sqrt.d \
./old/steeplechase.d \
./old/subway.d \
./old/suffix_array.d \
./old/suffix_array2.d \
./old/summerreading.d \
./old/test.d \
./old/topkelts.d \
./old/treasures.d \
./old/treequeries.d \
./old/treequeries2.d \
./old/umbrellas.d \
./old/vendingmachine.d \
./old/zeronine.d 


# Each subdirectory must supply rules for building sources it contributes
old/%.o: ../old/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


