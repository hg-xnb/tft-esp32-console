# Project information
CPP_FILE_PATH 	:= img2bin.cpp
CXX           	:= g++
CXXFLAGS      	:= -Wall -Wextra -Werror -O2 -std=c++17
LDFLAGS       	:= -ljpeg  # Linking flag for libjpeg

# Directories
SRC_DIR        	:= archived
IMG_DIR        	:= imgs
BIN_DIR        	:= bins
RESIZED_IMG_DIR := resized_imgs

# Input and Output Files
TARGET         	:= img2bin
SRCS           	:= $(CPP_FILE_PATH)

# Object Files (Replace .cpp with .o)
OBJS           	:= $(SRCS:.cpp=.o)

# Image Size Parameters
WIDTH          	:= 220
HEIGHT         	:= 172

# 
SDCARD_TARGET	:= /media/ngxxfus/SDCARD

# Create the output directories if they don't exist
$(shell mkdir -p $(BIN_DIR) $(RESIZED_IMG_DIR))

# Default build rule
all: $(TARGET)

# Convert JPG images in the imgs folder to BIN images and resized previews
convert_images: $(TARGET)
	@printf "Converting images..."
	@for img in $(IMG_DIR)/*; do\
		echo "\n@$$img";\
		./$(TARGET) $$img;\
	done

# Build the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(LDFLAGS) -o $(TARGET)

# Compile .cpp files into .o object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


# Clean all build files and output directories
clean:
	rm -f $(OBJS) $(TARGET)
	rm -rf $(BIN_DIR)/* $(RESIZED_IMG_DIR)/*

# Rebuild the project from scratch
rebuild: clean all

copy2sdcard:
	rm -rf $(SDCARD_TARGET)/imgs/*
	mkdir -p $(SDCARD_TARGET)/imgs
	@for bin_img in $(BIN_DIR)/*; do\
		echo "cp -rf $$bin_img $(SDCARD_TARGET)/imgs/";\
		cp -rf $$bin_img $(SDCARD_TARGET)/imgs/;\
	done

install_dep:
	sudo apt update
	sudo apt upgrade
	sudo apt install g++ gcc
	sudo apt install libjpeg-dev