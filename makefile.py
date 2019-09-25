from os import system as sys

sys('''
gcc -c IA.c
gcc -c functions.c
gcc -c main.c
gcc -o exe main.o functions.o IA.o
rm *.o
./exe
''')


