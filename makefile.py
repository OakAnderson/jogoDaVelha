from os import system as sys

sys('''
gcc -c functions.c
gcc -c main.c
gcc -o executavel main.o functions.o
rm *.o
./executavel
''')