################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS :=  \
../ECU_Layer/LED \
../MCAL_Layer \
../MCAL_Layer/GPIO \
../ECU_Layer \
../MCAL_Layer/Interrupt \
../MCAL_Layer/ADC \
../MCAL_Layer/I2C \
../MCAL_Layer/Timer1 \
../MCAL_Layer/Timer0 \
../Services_Layer \
../Services_Layer/Lighting_ECU \
../Services_Layer/LDR


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../application.c \
../ECU_Layer/LED/ecu_led.c \
../MCAL_Layer/ADC/hal_adc.c \
../MCAL_Layer/device_config.c \
../MCAL_Layer/GPIO/hal_gpio.c \
../MCAL_Layer/I2C/hal_i2c.c \
../MCAL_Layer/Interrupt/mcal_internal_interrupt.c \
../MCAL_Layer/Interrupt/mcal_external_interrupt.c \
../MCAL_Layer/Interrupt/mcal_interrupt_manger.c \
../MCAL_Layer/Timer0/hal_timer0.c \
../MCAL_Layer/Timer1/hal_timer1.c \
../Services_Layer/LDR/LDR_interface.c \
../Services_Layer/Lighting_ECU/lighting_interface.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
application.o \
ECU_Layer/LED/ecu_led.o \
MCAL_Layer/ADC/hal_adc.o \
MCAL_Layer/device_config.o \
MCAL_Layer/GPIO/hal_gpio.o \
MCAL_Layer/I2C/hal_i2c.o \
MCAL_Layer/Interrupt/mcal_internal_interrupt.o \
MCAL_Layer/Interrupt/mcal_external_interrupt.o \
MCAL_Layer/Interrupt/mcal_interrupt_manger.o \
MCAL_Layer/Timer0/hal_timer0.o \
MCAL_Layer/Timer1/hal_timer1.o \
Services_Layer/LDR/LDR_interface.o \
Services_Layer/Lighting_ECU/lighting_interface.o

OBJS_AS_ARGS +=  \
application.o \
ECU_Layer/LED/ecu_led.o \
MCAL_Layer/ADC/hal_adc.o \
MCAL_Layer/device_config.o \
MCAL_Layer/GPIO/hal_gpio.o \
MCAL_Layer/I2C/hal_i2c.o \
MCAL_Layer/Interrupt/mcal_internal_interrupt.o \
MCAL_Layer/Interrupt/mcal_external_interrupt.o \
MCAL_Layer/Interrupt/mcal_interrupt_manger.o \
MCAL_Layer/Timer0/hal_timer0.o \
MCAL_Layer/Timer1/hal_timer1.o \
Services_Layer/LDR/LDR_interface.o \
Services_Layer/Lighting_ECU/lighting_interface.o

C_DEPS +=  \
application.d \
ECU_Layer/LED/ecu_led.d \
MCAL_Layer/ADC/hal_adc.d \
MCAL_Layer/device_config.d \
MCAL_Layer/GPIO/hal_gpio.d \
MCAL_Layer/I2C/hal_i2c.d \
MCAL_Layer/Interrupt/mcal_internal_interrupt.d \
MCAL_Layer/Interrupt/mcal_external_interrupt.d \
MCAL_Layer/Interrupt/mcal_interrupt_manger.d \
MCAL_Layer/Timer0/hal_timer0.d \
MCAL_Layer/Timer1/hal_timer1.d \
Services_Layer/LDR/LDR_interface.d \
Services_Layer/Lighting_ECU/lighting_interface.d

C_DEPS_AS_ARGS +=  \
application.d \
ECU_Layer/LED/ecu_led.d \
MCAL_Layer/ADC/hal_adc.d \
MCAL_Layer/device_config.d \
MCAL_Layer/GPIO/hal_gpio.d \
MCAL_Layer/I2C/hal_i2c.d \
MCAL_Layer/Interrupt/mcal_internal_interrupt.d \
MCAL_Layer/Interrupt/mcal_external_interrupt.d \
MCAL_Layer/Interrupt/mcal_interrupt_manger.d \
MCAL_Layer/Timer0/hal_timer0.d \
MCAL_Layer/Timer1/hal_timer1.d \
Services_Layer/LDR/LDR_interface.d \
Services_Layer/Lighting_ECU/lighting_interface.d

OUTPUT_FILE_PATH +=Lighting.elf

OUTPUT_FILE_PATH_AS_ARGS +=Lighting.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler
./application.o: .././application.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.7.374\include" -I"../MCAL_Layer" -I"../MCAL_Layer/ADC" -I"../MCAL_Layer/GPIO" -I"../MCAL_Layer/Interrupt" -I"../MCAL_Layer/I2C" -I"../MCAL_Layer/SPI" -I"../ECU_Layer/LED" -I"../MCAL_Layer/Timer0" -I"../MCAL_Layer/Timer1" -I"../Services_Layer" -I"../Services_Layer/Lighting_ECU" -I"../Services_Layer/LDR"  -Og -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega32a -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.7.374\gcc\dev\atmega32a" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

