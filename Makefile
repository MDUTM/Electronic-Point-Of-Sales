BIN_DIR = build
INC_DIR = inc
SRC_DIR = src

CXX = g++
ARM = arm-linux-g++

CXXFLAGS = -std=c++11
LIB = -lpthread -lm

MAIN_SOURCE = bmp.cpp food.cpp lcd.cpp point.cpp thread.cpp udp.cpp callBack.cpp font.c foodFrame.cpp main.cpp touch.cpp cJSON.c fontUtil.cpp JsonUtil.c menuFrame.cpp shopFrame.cpp truetype.c

EPOS_SOURCE = epos.cpp bmp.cpp lcd.cpp point.cpp touch.cpp
SERVER_SOURCE = server.cpp udp.cpp cJSON.c JsonUtil.c

all: create_dir main epos server

create_dir:
	mkdir -p $(BIN_DIR)

main: $(addprefix $(SRC_DIR)/,$(MAIN_SOURCE))
	$(ARM) $(addprefix $(SRC_DIR)/,$(MAIN_SOURCE)) -o $(BIN_DIR)/main -I $(INC_DIR) $(CXXFLAGS) $(LIB)

epos: $(addprefix $(SRC_DIR)/,$(EPOS_SOURCE))
	$(ARM) $(addprefix $(SRC_DIR)/,$(EPOS_SOURCE)) -o $(BIN_DIR)/epos -I $(INC_DIR) $(CXXFLAGS) $(LIB)

server: $(addprefix $(SRC_DIR)/,$(SERVER_SOURCE))
	$(CXX) $(addprefix $(SRC_DIR)/,$(SERVER_SOURCE)) -o $(BIN_DIR)/server -I $(INC_DIR) $(CXXFLAGS) $(LIB)

.PHONY: clean
clean:
	rm -rf $(BIN_DIR)