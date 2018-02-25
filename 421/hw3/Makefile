all: node client dios
node: node.c
	gcc -lm -o node node.c
client: client.c
	gcc -o client client.c
dios: dios.c
	gcc -o dios dios.c
clean:
	rm -f client node dios
runnodes:
	killall node
	./node sin &
	./node power &
	./node log &
	./node cos &
	./node tan &
