# Created by tractorbeam
ROOT_DIR := $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

SOURCE_DIR = $(ROOT_DIR)/src
MAKEFILE_RELEASE = $(ROOT_DIR)/build/Makefile
MAKEFILE_DEBUG = $(ROOT_DIR)/build-debug/Makefile
BIN_DIR := $(ROOT_DIR)/build
ALL_ASSETS := $(wildcard $(ROOT_DIR)/assets/*)

release: CMAKE_FLAGS := -DCMAKE_BUILD_TYPE=Release -DSRC_DIR:STRING=$(SOURCE_DIR)
release: configure build finalize

debug: CMAKE_FLAGS := -DCMAKE_BUILD_TYPE=Debug -DSRC_DIR:STRING=$(SOURCE_DIR)
debug: BIN_DIR := $(ROOT_DIR)/build-debug
debug: configuredebug build finalize

test: debug
	cd $(ROOT_DIR)/build-debug && ./termlink

clean:
	rm -rf $(BIN_DIR) $(ROOT_DIR)/build-debug

rebuild: clean release

configure: $(MAKEFILE_RELEASE)

$(MAKEFILE_RELEASE):
	mkdir -p $(BIN_DIR)
	cmake $(CMAKE_FLAGS) -B $(BIN_DIR)

configuredebug: $(MAKEFILE_DEBUG)

$(MAKEFILE_DEBUG):
	mkdir -p $(BIN_DIR)
	cmake $(CMAKE_FLAGS) -B $(BIN_DIR)

build: 
	make --no-print-directory -C $(BIN_DIR)

finalize: $(ALL_ASSETS)
	cp -r $^ $(BIN_DIR)

.PHONY: release debug test clean rebuild configure build finalize