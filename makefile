CC = g++
INCLDIR = include
SRCDIR = src
BINDIR = bin
OPENGLFLAGS = -lGL -lGLU -lglut -std=c++11
CFLAGS = $(OPENGLFLAGS)
INCLFLAG = -I $(INCLDIR)

billy-yards: $(SRCDIR)/french-billy-yards.cpp
	@mkdir -p $(BINDIR)
	@echo "Begin compiling..."
	g++ $(SRCDIR)/*.cpp $(CFLAGS) $(INCLFLAG) -o $(BINDIR)/french-billy-yards -Wall
	@echo "Compiling finished"
