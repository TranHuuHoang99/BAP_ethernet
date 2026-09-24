ifdef OS
   RM = rmdir /s /q
   FIX_PATH = $(subst /,\,$(1))
   CMAKE_GENERATOR = -G "MinGW Makefiles"
else
   RM = rm -rf
   FIX_PATH = $(1)
   CMAKE_GENERATOR =
endif

BUILD_DIR = build
BIN_DIR = $(BUILD_DIR)/bin

all: $(BUILD_DIR)
	@echo "======================================================"
	@echo "Configuration and compile in-progress with CMake..."
	@echo "======================================================"
	cd $(BUILD_DIR) && cmake .. $(CMAKE_GENERATOR) -DCMAKE_INSTALL_PREFIX=./install_outputs
	cd $(BUILD_DIR) && cmake --build . --target install

debug: $(BUILD_DIR)
	@echo "======================================================"
	@echo "Configuration and compile in-progress with CMake..."
	@echo "======================================================"
	cd $(BUILD_DIR) && cmake .. $(CMAKE_GENERATOR) -D__ASG_DEBUG_MODE__=ON -DCMAKE_INSTALL_PREFIX=./install_outputs
	cd $(BUILD_DIR) && cmake --build . --target install

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

clean:
	@echo "Cleaning build output directory ..."
	@$(RM) $(call FIX_PATH,$(BUILD_DIR))
	@echo "build directory deleted."

.PHONY: all clean
