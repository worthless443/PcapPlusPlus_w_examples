LDFLAGS=../libpcap++.so  ../../Packet++/Lib/libPacket++.a ../../Common++/Lib/Release/libCommon++.a ../../Pcap++/PF_RING/userland/libpcap-1.1.1-ring/libpcap.a ../../Pcap++/PF_RING/userland/lib/libpfring.a -lpcap
INCS=-I../header -I../../Common++/header/ -I../../Packet++/header
SRC=main

$(SRC): clean
	c++ $@.cpp $(INCS) $(LDFLAGS) -o $(@)
clean:
	rm -rf $(SRC)
