# it's just a library
TODO := lib

include ${ARDDUDE_DIR}/etc/target.mk

$(info TARGET_PLATFORM = ${TARGET_PLATFORM})

SOURCE_DIRS := ${LIBRARIES_DIRS} .
# ${<D is a workaround because some libs includes <..> instead of ".." for neighbour files
INCLUDE_FLAGS_EXTRA += $(addprefix -I,${LIBRARIES_DIRS} ${<D})

SOURCE_EXCLUDE_PATTERNS := /examples/ /tests/ /makePolice/

ifeq (${TARGET_PLATFORM},sam)
  SOURCE_EXCLUDES := MsTimer2/ /avr/ ledStrip/
  SOURCE_EXCLUDE_PATTERNS += led7/a574g.cpp /GSM/
else
  SOURCE_EXCLUDES := DueTimer/ Audio/ /sam/
  SOURCE_EXCLUDE_PATTERNS += /Audio/ /Scheduler/ /USBHost/
endif

ifneq (${TARGET_MCU},atmega32u4)
  SOURCE_EXCLUDE_PATTERNS += /Esplora/ /Robot /SpacebrewYun/
endif

${TARGET_DIR}/Wire/Wire.o: INCLUDE_FLAGS += -I${<D}/utility
${TARGET_DIR}/Servo/src/avr/Servo.o: INCLUDE_FLAGS += -I${<D}/..

# workaround because many libs depends on SPI by including <SPI.h> instead of <SPI/SPI.h>
INCLUDE_FLAGS_EXTRA += -I${ARDUINO_IDE}/hardware/arduino/${TARGET_PLATFORM}/libraries/SPI
#$(info INCLUDE_FLAGS_EXTRA = ${INCLUDE_FLAGS_EXTRA})
SOURCE_EXCLUDE_PATTERNS += /WiFi/ /SD/ /TFT/ /Ethernet/
# /Servo/
# /Bridge/ /Temboo/

#$(info SOURCE_EXCLUDE_PATTERNS = ${SOURCE_EXCLUDE_PATTERNS})
#$(info SOURCE_EXCLUDES = ${SOURCE_EXCLUDES})

include ${ARDDUDE_DIR}/etc/main.mk
