testdriveremployee: employee.o salariedemployee.o hourlyemployee.o testdriveremployee.o
	g++ employee.o salariedemployee.o hourlyemployee.o testdriveremployee.o -o testdriveremployee
employee.o: employee.h employee.cpp
	g++ -c employee.cpp
salariedemployee.o: salariedemployee.h salariedemployee.cpp
	g++ -c salariedemployee.cpp
hourlyemployee.o: hourlyemployee.h hourlyemployee.cpp
	g++ -c hourlyemployee.cpp
testdriveremployee.o: salariedemployee.h hourlyemployee.h testdriveremployee.cpp
	g++ -c testdriveremployee.cpp
clean: 
	rm *.o testdriveremployee

