CC = g++

resistance-calculator: resistance_calculator.cpp
	$(CC) -o resistance_calculator.out resistance_calculator.cpp
	./resistance_calculator.out
