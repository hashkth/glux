
# Usage:
# make - build for all versions
# make VER=3.XX - build for 3.XX

ifneq ($(strip $(VER)),)
MAKEFLAGS += -j4
endif

VERSIONS := 3.11 3.12 3.13
VER ?=

PYTHON_SUFFIX = $(subst .,,$(VER))
PYTHON = py -$(VER)

PY_PATH = $(shell $(PYTHON) -c "import sys; print(sys.prefix)")
PY_INCLUDE = $(PY_PATH)/include
PYBIND11_INCLUDE = $(shell $(PYTHON) -c "import pybind11; print(pybind11.get_include())")

CC := gcc
CFLAGS := -O2 -Wall -ffunction-sections -fdata-sections -msse2

CXX := g++
CXXFLAGS := -O2 -Wall -std=c++17 -ffunction-sections -fdata-sections -msse2 -finline-functions

INCLUDES = 	-Iinclude \
			-Iexternal/glad/include \
			-Iexternal/glfw/include \
			-Iexternal/imgui/include \
           	-I"$(PY_INCLUDE)" \
           	-I"$(PYBIND11_INCLUDE)"

GLFW_LIB := external/glfw/lib/libglfw3.a

LDFLAGS := 	-shared -static-libgcc -static-libstdc++ \
			-Wl,--gc-sections -Wl,--strip-all

LDLIBS = 	-L"$(PY_PATH)/libs" -lpython$(PYTHON_SUFFIX) \
			"$(GLFW_LIB)" -lgdi32 -lopengl32

DEPFLAGS := -MMD -MP

NAME := glux

SRC_DIR := src
GLAD_SRC := $(wildcard external/glad/src/*.c) \
            $(wildcard external/glad/src/*.cpp)

IMGUI_SRC := $(wildcard external/imgui/src/*.cpp)
SRC := 	$(wildcard $(SRC_DIR)/*.cpp) \
		$(GLAD_SRC) \
		$(IMGUI_SRC)

OBJ_DIR = obj/$(PYTHON_SUFFIX)
OBJ = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(filter %.cpp,$(SRC))) \
      $(patsubst %.c,$(OBJ_DIR)/%.o,$(filter %.c,$(SRC)))

OUTPUT_DIR = release

TARGET = $(OUTPUT_DIR)/$(NAME)$(PYTHON_SUFFIX).pyd

.PHONY: all multi-build build-one build clean

ifeq ($(strip $(VER)),)
all: multi-build
else
all: build-one
endif

define BUILD_VERSION
.PHONY: build-$(subst .,,$(1))

build-$(subst .,,$(1)):
	@echo.
	@echo Building library for Python $(1)
	@echo ----------------------------------
	@$$(MAKE) -j4 --no-print-directory VER=$(1) build
endef

$(foreach v,$(VERSIONS),$(eval $(call BUILD_VERSION,$(v))))

multi-build: $(addprefix build-,$(subst .,,$(VERSIONS)))

build: $(TARGET)

$(TARGET): $(OBJ)
	@if not exist "$(OUTPUT_DIR)" mkdir "$(OUTPUT_DIR)"
	@echo Linking $@
	@$(CXX) $(LDFLAGS) $^ -o $@ $(LDLIBS)
	@echo BUILD SUCCESS: $(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@if not exist "$(@D)" mkdir "$(@D)"
	@echo Compiling $<
	@$(CXX) $(INCLUDES) $(CXXFLAGS) $(DEPFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: %.c
	@if not exist "$(@D)" mkdir "$(@D)"
	@echo Compiling $<
	@$(CC) $(INCLUDES) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

-include $(OBJ:.o=.d)

clean:
	@if exist "obj" rmdir /s /q "obj"
	@echo Cleaning complete!