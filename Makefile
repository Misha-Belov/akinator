FLAGS=-Wshadow -Winit-self -Wredundant-decls -Wcast-align       \
	  -Wundef -Wfloat-equal -Winline -Wunreachable-code  		\
	  -Wmissing-declarations -Wmissing-include-dirs 			\
	  -Wswitch-enum -Wswitch-default -Weffc++ -Wmain 			\
	  -Wextra -Wall -g -pipe -fexceptions -Wcast-qual 			\
	  -Wconversion -Wctor-dtor-privacy -Wempty-body 			\
	  -Wformat-security -Wformat=2 -Wignored-qualifiers 		\
	  -Wlogical-op -Wno-missing-field-initializers 				\
	  -Wnon-virtual-dtor -Woverloaded-virtual 					\
	  -Wpointer-arith -Wsign-promo -Wstack-usage=8192 			\
	  -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits 	\
	  -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE

all: akinator

akinator: akinator.o define.o compare.o
	g++ akinator.o define.o compare.o -o akinator

akinator.: akinator.cpp akinator.h
	g++ $(FLAGS) -c akinator.cpp -o akinator.o

file.o: define.cpp akinator.h
	g++ $(FLAGS) -c define.cpp -o define.o

sort.o: compare.cpp akinator.h
	g++ $(FLAGS) -c compare.cpp -o compare.o
