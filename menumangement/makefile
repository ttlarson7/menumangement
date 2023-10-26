CC= g++ --std=c++11 -g -s
exe_file=run

$(exe_file): prog.cpp coffee.o menu.o order.o shop.o
	$(CC) prog.cpp coffee.o menu.o order.o shop.o -o $(exe_file)

shop.o: shop.h shop.cpp
	$(CC) -c shop.cpp

menu.o: menu.h menu.cpp
	$(CC) -c menu.cpp

order.o: order.h order.cpp
	$(CC) -c order.cpp

coffee.o: coffee.h coffee.cpp
	$(CC) -c coffee.cpp

clean: 
	rm -f *.o $(exe_file)