CFLAGS  += -D INCLUDEMAIN
headers = $(wildcard *.h)
sources = $(wildcard *.c)
objects = $(patsubst %.c,%.o,$(sources))

# program : $(objects)
# 	cc -c -o program $(objects)
	
$(objects) : $(headers)


.PHONY : clean cleanobj
clean : cleanobj
	rm program

cleanobj : 
	rm *.o
