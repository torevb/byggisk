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
../solenoid.c \
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
solenoid.o \
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
solenoid.o \
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
solenoid.d \
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
solenoid.d \
SPI_driver.d \
SRAM_test.d \
uart.d

OUTPUT_FILE_PATH +=Oving1_6_2.elf

OUTPUT_FILE_PATH_AS_ARGS +=Oving1_6_2.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler































./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 4.8.1
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega162 -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
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
	@echo Invoking: AVR/GNU Linker : 4.8.1
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="Oving1_6_2.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -mmcu=atmega162  
	@echo Finished building target: $@
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "Oving1_6_2.elf" "Oving1_6_2.hex"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "Oving1_6_2.elf" "Oving1_6_2.eep" || exit 0
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "Oving1_6_2.elf" > "Oving1_6_2.lss"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "Oving1_6_2.elf" "Oving1_6_2.srec"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-size.exe" "Oving1_6_2.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "Oving1_6_2.elf" "Oving1_6_2.a" "Oving1_6_2.hex" "Oving1_6_2.lss" "Oving1_6_2.eep" "Oving1_6_2.map" "Oving1_6_2.srec" "Oving1_6_2.usersignatures"
	