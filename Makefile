# Created by tractorbeam
ROOT_DIR := $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

SOURCE_DIR = $(ROOT_DIR)/src
BIN_DIR = $(ROOT_DIR)/bin
CMAKE_DIR := $(BIN_DIR)
ALL_ASSETS := $(wildcard $(ROOT_DIR)/assets/*)

release: CMAKE_FLAGS := -DCMAKE_BUILD_TYPE=Release -DSRC_DIR:STRING=$(SOURCE_DIR)
release: CMAKE_DIR := $(BIN_DIR)/release
release: configure build finalize

debug: CMAKE_FLAGS := -DCMAKE_BUILD_TYPE=Debug -DSRC_DIR:STRING=$(SOURCE_DIR)
debug: CMAKE_DIR := $(BIN_DIR)/debug
debug: configure build finalize

test: debug
	@cd $(BIN_DIR) && ./termlink

clean:
	@rm -rf $(BIN_DIR) $(ROOT_DIR)/build

configure: $(CMAKE_DIR)/Makefile

$(CMAKE_DIR)/Makefile:
	@mkdir -p $(CMAKE_DIR)
	@cmake $(CMAKE_FLAGS) -B $(CMAKE_DIR)

build: $(CMAKE_DIR)/termlink

$(CMAKE_DIR)/termlink:
	@make --no-print-directory -C $(CMAKE_DIR)
	@mv $(CMAKE_DIR)/termlink $(BIN_DIR)/termlink

finalize: $(ALL_ASSETS)
	@cp -r $^ $(BIN_DIR)

.PHONY: release debug test clean configure build finalize