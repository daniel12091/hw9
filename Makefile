
CXX=g++
CXXLINK=$(CXX) 
CXXFLAGS=-g -Wall -std=c++11
OBJS=main.o libfirewall.so libinput.so



firewall.exe: main.o libfirewall.so libinput.so
	$(CXX) $(CXXFLAGS) main.o -o firewall.exe -lfirewall -linput -L.
	
main.o: main.cpp libfirewall.so
	$(CXX) $(CXXFLAGS) -c main.cpp 
	
libfirewall.so: ip.o port.o field.o string.o
	$(CXXLINK) -shared ip.o port.o field.o string.o -o libfirewall.so 

ip.o: field.o string.o ip.h ip.cpp
	$(CXX) $(CXXFLAGS) -c -fpic ip.cpp

port.o: field.o string.o port.h port.cpp
	$(CXX) $(CXXFLAGS) -c -fpic port.cpp

field.o: string.o field.h field.cpp
	$(CXX) $(CXXFLAGS) -c -fpic field.cpp
	
string.o: string.h string.cpp
	$(CXX) $(CXXFLAGS) -c -fpic string.cpp
	

clean:
	rm -rf *.o 