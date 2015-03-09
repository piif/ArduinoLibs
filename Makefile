# it's just a library
TODO := lib

include ${AMM_DIR}/etc/Makefile.target

$(info TARGET_PLATFORM = ${TARGET_PLATFORM})

SOURCE_DIRS := ${LIBRARIES_DIRS} .
INCLUDE_FLAGS += $(addprefix -I,${LIBRARIES_DIRS} ${<D})

SOURCE_EXCLUDE_PATTERNS := /examples/ /tests/ /makePolice/

ifeq (${TARGET_PLATFORM},sam)
  SOURCE_EXCLUDES := MsTimer2/ /avr/
else
  SOURCE_EXCLUDES := DueTimer/ Audio/
  SOURCE_EXCLUDE_PATTERNS += /Audio/ /Scheduler/ /USBHost/ /sam/
endif

ifneq (${TARGET_MCU},atmega32u4)
  SOURCE_EXCLUDE_PATTERNS += /Esplora/ /Robot /SpacebrewYun/
endif

${TARGET_DIR}/Wire/Wire.o: INCLUDE_FLAGS += -I${<D}/utility
${TARGET_DIR}/Servo/src/avr/Servo.o: INCLUDE_FLAGS += -I${<D}/..

INCLUDE_FLAGS += -I${ARDUINO_IDE}/hardware/arduino/${TARGET_PLATFORM}/libraries/SPI

SOURCE_EXCLUDE_PATTERNS += /WiFi/ /SD/ /TFT/ /Ethernet/
# /Bridge/ /GSM/ /Temboo/ /Servo/

include ${AMM_DIR}/etc/Makefile.main
