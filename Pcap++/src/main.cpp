#include<NetworkUtils.h>
#include<PcapLiveDeviceList.h>
#include "IpUtils.h"

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
class IPcapDevice_d : public pcpp::IPcapDevice {

	public:
	bool (IPcapDevice::*open_p)(), (*close_p)();

	IPcapDevice_d() : IPcapDevice() {
		open_p =  &IPcapDevice::open;
		init();
	}

	// put impl
	bool open() {return true;}  
	void close() {}
	void getStatistics(PcapStats &stats) const {}

	void init() {
		if(!open()) close();
	}
};

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
	std::remove(str.begin(), str.end(), ' ');
	char *string = (char*)str.c_str();
	for(char *s = (char*)str.c_str();;s = s+1, i++) {
		if(*(int*)s==0) {
			return string + (i-2);
		}
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

	pcpp::PortFilter filter(24, pcpp::SRC);
	filter.parseToString(str);

	pcpp::EthLayer ethLayer(dev.getMacAddress(), *(pcpp::MacAddress*)ipaddr );
	

	using namespace pcpp;

	IPcapDevice_d idev;

	PcapLiveDeviceList idevlist_  =  PcapLiveDeviceList::getInstance();

	PcapLiveDeviceList idevlist; //= PcapLiveDeviceList::getInstance();
	idevlist.init();
	idevlist.setDnsServers();
	std::cout <<  idevlist_.getDnsServers().size();

 	PcapLiveDevice *livedev = idevlist.getPcapLiveDeviceByIp(*ipaddr);
	char *pr = parse(str);
	struct pcap_pkthdr pkthdr;
	//idevlist_.fonPacketArrivesBlockingMode("aissy", pkthdr, NULL);
	dev.setDefaultGateway();
	PcapLiveDeviceList *devlist__ = PcapLiveDeviceList::getInstancePtr();
	idevlist_ = *devlist__;

	if(ipaddr->isValid()) {
		PcapLiveDevice *new_idevlist = idevlist.getPcapLiveDeviceByIp(*ipaddr);
		PcapLiveDevice new_idev = *new_idevlist; //problem : c'strutor returns segfault
	}
	int port = atoi(pr);

	std::cout << port;

	//SCDynamicStoreRef storeref = SCDynamicStoreCreate(kCFAllocatorSystemDefaul, CFSTR("test"), NULL,NULL);
	PcapLiveDevice _live(2);
	//IPv4Address addripv4 =  utils.getIPv4Address(std::string{"google.com"}, &dev, x,y);
	
	//std::cout << 69;
	
}
