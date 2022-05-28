TARGET := glfft_cli
EXTERNAL_INCLUDE_DIRS := -I. -Itest -Itest/glfw

ifeq ($(PLATFORM),)
	PLATFORM = unix
	ifeq ($(shell uname -a),)
		PLATFORM = win
	else ifneq ($(findstring MINGW,$(shell uname -a)),)
		PLATFORM = win
	else ifneq ($(findstring Darwin,$(shell uname -a)),)
		PLATFORM = osx
	else ifneq ($(findstring win,$(shell uname -a)),)
		PLATFORM = win
	endif
endif

ifeq ($(PLATFORM),win)
	LDFLAGS += -Lexternal/lib/win-x64 -lglfw3 -lopengl32 -lgdi32
	EXTERNAL_INCLUDE_DIRS += -Iexternal/include
else
	LDFLAGS += $(shell pkg-config glfw3 --libs) -lGL
endif
GLSYM := test/glfw/glsym/rglgen.c test/glfw/glsym/glsym_gl.c

CXX = clang++
CC = clang

ifeq ($(PLATFORM),win)
	CC = gcc
	CXX = g++
endif

ifeq ($(DEBUG_SANITIZE), 1)
	CXXFLAGS += -O0 -gdwarf-2 -fsanitize=memory -DGLFFT_GL_DEBUG
	CFLAGS += -O0 -gdwarf-2 -fsanitize=memory -DGLFFT_GL_DEBUG
	LDFLAGS += -fsanitize=memory
else ifeq ($(DEBUG), 1)
	CXXFLAGS += -O0 -gdwarf-2 -DGLFFT_GL_DEBUG
	CFLAGS += -O0 -gdwarf-2 -DGLFFT_GL_DEBUG
else
	CXXFLAGS += -Ofast -gdwarf-2
	CFLAGS += -Ofast -gdwarf-2
endif

ifneq ($(TOOLCHAIN_PREFIX),)
	CC = $(TOOLCHAIN_PREFIX)gcc
	CXX = $(TOOLCHAIN_PREFIX)g++
endif

LDFLAGS += -pthread

all: build_fft_inc
	@+$(MAKE) $(TARGET)

CXX_SOURCES := $(wildcard *.cpp) $(wildcard test/*.cpp) $(wildcard test/glfw/*.cpp)
C_SOURCES := $(GLSYM)
OBJDIR := obj
OBJECTS := $(addprefix $(OBJDIR)/,$(CXX_SOURCES:.cpp=.o)) $(addprefix $(OBJDIR)/,$(C_SOURCES:.c=.o))
DEPS := $(OBJECTS:.o=.d)

CXXFLAGS += -Wall -Wextra -pedantic -std=c++11 $(EXTERNAL_INCLUDE_DIRS)
CFLAGS += -Wall -Wextra -std=c99 $(EXTERNAL_INCLUDE_DIRS)
LDFLAGS += $(EXTERNAL_LIB_DIRS) -lm

build_fft_inc:
	$(MAKE) -C glsl

-include $(DEPS)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS) $(LDFLAGS) $(EXTERNAL_LIBS)

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) -c -o $@ $< $(CXXFLAGS) -MMD

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -c -o $@ $< $(CFLAGS) -MMD

clean:
	rm -rf $(OBJDIR) $(TARGET)
	$(MAKE) -C glsl clean

.PHONY: clean
