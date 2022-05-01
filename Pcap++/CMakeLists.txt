project(libpcap++)
file(GLOB Sources src/*.cpp)
set (CXX, clang++)
set(CMAKE_CXX_COMPILER "/usr/lib/llvm/14/bin/clang++")
set(LD_ header ../Common++/header
	../Packet++/header ../3rdParty/EndianPortable/include ../3rdParty/LightPcapNg/LightPcapNg/include)

set (LDFLAGS lib/libPcap++.a ../Packet++/Lib/libPacket++.a
	../Common++/Lib/Release/libCommon++.a
	../Pcap++/PF_RING/userland/libpcap-1.1.1-ring/libpcap.a
	../Pcap++/PF_RING/userland/lib/)
add_library(pcap++ ${Sources})
message(STATUS ${LD_})

target_include_directories(pcap++ PUBLIC ${LD_})

add_executable(main src/main.cpp)
target_link_directories(main PUBLIC ./ ../Common++/Lib/Release/
	../Packet++/Lib/ ../Pcap++/PF_RING/userland/lib/ ../Pcap++/PF_RING/userland/lib/)
target_link_libraries(main PUBLIC pcap++  Packet++  Common++  pfring pcap)
#target_compile_options(main PUBLIC )
target_include_directories(main PUBLIC ${LD_} )

