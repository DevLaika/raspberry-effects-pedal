CC = g++
CFLAGS = -Wall -c -g
LFLAGS = -Wall -g -pthread -lpigpio -lrt

MAIN = main

CPP = $(wildcard effect-master/*.cpp)
CPPO = $(patsubst %.cpp,%.o, $(CPP))

EFFECT = effect.cpp
PEDAL = pedal.cpp
CHAIN = chain.cpp
MASTER = master.cpp
LOOPER = looper.cpp
LOWPASS = lowpass.cpp
BUTTON = button.cpp

install: $(MAIN).o $(CPPO)
	$(CC) $(LFLAGS) $^ -o $(MAIN)

$(MAIN).o: $(MAIN).cpp
	$(CC) $(CFLAGS) $^ -o $@

$(CPPO): %.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
#	del $(MAIN).exe $(MAIN).o $(subst /,\, $(CPPO)) $(subst /,\, $(CO));
	rm -f $(MAIN) $(MAIN).o $(CPPO);
