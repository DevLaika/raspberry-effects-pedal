CC = g++
CFLAGS = -Wall -c -g
LFLAGS = -Wall -g

MAIN = main

CPP = $(wildcard effect-master/*.cpp)
O = $(patsubst %.cpp,%.o, $(CPP))

EFFECT = effect.cpp
PEDAL = pedal.cpp
CHAIN = chain.cpp
MASTER = master.cpp
LOOPER = looper.cpp
LOWPASS = lowpass.cpp
BUTTON = button.cpp

install: $(MAIN).o $(O)
	$(CC) $(LFLAGS) $^ -o $(MAIN)

$(MAIN).o: $(MAIN).cpp
	$(CC) $(CFLAGS) $^ -o $@

$(O): %.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	del $(MAIN).exe $(MAIN).o $(subst /,\, $(O));