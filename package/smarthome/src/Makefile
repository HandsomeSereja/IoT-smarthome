CXX = $(TARGET_CXX)
CXXFLAGS = $(TARGET_CXXFLAGS) -I$(STAGING_DIR)/usr/include
LDFLAGS = $(TARGET_LDFLAGS) -L$(STAGING_DIR)/usr/lib

all: smarthome

smarthome: main.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDFLAGS) -lgpiod

clean:
	rm -f smarthome

.PHONY: all clean
