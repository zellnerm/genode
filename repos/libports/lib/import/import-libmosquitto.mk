LIBMOSQUITTO_PORT_DIR := $(call select_from_ports,libmosquitto)
INC_DIR += $(LIBMOSQUITTO_PORT_DIR)/src/lib/libmosquitto/lib/ $(LIBMOSQUITTO_PORT_DIR)/src/lib/libmosquitto/lib/cpp
