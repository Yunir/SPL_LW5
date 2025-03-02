FLAGS=-ggdb -c -Wall -Werror -Wextra -std=c89 -ansi -pedantic

BUILD_DIR  := ./build
SOURCE_DIR := ./src

SOURCE_FILES := $(wildcard $(SOURCE_DIR)/*.c)
BUILD_FILES  := $(patsubst $(SOURCE_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCE_FILES))


all: main

main: $(BUILD_FILES)
	gcc -ggdb -o main $^ -lm

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	mkdir -p $(dir $@)
	gcc $(FLAGS) -o $@ $<

clean:
	rm -rf main $(BUILD_DIR) images/rp.bmp images/cube.bmp
