LIBMOSQUITTO_DIR := $(call select_from_ports,libmosquitto)/src/lib/libmosquitto

SRC_LIBMOSQUITTO := logging_mosq.c \
        memory_mosq.c \
        messages_mosq.c \
        mosquitto.c \
        net_mosq.c \
        read_handle.c \
        read_handle_client.c \
        read_handle_shared.c \
        send_client_mosq.c \
        send_mosq.c \
        socks_mosq.c \
        srv_mosq.c \
        thread_mosq.c \
        time_mosq.c \
        tls_mosq.c \
        util_mosq.c \
        will_mosq.c

INC_DIR += $(LIBMOSQUITTO_DIR) $(LIBMOSQUITTO_DIR)/lib $(LIBMOSQUITTO_DIR)/lib/cpp/

SRC_CC = $(addprefix $(LIBMOSQUITTO_DIR)/lib/, $(SRC_LIBMOSQUITTO)) $(LIBMOSQUITTO_DIR)/lib/cpp/mosquittopp.cpp

LIBS += libc libc_lwip lwip pthread stdcxx

CC_DEF += -DWITH_THREADING -DHAVE_PSELECT

SHARED_LIB = yes

CC_OPT += -O2
