all: compile_medium-1

compile_medium-1:
	g++ medium-1.cpp room_list.cpp reservation_list.cpp -o medium-1

test:
	./medium-1 reserve.in out1.out out2.out out3.out

clean:
	rm medium-1 out1.out out2.out out3.out
