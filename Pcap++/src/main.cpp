#include<regex>
#include<sstream>

#include<NetworkUtils.h>
#include<PcapLiveDeviceList.h>
#include "IpUtils.h"

#include "PcapDevice.h"
#include "strparse.h"
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


std::string replace(std::string str) {
	std::regex exp("[^0-9]");
	std::stringstream stream;
	std::regex_replace(std::ostream_iterator<char>(stream), str.begin(), str.end(), exp, "");
	return std::string{stream.str()};
}

void parseIP() {
	const char* addr = "12.420.69.1";
	for(auto s : parseIpv4(addr)) {
		std::cout << replace(s) << "\n";
	}
}
// Utils
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
template<class T>
std::vector<T> convertPtrToVector(T* data) {
	std::vector<T> v;
	for(int i=0;*(int*)data!=0;i++) {
		v.push_back(*data+i);
		data = data + 1;
	}
	return v;
}
uint32_t getIpv4AsInt(char *addrAsString) {
	uint32_t *addrInt = new uint32_t;
	pcpp::IPv4Address addr = addrAsString;
	uint8_t *bytes = (uint8_t*)addr.toBytes();
	memcpy(addrInt, bytes, sizeof(bytes));
	uint32_t addrInt_ =  *addrInt;
	delete addrInt;
	return addrInt_;
}
pcpp::IPv6Address instanceV6FromV4(char *addr) {
	uint32_t V4AddrInt = getIpv4AsInt(addr);
	uint8_t *V6Addr  = new uint8_t;
	memcpy(V6Addr, &V4AddrInt, sizeof(V6Addr));
	int x = *V6Addr;
	return pcpp::IPv6Address(V6Addr);
}

std::string BytesToString(uint8_t *Bytes) {
	char addrBuffer[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, Bytes, addrBuffer, INET_ADDRSTRLEN);
	return std::string(addrBuffer);
}
// Only for ipv4, TODO: make it compatible with ipv6
std::string asPlainStringNum(std::string string) {
	char temp[string.size()-4];
	std::remove(string.begin(), string.end(), '.');
	int i=0;
	for(auto s=string.begin();s<=string.end() - 4;s++) { 
		temp[i] = *s;
		i++;
	}
	return std::string(temp);
}
// End of Utils
// TODO: wrap this in a class && define some enum flags
int main() {
	using namespace pcpp;
	pcap_if_t* dev,  dev_;
	timespec t_spec;
	//std::cout << instanceV6FromV4("1.2.4.5");
	//std::string  b2s = BytesToString((uint8_t*)instanceV6FromV4("1.2.4.69").toBytes());
	//std::cout  <<  asPlainStringNum(b2s);
	IPv4Address ipv4("132.231.511.152");
	bool valid = ipv4.isValid_();
	parseIP();
	return 0;
	uint32_t dnsTTL = 0; 
	uint8_t *rawData = new uint8_t;
	double dnsTimeout = 0, realTimeout;
	std::vector<PcapLiveDevice> liveDevs;
	NetworkUtils NUtils;
	char ERR_BUF[PCAP_ERRBUF_SIZE+1];
	int ret = pcap_findalldevs(&dev, ERR_BUF);
	if(dev==NULL || ret!=0) {
		std::cout << "invalid dev\n";
		return -1;
	}
	PcapLiveDevice liveDev(dev,1,1,1);
	PcapLiveDeviceList liveDevList;
	liveDev.init();
	IPv4Address mainAddr = liveDev.getIPv4Address();
	liveDev.open();

	liveDevList.init();
	//MacAddress macaddr = NUtils.getMacAddress(mainAddr, &liveDev, dnsTimeout);
	if(liveDevList.getDnsServers().size()<1) std::cout << "can not find dns servers" << "\n";
	IPv4Address dnsAddr = liveDevList.getDnsServers().at(1);
	IPv4Address defaultGateWay = liveDev.getDefaultGateway();
	IPv4Address ipv4addr = NUtils.getIPv4Address(std::string{"google.com"}, &liveDev, dnsTimeout,dnsTTL,-1, dnsAddr, defaultGateWay);
	RawPacket rawpacket(rawData, sizeof(uint32_t)*8, t_spec, false);
	NUtils.ArpRecieved(&rawpacket, &liveDev, NULL);
	std::cout << ipv4addr << "\n";
}

// old main, bloated!!

/*
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
	uint16_t *unbytes = (uint16_t*)(*ipaddr).toBytes();
	std::vector<uint16_t> vec = convertPtrToVector(unbytes);
	int port =  atoi(pr);
	//std::cout << port;
	//SCDynamicStoreRef storeref = SCDynamicStoreCreate(kCFAllocatorSystemDefaul, CFSTR("test"), NULL,NULL);
	PcapLiveDevice _live(2);
	IPv4Address addripv4 =  utils.getIPv4Address(std::string{"google.com"}, &dev, x,y);
	
	//std::cout << 69;
	
}
*/