ECU_Layer/LED/ecu_led.o: ../ECU_Layer/LED/ecu_led.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.7.374\include" -I"../MCAL_Layer" -I"../MCAL_Layer/ADC" -I"../MCAL_Layer/GPIO" -I"../MCAL_Layer/Interrupt" -I"../MCAL_Layer/I2C" -I"../MCAL_Layer/SPI" -I"../ECU_Layer/LED" -I"../MCAL_Layer/Timer0" -I"../MCAL_Layer/Timer1" -I"../Services_Layer" -I"../Services_Layer/Lighting_ECU" -I"../Services_Layer/LDR"  -Og -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega32a -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.7.374\gcc\dev\atmega32a" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

MCAL_Layer/ADC/hal_adc.o: ../MCAL_Layer/ADC/hal_adc.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.7.374\include" -I"../MCAL_Layer" -I"../MCAL_Layer/ADC" -I"../MCAL_Layer/GPIO" -I"../MCAL_Layer/Interrupt" -I"../MCAL_Layer/I2C" -I"../MCAL_Layer/SPI" -I"../ECU_Layer/LED" -I"../MCAL_Layer/Timer0" -I"../MCAL_Layer/Timer1" -I"../Services_Layer" -I"../Services_Layer/Lighting_ECU" -I"../Services_Layer/LDR"  -Og -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega32a -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.7.374\gcc\dev\atmega32a" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

MCAL_Layer/device_config.o: ../MCAL_Layer/device_config.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.7.374\include" -I"../MCAL_Layer" -I"../MCAL_Layer/ADC" -I"../MCAL_Layer/GPIO" -I"../MCAL_Layer/Interrupt" -I"../MCAL_Layer/I2C" -I"../MCAL_Layer/SPI" -I"../ECU_Layer/LED" -I"../MCAL_Layer/Timer0" -I"../MCAL_Layer/Timer1" -I"../Services_Layer" -I"../Services_Layer/Lighting_ECU" -I"../Services_Layer/LDR"  -Og -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega32a -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.7.374\gcc\dev\atmega32a" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

MCAL_Layer/GPIO/hal_gpio.o: ../MCAL_Layer/GPIO/hal_gpio.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.7.374\include" -I"../MCAL_Layer" -I"../MCAL_Layer/ADC" -I"../MCAL_Layer/GPIO" -I"../MCAL_Layer/Interrupt" -I"../MCAL_Layer/I2C" -I"../MCAL_Layer/SPI" -I"../ECU_Layer/LED" -I"../MCAL_Layer/Timer0" -I"../MCAL_Layer/Timer1" -I"../Services_Layer" -I"../Services_Layer/Lighting_ECU" -I"../Services_Layer/LDR"  -Og -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega32a -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.7.374\gcc\dev\atmega32a" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

MCAL_Layer/I2C/hal_i2c.o: ../MCAL_Layer/I2C/hal_i2c.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.7.374\include" -I"../MCAL_Layer" -I"../MCAL_Layer/ADC" -I"../MCAL_Layer/GPIO" -I"../MCAL_Layer/Interrupt" -I"../MCAL_Layer/I2C" -I"../MCAL_Layer/SPI" -I"../ECU_Layer/LED" -I"../MCAL_Layer/Timer0" -I"../MCAL_Layer/Timer1" -I"../Services_Layer" -I"../Services_Layer/Lighting_ECU" -I"../Services_Layer/LDR"  -Og -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega32a -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.7.374\gcc\dev\atmega32a" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

MCAL_Layer/Interrupt/mcal_internal_interrupt.o: ../MCAL_Layer/Interrupt/mcal_internal_interrupt.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.7.374\include" -I"../MCAL_Layer" -I"../MCAL_Layer/ADC" -I"../MCAL_Layer/GPIO" -I"../MCAL_Layer/Interrupt" -I"../MCAL_Layer/I2C" -I"../MCAL_Layer/SPI" -I"../ECU_Layer/LED" -I"../MCAL_Layer/Timer0" -I"../MCAL_Layer/Timer1" -I"../Services_Layer" -I"../Services_Layer/Lighting_ECU" -I"../Services_Layer/LDR"  -Og -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega32a -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.7.374\gcc\dev\atmega32a" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

