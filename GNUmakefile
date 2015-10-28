TARGET := glfft_cli

BACKEND := glfw

EXTERNAL_INCLUDE_DIRS := -ImuFFT -I. -Itest -Itest/$(BACKEND)
EXTERNAL_LIB_DIRS := -LmuFFT
EXTERNAL_LIBS := -lmufft
MUFFT_LIB := muFFT/libmufft.a

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

ifeq ($(BACKEND), glfw)
	ifeq ($(PLATFORM),win)
		LDFLAGS += -Lexternal/lib/win-x64 -lglfw3 -lopengl32 -lgdi32
		EXTERNAL_INCLUDE_DIRS += -Iexternal/include
	else
		LDFLAGS += -lmufft $(shell pkg-config glfw3 --libs) -lGL
	endif
	GLSYM := test/glfw/glsym/rglgen.c test/glfw/glsym/glsym_gl.c

	CC = clang
	CXX = clang++
endif

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

CXX_SOURCES := $(wildcard *.cpp) $(wildcard test/*.cpp) $(wildcard test/$(BACKEND)/*.cpp)
C_SOURCES := $(GLSYM)
OBJDIR := obj
OBJECTS := $(addprefix $(OBJDIR)/,$(CXX_SOURCES:.cpp=.o)) $(addprefix $(OBJDIR)/,$(C_SOURCES:.c=.o))
DEPS := $(OBJECTS:.o=.d)

CXXFLAGS += -Wall -Wextra -pedantic -std=c++11 $(EXTERNAL_INCLUDE_DIRS) -DGLFFT_SERIALIZATION
CFLAGS += -Wall -Wextra -std=c99 $(EXTERNAL_INCLUDE_DIRS)
LDFLAGS += $(EXTERNAL_LIB_DIRS) -lm


all: $(TARGET)

glfft.cpp: build_fft_inc

build_fft_inc:
	$(MAKE) -C glsl

-include $(DEPS)

muFFT/libmufft.a:
	$(MAKE) -C muFFT static PLATFORM=$(PLATFORM) TOOLCHAIN_PREFIX=$(TOOLCHAIN_PREFIX)

$(TARGET): $(OBJECTS) $(MUFFT_LIB)
	$(CXX) -o $@ $(OBJECTS) $(LDFLAGS) $(EXTERNAL_LIBS)

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) -c -o $@ $< $(CXXFLAGS) -MMD

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -c -o $@ $< $(CFLAGS) -MMD

clean:
	rm -rf $(OBJDIR) $(TARGET)
	$(MAKE) -C muFFT clean PLATFORM=$(PLATFORM)
	$(MAKE) -C glsl clean
	rm -f muFFT/libmufft.a

.PHONY: clean
