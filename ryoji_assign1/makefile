CC = g++

mvote: mvote.o hash.o participant.o zipList.o
	$(CC) -o mvote mvote.o hash.o zipList.o participant.o

mvote.o: mvote.cpp hash.h zipList.h participant.h
	$(CC) -c mvote.cpp

hash.o: hash.cpp participant.h
	$(CC) -c hash.cpp

participant.o: participant.cpp
	$(CC) -c participant.cpp

zipList.o: zipList.cpp participant.h 
	$(CC) -c zipList.cpp

clean: 
	rm *.o mvote

