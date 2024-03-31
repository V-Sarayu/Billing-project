a.exe: main.o customer.o  bill.o
    gcc -o billing main.o customer.o  bill.o

main.o: main.c
    gcc -c -o main.o main.c

customer.o: customer.c
    gcc -c -o customer.o customer.c

bill.o: bill.c
    gcc -c -o bill.o bill.c

clean:
    rm -f billing main.o customer.o  bill.o
