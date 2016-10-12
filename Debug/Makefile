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
../CAN\ MCP2515\ header\ files


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../CAN_driver.c \
../CAN_test.c \
../joy_ctrl.c \
../d_latch_test.c \
../GAL_test.c \
../MCP2515_driver.c \
../memory_interface.c \
../menu.c \
../OLED.c \
../Oving1.c \
../slide.c \
../SPI_driver.c \
../SRAM_test.c \
../uart.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
CAN_driver.o \
CAN_test.o \
joy_ctrl.o \
d_latch_test.o \
GAL_test.o \
MCP2515_driver.o \
memory_interface.o \
menu.o \
OLED.o \
Oving1.o \
slide.o \
SPI_driver.o \
SRAM_test.o \
uart.o

OBJS_AS_ARGS +=  \
CAN_driver.o \
CAN_test.o \
joy_ctrl.o \
d_latch_test.o \
GAL_test.o \
MCP2515_driver.o \
memory_interface.o \
menu.o \
OLED.o \
Oving1.o \
slide.o \
SPI_driver.o \
SRAM_test.o \
uart.o

C_DEPS +=  \
CAN_driver.d \
CAN_test.d \
joy_ctrl.d \
d_latch_test.d \
GAL_test.d \
MCP2515_driver.d \
memory_interface.d \
menu.d \
OLED.d \
Oving1.d \
slide.d \
SPI_driver.d \
SRAM_test.d \
uart.d

C_DEPS_AS_ARGS +=  \
CAN_driver.d \
CAN_test.d \
joy_ctrl.d \
d_latch_test.d \
GAL_test.d \
MCP2515_driver.d \
memory_interface.d \
menu.d \
OLED.d \
Oving1.d \
slide.d \
SPI_driver.d \
SRAM_test.d \
uart.d

OUTPUT_FILE_PATH +=Oving1.elf

OUTPUT_FILE_PATH_AS_ARGS +=Oving1.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler





























./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 4.9.2
	$(QUOTE)E:\AtmelStudio7.0\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"E:\AtmelStudio7.0\7.0\Packs\atmel\ATmega_DFP\1.1.130\include"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega162 -B "E:\AtmelStudio7.0\7.0\Packs\atmel\ATmega_DFP\1.1.130\gcc\dev\atmega162" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
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
	@echo Invoking: AVR/GNU Linker : 4.9.2
	$(QUOTE)E:\AtmelStudio7.0\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="Oving1.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -mmcu=atmega162 -B "E:\AtmelStudio7.0\7.0\Packs\atmel\ATmega_DFP\1.1.130\gcc\dev\atmega162"  
	@echo Finished building target: $@
	"E:\AtmelStudio7.0\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "Oving1.elf" "Oving1.hex"
	"E:\AtmelStudio7.0\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "Oving1.elf" "Oving1.eep" || exit 0
	"E:\AtmelStudio7.0\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "Oving1.elf" > "Oving1.lss"
	"E:\AtmelStudio7.0\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "Oving1.elf" "Oving1.srec"
	"E:\AtmelStudio7.0\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-size.exe" "Oving1.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "Oving1.elf" "Oving1.a" "Oving1.hex" "Oving1.lss" "Oving1.eep" "Oving1.map" "Oving1.srec" "Oving1.usersignatures"
	