CC = g++
INCLDIR = include
SRCDIR = src
BINDIR = bin
#BUILDDIR = build
OPENGLFLAGS = -lGL -lGLU -lglut 
CFLAGS = $(OPENGLFLAGS) -std=c++11
#DEBUGFLAGS = $(CFLAGS) -g -O0
INCLFLAG = -I $(INCLDIR)

french-billy-yarids: $(SRCDIR)/*.cpp
	@mkdir -p $(BINDIR)
	@echo "Begin compiling..."
	g++ $(SRCDIR)/*.cpp $(CFLAGS) $(INCLFLAG) -o $(BINDIR)/french-billy-yards -Wall
	@echo "Compiling finished"

#debug: $(SRCDIR)/*.cpp
#	@mkdir -p $(BINDIR)
#	@echo "Begin compilation of DEBUG code..."
#	g++ $(SRCDIR)/*.cpp $(DEBUGFLAGS) $(INCLFLAG) -o $(BINDIR)/debug-french-billy-yards -Wall
#	@echo "DEBUG code compiled!"

#clean:
#	rm $(BINDIR)/*
