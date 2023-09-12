# Created by tractorbeam
ROOT_DIR := $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

SOURCE_DIR = $(ROOT_DIR)/src
BIN_DIR = $(ROOT_DIR)/bin
BUILD_DIR := $(BIN_DIR)/build
ALL_ASSETS := $(wildcard $(ROOT_DIR)/assets/*)

release: CMAKE_FLAGS := -DCMAKE_BUILD_TYPE=Release -DSRC_DIR:STRING=$(SOURCE_DIR)
release: BUILD_DIR := $(BIN_DIR)/release
release: configure build finalize

debug: CMAKE_FLAGS := -DCMAKE_BUILD_TYPE=Debug -DSRC_DIR:STRING=$(SOURCE_DIR)
debug: BUILD_DIR := $(BIN_DIR)/debug
debug: configure build finalize

test: BUILD_DIR := $(BIN_DIR)/debug
test: debug
	@cd $(BUILD_DIR) && ./termlink

clean:
	@rm -rf $(BIN_DIR) $(ROOT_DIR)/build

configure: $(BUILD_DIR)/Makefile

$(BUILD_DIR)/Makefile:
	@mkdir -p $(BUILD_DIR)
	@cmake $(CMAKE_FLAGS) -B $(BUILD_DIR)

build: $(BUILD_DIR)/termlink

$(BUILD_DIR)/termlink:
	@make --no-print-directory -C $(BUILD_DIR)
	@mv $(BUILD_DIR)/termlink $(BIN_DIR)/termlink

finalize: $(ALL_ASSETS)
	@cp -r $^ $(BIN_DIR)

.PHONY: release debug test clean configure build finalize