MCAL_Layer/Interrupt/mcal_external_interrupt.o: ../MCAL_Layer/Interrupt/mcal_external_interrupt.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.7.374\include" -I"../MCAL_Layer" -I"../MCAL_Layer/ADC" -I"../MCAL_Layer/GPIO" -I"../MCAL_Layer/Interrupt" -I"../MCAL_Layer/I2C" -I"../MCAL_Layer/SPI" -I"../ECU_Layer/LED" -I"../MCAL_Layer/Timer0" -I"../MCAL_Layer/Timer1" -I"../Services_Layer" -I"../Services_Layer/Lighting_ECU" -I"../Services_Layer/LDR"  -Og -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega32a -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.7.374\gcc\dev\atmega32a" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

MCAL_Layer/Interrupt/mcal_interrupt_manger.o: ../MCAL_Layer/Interrupt/mcal_interrupt_manger.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.7.374\include" -I"../MCAL_Layer" -I"../MCAL_Layer/ADC" -I"../MCAL_Layer/GPIO" -I"../MCAL_Layer/Interrupt" -I"../MCAL_Layer/I2C" -I"../MCAL_Layer/SPI" -I"../ECU_Layer/LED" -I"../MCAL_Layer/Timer0" -I"../MCAL_Layer/Timer1" -I"../Services_Layer" -I"../Services_Layer/Lighting_ECU" -I"../Services_Layer/LDR"  -Og -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega32a -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.7.374\gcc\dev\atmega32a" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

MCAL_Layer/Timer0/hal_timer0.o: ../MCAL_Layer/Timer0/hal_timer0.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.7.374\include" -I"../MCAL_Layer" -I"../MCAL_Layer/ADC" -I"../MCAL_Layer/GPIO" -I"../MCAL_Layer/Interrupt" -I"../MCAL_Layer/I2C" -I"../MCAL_Layer/SPI" -I"../ECU_Layer/LED" -I"../MCAL_Layer/Timer0" -I"../MCAL_Layer/Timer1" -I"../Services_Layer" -I"../Services_Layer/Lighting_ECU" -I"../Services_Layer/LDR"  -Og -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega32a -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.7.374\gcc\dev\atmega32a" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

MCAL_Layer/Timer1/hal_timer1.o: ../MCAL_Layer/Timer1/hal_timer1.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.7.374\include" -I"../MCAL_Layer" -I"../MCAL_Layer/ADC" -I"../MCAL_Layer/GPIO" -I"../MCAL_Layer/Interrupt" -I"../MCAL_Layer/I2C" -I"../MCAL_Layer/SPI" -I"../ECU_Layer/LED" -I"../MCAL_Layer/Timer0" -I"../MCAL_Layer/Timer1" -I"../Services_Layer" -I"../Services_Layer/Lighting_ECU" -I"../Services_Layer/LDR"  -Og -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega32a -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.7.374\gcc\dev\atmega32a" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

Services_Layer/LDR/LDR_interface.o: ../Services_Layer/LDR/LDR_interface.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.7.374\include" -I"../MCAL_Layer" -I"../MCAL_Layer/ADC" -I"../MCAL_Layer/GPIO" -I"../MCAL_Layer/Interrupt" -I"../MCAL_Layer/I2C" -I"../MCAL_Layer/SPI" -I"../ECU_Layer/LED" -I"../MCAL_Layer/Timer0" -I"../MCAL_Layer/Timer1" -I"../Services_Layer" -I"../Services_Layer/Lighting_ECU" -I"../Services_Layer/LDR"  -Og -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega32a -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.7.374\gcc\dev\atmega32a" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

Services_Layer/Lighting_ECU/lighting_interface.o: ../Services_Layer/Lighting_ECU/lighting_interface.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.7.374\include" -I"../MCAL_Layer" -I"../MCAL_Layer/ADC" -I"../MCAL_Layer/GPIO" -I"../MCAL_Layer/Interrupt" -I"../MCAL_Layer/I2C" -I"../MCAL_Layer/SPI" -I"../ECU_Layer/LED" -I"../MCAL_Layer/Timer0" -I"../MCAL_Layer/Timer1" -I"../Services_Layer" -I"../Services_Layer/Lighting_ECU" -I"../Services_Layer/LDR"  -Og -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega32a -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.7.374\gcc\dev\atmega32a" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	




# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : 5.4.0
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="Lighting.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -mmcu=atmega32a -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.7.374\gcc\dev\atmega32a"  
	@echo Finished building target: $@
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "Lighting.elf" "Lighting.hex"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "Lighting.elf" "Lighting.eep" || exit 0
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "Lighting.elf" > "Lighting.lss"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "Lighting.elf" "Lighting.srec"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-size.exe" "Lighting.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "Lighting.elf" "Lighting.a" "Lighting.hex" "Lighting.lss" "Lighting.eep" "Lighting.map" "Lighting.srec" "Lighting.usersignatures"
	