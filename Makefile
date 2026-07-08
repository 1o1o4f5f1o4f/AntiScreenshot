# AntiScreenshot2 Makefile
# Usage:
#   mingw32-make          - build project
#   mingw32-make run      - build and run
#   mingw32-make clean    - remove build artifacts
#   mingw32-make rebuild  - clean rebuild

TARGET  := build/antiscreenshot.exe
SRCDIR  := src
BLDDIR  := build

CXX     := g++
RC      := windres

CXXFLAGS := -mwindows -static -Wall -Wextra -Wpedantic -Oz
RCFLAGS  :=

LDFLAGS  := -mwindows -static

SRCS    := $(SRCDIR)/main.cpp
RCS     := $(SRCDIR)/Resource.rc

OBJS    := $(BLDDIR)/main.o
RCOBJ   := $(BLDDIR)/Resource.o

.PHONY: all run clean rebuild

all: $(TARGET)

$(BLDDIR):
	@echo "==> Creating build directory $(BLDDIR)"
	@if not exist $(BLDDIR) mkdir $(BLDDIR)

$(RCOBJ): $(RCS) $(SRCDIR)/resource.h resources/icon1.ico | $(BLDDIR)
	@echo "==> Compiling resource $<"
	$(RC) $(RCFLAGS) $< -o $@

$(BLDDIR)/main.o: $(SRCDIR)/main.cpp $(SRCDIR)/resource.h | $(BLDDIR)
	@echo "==> Compiling source $<"
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJS) $(RCOBJ)
	@echo "==> Linking $@"
	$(CXX) $(LDFLAGS) $^ -o $@
	@echo "==> Build succeeded: $@"

run: $(TARGET)
	@echo "==> Running $(TARGET)"
	$(TARGET)

clean:
	@echo "==> Cleaning build artifacts"
	@if exist $(BLDDIR) rmdir /s /q $(BLDDIR)
	@echo "==> Clean complete"

rebuild: clean all