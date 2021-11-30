PROGRAM_NAME = sdl2_issue

SRC_DIR = src
TARGET_DIR = target
RELEASE_DIR = $(TARGET_DIR)/release

RELEASE = $(RELEASE_DIR)/$(PROGRAM_NAME)
RELEASE_FLAGS = $(shell sdl2-config --cflags --libs) -g

CC = cc
MKDIR = mkdir -p
RM = rm -r


all: $(RELEASE)


$(RELEASE): $(RELEASE_DIR)
	$(CC) $(SRC_DIR)/main.c -o $(RELEASE) $(RELEASE_FLAGS)


$(RELEASE_DIR): $(TARGET_DIR)
	$(MKDIR) $(RELEASE_DIR)


$(TARGET_DIR):
	$(MKDIR) $(TARGET_DIR)


clean:
	$(RM) $(TARGET_DIR)
