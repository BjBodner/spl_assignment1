# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
CC = g++
CFLAGS = -g -Wall -Weffc++ -std=c++11
LFLAGS = -L/usr/lib
OFILES = bin/Action.o bin/Customer.o bin/Trainer.o bin/Workout.o bin/Studio.o bin/main.o
# All Targets
all: studio

# Tool invocations
studio: bin/srcToOFile
	@echo 'Building target: hello'
	@echo 'Invoking: C++ Linker'
	$(CC) -o bin/studio $(OFILES) $(LFLAGS)
	@echo 'Finished building target: studio'
	@echo ' '

# Parse all cpp files to o files
bin/srcToOFile: $(OFILES)

# Depends on the source and header files
bin/Action.o: src/Action.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Action.o src/Action.cpp

# Depends on the source and header files
bin/Customer.o: src/Customer.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Customer.o src/Customer.cpp

# Depends on the source and header files
bin/Studio.o: src/Studio.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Studio.o src/Studio.cpp

# Depends on the source and header files
bin/Trainer.o: src/Trainer.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Trainer.o src/Trainer.cpp

# Depends on the source and header files
bin/Workout.o: src/Workout.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Workout.o src/Workout.cpp

# Depends on the source and header files
bin/main.o: src/main.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/main.o src/main.cpp

#Clean the build directory
clean:
	rm -f bin/*