.PHONY: all build clean

all: clean build

build: src/account_manager.cpp src/account.cpp src/main.cpp src/utilities.cpp
	mkdir -p build
	g++ -g -std=c++11 -o build/banksystem \
	-I src/ \
	src/account_manager.cpp \
	src/account.cpp \
	src/main.cpp \
	src/utilities.cpp

clean:
	rm -f build/banksystem
