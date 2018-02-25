pgm3: template.o
	g++ -o pgm3 template.o
template.o: template.cc LList.cc LList.h Reg.cc BST4.cc BST4.h BinaryTree4.h BinaryTree4.cc
	g++ -g -c template.cc
clean:
	rm -rf *.o
	rm -rf core
	rm -rf pgm3
