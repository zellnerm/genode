TARGET = mpct
SRC_CC = main.cpp temperature_conversion.cpp
INC_DIR += . /home/alex/Projects/genode/repos/libports/include/lwip/
LIBS   = base libmosquitto stdcxx lwip pthread
