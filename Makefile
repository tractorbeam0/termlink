# Created by tractorbeam
ROOT_DIR := $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

SOURCE_DIR = $(ROOT_DIR)/src
BIN_DIR := $(ROOT_DIR)/build
ALL_ASSETS := $(wildcard $(ROOT_DIR)/assets/*)

release: CMAKE_FLAGS := -DCMAKE_BUILD_TYPE=Release -DSRC_DIR:STRING=$(SOURCE_DIR)
release: configure build finalize

debug: CMAKE_FLAGS := -DCMAKE_BUILD_TYPE=Debug -DSRC_DIR:STRING=$(SOURCE_DIR)
debug: BIN_DIR := $(ROOT_DIR)/build-debug
debug: configure build finalize

test: debug
	cd $(BIN_DIR) && ./termlink

clean:
	rm -rf $(BIN_DIR) $(ROOT_DIR)/build-debug

configure: $(BIN_DIR)/Makefile

$(BIN_DIR)/Makefile:
	mkdir -p $(BIN_DIR)
	cmake $(CMAKE_FLAGS) -B $(BIN_DIR)

build: 
	make --no-print-directory -C $(BIN_DIR)

finalize: $(ALL_ASSETS)
	cp -r $^ $(BIN_DIR)

.PHONY: release debug test clean configure build finalize