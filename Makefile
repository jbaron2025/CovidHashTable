hashtable: CovidHashTable.o CovidDataBase.o
	g++ -o hashtable CovidHashTable.o CovidDataBase.o

CovidHashTable.o: CovidHashTable.cpp CovidDataBase.h
	g++ -c -Wall -Werror -pedantic CovidHashTable.cpp

CovidDataBase.o: CovidDataBase.cpp CovidDataBase.h
	g++ -c -Wall -Werror -pedantic CovidDataBase.cpp
