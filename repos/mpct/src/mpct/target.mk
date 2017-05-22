TARGET = mpct
SRC_CC = main.cpp
INC_DIR += $(REP_DIR)/../libports/include/lwip
LIBS   = base libmosquitto stdcxx lwip pthread
