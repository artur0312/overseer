CXX=g++
IDIR=./include
ODIR=./obj
SRCDIR=./src
_DEPS=overseer.h chessboard.h alphabeta.h rating.h
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))
_OBJ=overseer.o chessboard.o alphabeta.o rating.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	$(CXX) -c -o $@ $<

overseer:  $(OBJ)
	$(CXX) -o overseer $^


