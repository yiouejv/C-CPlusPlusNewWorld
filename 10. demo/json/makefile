target = app
header = $(wildcard include/*.h)
src = $(wildcard src/*.cpp)
obj = $(patsubst %cpp,%o,$(src))

$(target): $(header) $(obj)
	g++ $^ -o $@ -std=c++11

%o:%c
	g++ $< -c -std=c++11

test:
	echo $(obj)

.PHYNO:clean
clean:
	rm */*.o app
