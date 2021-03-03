CXX      := g++ --std=c++11 -g
CXXFLAGS := -pedantic-errors #-Wall -Wextra -Werror
LDFLAGS  := -L/usr/lib -lstdc++ -lm
BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := $(BUILD)/apps
TARGET_CREATOR	:= creator
TARGET_GAME		:= game
INCLUDE  := -Iinclude
DEPS     := $(wildcard include/*.hpp include/*/*.hpp include/*/*/*.hpp include/*/*/*/*.hpp)
SRC_GAME :=                       \
	$(filter-out src/creator.cpp, $(wildcard src/*.cpp src/*/*.cpp src/*/*/*.cpp src/*/*/*/*.cpp))         \

OBJECTS_GAME := $(SRC_GAME:%.cpp=$(OBJ_DIR)/%.o)
SRC_CREATOR :=                       \
	$(filter-out src/game.cpp, $(wildcard src/*.cpp src/*/*.cpp src/*/*/*.cpp src/*/*/*/*.cpp))         \

OBJECTS_CREATOR := $(SRC_CREATOR:%.cpp=$(OBJ_DIR)/%.o)


all: build creator game

rebuild: clean build creator game

creator: build $(APP_DIR)/$(TARGET_CREATOR)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(APP_DIR)/$(TARGET_CREATOR): $(OBJECTS_CREATOR) $(DEPS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) -o $(APP_DIR)/$(TARGET_CREATOR) $(OBJECTS_CREATOR)

game: build $(APP_DIR)/$(TARGET_GAME)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(APP_DIR)/$(TARGET_GAME): $(OBJECTS_GAME) $(DEPS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) -o $(APP_DIR)/$(TARGET_GAME) $(OBJECTS_GAME)

ifeq (run,$(firstword $(MAKECMDGOALS)))
  RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  $(eval $(RUN_ARGS):;@:)
endif

.PHONY: all build clean debug release game creator tree run run_crea format doxygen dependency doc

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: all

release: CXXFLAGS += -O2
release: all

clean:
	@echo Cleaning...
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*
	@echo DONE

tree:
	@echo Building tree...
	@echo \`\`\` > tree.md
	@tree -I "build|CPPLINT.cfg|doc|compile_commands.json|tags" >> tree.md
	@echo \`\`\` >> tree.md
	@echo DONE

run:
	@./build/apps/game $(RUN_ARGS)
run_crea:
	@./build/apps/creator

format:
	@echo Formating using clang-format...
	@sh ./clang-format-all src/ inlcude/
	@echo DONE

doxygen:
	@echo Generating Doxygen documentation...
	-@doxygen Doxyfile
	@echo DONE: Check doc/html/index.html

dependency:
	@echo Generating dependency graph...
	@python dependency_graph.py -f png include doc/dependency_graph
	@echo DONE: Check file doc/dependency_graph.png

doc: doxygen dependency tree
