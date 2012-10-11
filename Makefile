
#Vars

BUILD_DIR 	:= build/
SRC 		:= $(wildcard *.cpp)
OBJ 		:= $(SRC:%.cpp=build/%.o)
BIN 		:= lines

#compiler

CC 		:= g++
CFLAGS  := -Wall -pedantic -g
VERSION := 0.0.1
LDFLAGS := `pkg-config --cflags --libs allegro-5.0 allegro_acodec-5.0 allegro_audio-5.0 allegro_color-5.0 allegro_dialog-5.0 allegro_font-5.0 allegro_image-5.0 allegro_main-5.0 allegro_memfile-5.0 allegro_physfs-5.0 allegro_primitives-5.0 allegro_ttf-5.0` 


################################################################################

all: $(BIN)

build/%.o: %.cpp $(BUILD_DIR)
	@echo
	@echo "--- Building $@ ---"
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo


.PHONY: all checkdirs clean

$(BIN): $(OBJ)
	@echo "--- Building $(BIN) ---"
	@$(CC) $^ -o $(BIN) $(LDFLAGS) $(INCLUDE)
	@echo # newline
	@echo "Build Complete"
	@echo

checkdirs: $(BUILD_DIR)

$(BUILD_DIR):
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(BIN)
	@echo cleaned

#EOF