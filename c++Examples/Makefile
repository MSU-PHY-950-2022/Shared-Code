CC=g++

# set compiler options:
#   -g    = debugging
#   -Wall = show all warnings 
COPT=-Wall

default:
	@echo "Possible targets are:"
	@echo "equality   Compile equality.cpp"
	@echo "simple     Compile simple.cpp"
	@echo "probability     Compile probability.cpp"
	@echo "temperature     Compile temperature.cpp"
	@echo "statistics     Compile statistics.cpp"
	@echo "norefs     compile norefs.cpp"
	@echo "pointers   compile pointers.cpp"
	@echo "refs       compile refs.cpp"
	@echo "swap       compile swap.cpp"	
	@echo "swappters compile swap_pters.cpp"	
	@echo "swaprefs  compile swap_refs.cpp"	
	@echo "car	Compile car.cpp"
	@echo "point	Compile point.cpp"
	@echo "debug	Compile debug.cpp"
	@echo "format	Compile format.cpp"
	@echo "names	Compile names.cpp"
	@echo "read	Compile read.cpp"
	@echo "readline	Compile readline.cpp"
	@echo "strstream	Compile strstream.cpp"
	@echo "write	Compile write.cpp"

equality:
	$(CC) $(COPT)  equality.cpp -o Equality.exe

simple:
	$(CC) $(COPT)  simple.cpp -o Simple.exe

probability:
	$(CC) $(COPT)  probability.cpp -o Probability.exe

temperature:
	$(CC) $(COPT)  temperature.cpp -o Temperature.exe

statistics:
	$(CC) $(COPT)  statistics.cpp -o Statistics.exe

norefs:
	$(CC) $(COPT)  norefs.cpp -o Norefs.exe

swap:
	$(CC) $(COPT)  swap.cpp -o Swap.exe

swappters:
	$(CC) $(COPT)  swappters.cpp -o Swappters.exe

swaprefs:
	$(CC) $(COPT)  swaprefs.cpp -o Swaprefs.exe

car:
	$(CC) $(COPT)  car.cpp -o Car.exe

point:
	$(CC) $(COPT)  point.cpp -o Point.exe

debug:
	$(CC) $(COPT)  debug.cpp -o Debug.exe

format:
	$(CC) $(COPT)  format.cpp -o Format.exe

names:
	$(CC) $(COPT)  names.cpp -o Names.exe

read:
	$(CC) $(COPT)  read.cpp -o Read.exe

write:
	$(CC) $(COPT)  write.cpp -o Write.exe

readline:
	$(CC) $(COPT)  readline.cpp -o Readline.exe

strstream:
	$(CC) $(COPT)  strstream.cpp -o Strstream.exe


clean:
	-rm *.exe *.o *~