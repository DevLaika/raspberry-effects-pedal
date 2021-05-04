CC = g++
CFLAGS = -Wall -c -g
LFLAGS = -Wall -g

MAIN = main

CPP = $(wildcard effect-master/*.cpp)
C = bcm2835-master/bcm2835.c
CPPO = $(patsubst %.cpp,%.o, $(CPP))
CO = $(patsubst %.c,%.o, $(C))

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

$(CO): %.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
#	del $(MAIN).exe $(MAIN).o $(subst /,\, $(CPPO)) $(subst /,\, $(CO));
	rm $(MAIN) $(MAIN).o $(CPPO) $(CO);