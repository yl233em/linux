.PHONY:all
all:libhello.so libhello.a

libhello.so:demo_d.o test_d.o
	gcc -shared demo_d.o test_d.o -o libhello.so
demo_d.o:demo.c
	gcc -c -fPIC demo.c -o demo_d.o
test_d.o:test.c
	gcc -c -fPIC test.c -o test_d.o

libhello.a:demo.o test.o
	ar -rc libhello.a demo.o test.o

demo.o:demo.c
	gcc -c demo.c -o demo.o 
test.o:test.c
	gcc -c test.c -o test.o

.PHONY:creat
creat:
	mkdir -p exec/lib
	mkdir -p exec/include
	cp -rf *.a exec/lib
	cp -rf *.so exec/lib
	cp -rf *.h exec/include

.PHONY:clean
clean:
	rm -rf *.o *.a *.so exec