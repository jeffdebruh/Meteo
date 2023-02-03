all:weather

Sort.o: Sort.c Sort.h
	gcc -c Sort.c -o Sort.o -lm
t1.o: t1.c t1.h
	gcc -c t1.c -o t1.o -lm
p1.o: p1.c p1.h
	gcc -c p1.c -o p1.o -lm
tp2.o: tp2.c tp2.h
	gcc -c tp2.c -o tp2.o -lm
tp3.o: tp3.c tp3.h
	gcc -c tp3.c -o tp3.o -lm
height.o: height.c height.h
	gcc -c height.c -o height.o -lm
wind.o: wind.c wind.h
	gcc -c wind.c -o wind.o -lm
moist.o: moist.c moist.h
	gcc -c moist.c -o moist.o -lm
moist2.o: moist2.c moist2.h
	gcc -c moist2.c -o moist2.o -lm
main.o: main.c main.h
	gcc -c main.c -o main.o -lm
weather: main.o t1.o p1.o tp2.o tp3.o height.o wind.o moist.o Sort.o moist2.o 
	gcc main.o t1.o p1.o tp2.o tp3.o height.o wind.o moist.o moist2.o Sort.o -o weather -lm

clean: 
	rm -f *.o
	rm weather

