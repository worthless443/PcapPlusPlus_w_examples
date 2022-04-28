#include<NetworkUtils.h>

#include "PcapDevice.h"
#include "IPv4Layer.h"
#include "Packet.h"
#include "PcapFileDevice.h"
#include "PcapLiveDevice.h"
#include "cstdlib"
#include "iostream"
#include "cstdio"
#include "EthLayer.h"
#include<pcap/pcap.h>

pcap_if_t *getdev(pcap_if_t *d) {
	for(pcap_if_t *dv = d; dv!=NULL; dv = dv->next) {
		if(std::string{dv->name} == std::string{"enp7s0"}) { 
			return dv;
		}
	};
	return NULL;
}
char *parse(std::string str) {
	int i =0;
	char *string = (char*)str.c_str();
	for(char *s = (char*)str.c_str();;s = s+1, i++) {
		if(*(int*)s!=0) return (string + i)-2;
	}
	return NULL;
}

int main() {

	pcpp::NetworkUtils utils = pcpp::NetworkUtils::getInstance();
	pcap_if_t *d, *dd; //= NULL;
	char errbuf[PCAP_ERRBUF_SIZE+1];
	pcap_findalldevs(&d, errbuf);
	int index = 0, i=1;
	double x;
	uint32_t y;
	pcpp::RawPacketVector raw_v;
	std::string str;
	pcpp::Packet p(100);
	
	int *cap = new int;

	dd = getdev(d);
	if(dd==NULL) return 1;

	pcpp::PcapLiveDevice dev(dd,1,1,1);
	dev.open();
	pcpp::MacAddress macaddr  =  utils.getMacAddress(dev.getDefaultGateway(), &dev, x);
	pcpp::IPv4Address *ipaddr = (pcpp::IPv4Address*)&macaddr;

	pcpp::PortFilter filter(53, pcpp::SRC);
	filter.parseToString(str);


	pcpp::EthLayer ethLayer(dev.getMacAddress(), *(pcpp::MacAddress*)ipaddr );

	using namespace pcpp;
	IPcapDevice idev;
	if (dev.getDnsServers().size() == 0) return -1;

	IPv4Address addripv4 =  utils.getIPv4Address(std::string{"google.com"}, &dev, x,y);
	
	//std::cout << 69;
	
}
