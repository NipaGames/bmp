SRC_DIR := src
OBJ_DIR := objects
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/**/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))
OBJ_COUNT := $(words $(OBJ_FILES))
EXECUTABLE_DIR = bin
EXECUTABLE := bmp.exe
LDLIBS :=
LDFLAGS := -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic
INCLUDES := -Isrc
CC := ccache g++
CXXFLAGS := -std=c++17

_pos = $(if $(findstring $1,$2),$(call _pos,$1,\
       $(wordlist 2,$(words $2),$2),x $3),$3)
pos = $(words $(call _pos,$1,$2))

all: setup $(EXECUTABLE_DIR)/$(EXECUTABLE) clean

setup:
	@echo [INFO] Setting up directories
	@if not exist $(EXECUTABLE_DIR) mkdir $(EXECUTABLE_DIR)
	@if exist $(OBJ_DIR) rmdir /s /q $(OBJ_DIR)
	@xcopy $(SRC_DIR) $(OBJ_DIR) /t /e /q /i

clean:
	@echo [INFO] Cleaning objects
	@if exist $(OBJ_DIR) rmdir /s /q $(OBJ_DIR)
	@echo [INFO] Done!

$(EXECUTABLE_DIR)/$(EXECUTABLE): $(OBJ_FILES)
	@echo [LINKING] Linking ${OBJ_COUNT} files total
	@$(CC) $(CXXFLAGS) $(INCLUDES) -o $@ $^ $(LDFLAGS) $(LDLIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo [COMPILE] ($(call pos,$@,$(OBJ_FILES))/${OBJ_COUNT}) Compiling $<
	@$(CC) $(CXXFLAGS) -c -o $@ $< $(INCLUDES) $(LDFLAGS)
	@echo [COMPILE] Compiled into $@
