gcc -c csvRead.c
gcc -c readSettings.c
gcc -c setSettings.c
gcc -c appliance.c
gcc -c Main.c
gcc -c Menu.c

gcc readSettings.o setSettings.o appliance.o csvRead.o Menu.o Main.o -lm -o test.out
