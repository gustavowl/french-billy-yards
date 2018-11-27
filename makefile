CC = g++
SRCDIR = src
BINDIR = bin
OPENGLFLAGS = -lGL -lGLU -lglut
CFLAGS = $(OPENGLFLAGS)

billy-yards: $(SRCDIR)/billy-yards.cpp
	@mkdir -p $(BINDIR)
	@echo "Begin compiling..."
	g++ $(SRCDIR)/billy-yards.cpp $(CFLAGS) -o $(BINDIR)/billy-yards -Wall
	@echo "Compiling finished"
