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
SUBDIRS := 


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../adc.c \
../Arduino_Atmega2560.c \
../CAN_driver.c \
../CAN_test.c \
../ir_receiver.c \
../motor.c \
../MCP2515_driver.c \
../memory_interface.c \
../pid.c \
../pwm.c \
../scoretable.c \
../solenoid.c \
../SPI_driver.c \
../TWI_Master.c \
../uart.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
adc.o \
Arduino_Atmega2560.o \
CAN_driver.o \
CAN_test.o \
ir_receiver.o \
motor.o \
MCP2515_driver.o \
memory_interface.o \
pid.o \
pwm.o \
scoretable.o \
solenoid.o \
SPI_driver.o \
TWI_Master.o \
uart.o

OBJS_AS_ARGS +=  \
adc.o \
Arduino_Atmega2560.o \
CAN_driver.o \
CAN_test.o \
ir_receiver.o \
motor.o \
MCP2515_driver.o \
memory_interface.o \
pid.o \
pwm.o \
scoretable.o \
solenoid.o \
SPI_driver.o \
TWI_Master.o \
uart.o

C_DEPS +=  \
adc.d \
Arduino_Atmega2560.d \
CAN_driver.d \
CAN_test.d \
ir_receiver.d \
motor.d \
MCP2515_driver.d \
memory_interface.d \
pid.d \
pwm.d \
scoretable.d \
solenoid.d \
SPI_driver.d \
TWI_Master.d \
uart.d

C_DEPS_AS_ARGS +=  \
adc.d \
Arduino_Atmega2560.d \
CAN_driver.d \
CAN_test.d \
ir_receiver.d \
motor.d \
MCP2515_driver.d \
memory_interface.d \
pid.d \
pwm.d \
scoretable.d \
solenoid.d \
SPI_driver.d \
TWI_Master.d \
uart.d

OUTPUT_FILE_PATH +=Arduino_Atmega2560.elf

OUTPUT_FILE_PATH_AS_ARGS +=Arduino_Atmega2560.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler































./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 4.8.1
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mrelax -g2 -Wall -mmcu=atmega2560 -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
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
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="Arduino_Atmega2560.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -mrelax -mmcu=atmega2560  
	@echo Finished building target: $@
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "Arduino_Atmega2560.elf" "Arduino_Atmega2560.hex"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "Arduino_Atmega2560.elf" "Arduino_Atmega2560.eep" || exit 0
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "Arduino_Atmega2560.elf" > "Arduino_Atmega2560.lss"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "Arduino_Atmega2560.elf" "Arduino_Atmega2560.srec"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-size.exe" "Arduino_Atmega2560.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "Arduino_Atmega2560.elf" "Arduino_Atmega2560.a" "Arduino_Atmega2560.hex" "Arduino_Atmega2560.lss" "Arduino_Atmega2560.eep" "Arduino_Atmega2560.map" "Arduino_Atmega2560.srec" "Arduino_Atmega2560.usersignatures"
	