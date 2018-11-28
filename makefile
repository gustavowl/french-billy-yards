CC = g++
INCDIR = include
SRCDIR = src
BINDIR = bin
OPENGLFLAGS = -lGL -lGLU -lglut
CFLAGS = $(OPENGLFLAGS)
INCFLAG = -I $(INCDIR)

billy-yards: $(SRCDIR)/french-billy-yards.cpp
	@mkdir -p $(BINDIR)
	@echo "Begin compiling..."
	g++ $(SRCDIR)/*.cpp $(CFLAGS) $(INCFLAG) -o $(BINDIR)/french-billy-yards -Wall
	@echo "Compiling finished"
