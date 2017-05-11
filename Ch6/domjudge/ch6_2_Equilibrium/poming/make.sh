#compile bison
bison --debug --verbose -o $1.tab.c $1.y
gcc -c -g -I.. $1.tab.c
#compile flex
flex -o $1.yy.c $1.l
gcc -c -g -I.. $1.yy.c
#compile and link bison and flex
gcc -o $1 $1.tab.o $1.yy.o -lfl -ly
