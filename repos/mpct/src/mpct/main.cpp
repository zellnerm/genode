#include <base/printf.h>
#include <mosquittopp.h>

#include <cstdio>
#include <cstring>

// lwip includes
extern "C" {
	#include <lwip/sockets.h>
	#include <lwip/api.h>
}
#include <lwip/genode.h>
#include <nic/packet_allocator.h>

#include <timer_session/connection.h>

class MPCT : public mosqpp::mosquittopp {
public:
	MPCT(const char* id, const char* host, int port) : mosquittopp(id) {
		mosqpp::lib_init();

		int keepalive = 60;
		connect(host, port, keepalive);
	}
	void on_connect(int ret) {
		PDBG("Connect with code %d!", ret);
	}

	void on_publish(int ret) {
		PDBG("Publish with code %d!", ret);
	}

	void on_disconnect(int ret) {
		PDBG("Disconnect with code %d!", ret);
	}

	void on_error() {
		PDBG("Error!");
	}
};

int main(int argc, char* argv[]) {
	lwip_tcpip_init();

	Timer::Connection timer;

	//timer.msleep(10000);

	enum { BUF_SIZE = Nic::Packet_allocator::DEFAULT_PACKET_SIZE * 128 };

	if (lwip_nic_init(inet_addr("192.168.100.42"),
										inet_addr("255.255.255.0"),
										inet_addr("192.168.100.254"),
										BUF_SIZE,
										BUF_SIZE)) {
		PERR("lwip init failed!");
		return 1;
	}

	PDBG("Trying to connect");
	class MPCT *mpct = new MPCT("mpct", "192.168.100.254", 1883);
	PDBG("Connect... done?");

	char buffer[1024] = { 0 };
	int i = 0, ret = -1;
	int loop;
	while(1) {
		loop = mpct->loop();
		if (loop) {
			//PDBG("reconnecting!");
			mpct->reconnect();
		}
		sprintf(buffer, "Hello World: %d", i);
		ret = mpct->publish(NULL, "mpct", strlen(buffer), buffer);
		PDBG("Publish '%s' successful: %d", buffer, MOSQ_ERR_SUCCESS == ret);
		i++;
		timer.msleep(10);
	}

	mosqpp::lib_cleanup();

	return 0;
}
