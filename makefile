INC=include
BIN=bin
SRC=src
OBJ=obj
LIB=lib

CXX=g++
LDFLAGS= -L$(LIB) -ltetris
ALLEGROFLAGS= $(LDFLAGS) -L/usr/local/lib -lallegro_main -lallegro -lallegro_primitives -lallegro_image -lallegro_font -lallegro_ttf -lallegro_audio -lallegro_acodec 
CPPFLAGS= -Wall -g -I$(INC) -c 

all:$(BIN)/prueba $(BIN)/allegro $(BIN)/allegro2 $(OBJ)/timer.o


$(BIN)/allegro: $(OBJ)/allegroprueba.o $(LIB)/libtetris.a
	$(CXX) $< -o $@ $(ALLEGROFLAGS)

$(BIN)/prueba: $(OBJ)/mainprueba.o $(LIB)/libtetris.a
	$(CXX) $< -o $@ $(LDFLAGS)
$(BIN)/allegro2: $(OBJ)/allegroprueba2.o $(LIB)/libtetris.a
	$(CXX) $< -o $@ $(ALLEGROFLAGS)


$(LIB)/libtetris.a: $(OBJ)/tetromino.o $(OBJ)/timer.o $(OBJ)/coordinate.o $(OBJ)/tetrismap.o
	ar rvs $@ $^


$(OBJ)/coordinate.o: $(SRC)/coordinate.cpp $(INC)/overloading.h $(INC)/coordinate.h $(INC)/coordinate.h
	$(CXX) $(CPPFLAGS) $< -o $@

$(OBJ)/tetromino.o: $(SRC)/tetromino.cpp $(INC)/overloading.h $(INC)/tetromino.h $(INC)/coordinate.h
	$(CXX) $(CPPFLAGS) $< -o $@
$(OBJ)/tetrismap.o: $(SRC)/tetrismap.cpp $(INC)/overloading.h $(INC)/tetromino.h $(INC)/tetrismap.h $(INC)/coordinate.h $(INC)/timer.h
	$(CXX) $(CPPFLAGS) $< -o $@
$(OBJ)/mainprueba.o:$(SRC)/mainprueba.cpp $(INC)/overloading.h $(INC)/tetromino.h $(INC)/coordinate.h
	$(CXX) $(CPPFLAGS) $< -o $@
$(OBJ)/allegroprueba.o:$(SRC)/allegroprueba.cpp $(INC)/overloading.h $(INC)/tetromino.h $(INC)/tetrismap.h $(INC)/coordinate.h
	$(CXX) $(CPPFLAGS) $< -o $@
$(OBJ)/allegroprueba2.o:$(SRC)/allegroprueba2.cpp $(INC)/overloading.h $(INC)/tetromino.h $(INC)/tetrismap.h $(INC)/coordinate.h
	$(CXX) $(CPPFLAGS) $< -o $@
$(OBJ)/timer.o:$(SRC)/timer.cpp $(INC)/timer.h
	$(CXX) $(CPPFLAGS) $< -o $@
clean:
	rm $(OBJ)/*