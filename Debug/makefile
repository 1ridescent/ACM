################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include weekly/giants/subdir.mk
-include weekly/9.3/subdir.mk
-include weekly/9.27/subdir.mk
-include weekly/9.17/subdir.mk
-include weekly/9.10/subdir.mk
-include weekly/3.4/subdir.mk
-include weekly/2.4/subdir.mk
-include weekly/2.25/subdir.mk
-include weekly/2.18/subdir.mk
-include weekly/2.11/subdir.mk
-include weekly/12.3/subdir.mk
-include weekly/11.5/subdir.mk
-include weekly/10.8/subdir.mk
-include weekly/10.29/subdir.mk
-include weekly/10.22/subdir.mk
-include weekly/10.1/subdir.mk
-include weekly/1.28/subdir.mk
-include weekly/1.21/subdir.mk
-include old/4-30/subdir.mk
-include old/4-23/subdir.mk
-include old/subdir.mk
-include annual/USACO14J/subdir.mk
-include annual/USACO14F/subdir.mk
-include annual/FBHC153/subdir.mk
-include annual/FBHC151/subdir.mk
-include annual/FBHC15/subdir.mk
-include annual/CJ141A/subdir.mk
-include annual/CJ14/subdir.mk
-include SGU/subdir.mk
-include CF/moscow14/subdir.mk
-include CF/NEERC14/subdir.mk
-include CF/CERC14/k/subdir.mk
-include CF/CERC14/e/subdir.mk
-include CF/CERC14/subdir.mk
-include CF/ASC10/subdir.mk
-include CF/521/subdir.mk
-include CF/518/subdir.mk
-include CF/516/subdir.mk
-include CF/514/subdir.mk
-include CF/513/subdir.mk
-include CF/512/subdir.mk
-include CF/509/subdir.mk
-include CF/506/subdir.mk
-include CF/504/subdir.mk
-include CF/500/subdir.mk
-include CF/498/subdir.mk
-include CF/494/subdir.mk
-include CF/491/subdir.mk
-include CF/490/subdir.mk
-include CF/489/subdir.mk
-include CF/486/subdir.mk
-include CF/484/subdir.mk
-include CF/482/subdir.mk
-include CF/480/subdir.mk
-include CF/477/subdir.mk
-include CF/468/subdir.mk
-include CF/464/subdir.mk
-include CF/461/subdir.mk
-include CF/458/subdir.mk
-include CF/453/subdir.mk
-include CF/449/subdir.mk
-include CF/438/subdir.mk
-include CF/434/subdir.mk
-include CF/432/subdir.mk
-include CF/431/subdir.mk
-include CF/429/subdir.mk
-include CF/425/subdir.mk
-include CF/424/subdir.mk
-include CF/414/subdir.mk
-include CF/413/subdir.mk
-include CF/412/subdir.mk
-include CF/407/subdir.mk
-include CF/100625/subdir.mk
-include CF/100589/subdir.mk
-include CF/100570/subdir.mk
-include CF/100541/subdir.mk
-include CF/100499/subdir.mk
-include CF/100162/subdir.mk
-include CC/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: ACM

# Tool invocations
ACM: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross G++ Linker'
	g++  -o "ACM" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(EXECUTABLES)$(OBJS)$(C_UPPER_DEPS)$(CXX_DEPS)$(C_DEPS)$(CPP_DEPS) ACM
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
