all: bTree

bTree: bTree.o bTreeNode.o bTree_main.o
	g++ -o bTree bTree.o bTreeNode.o bTree_main.o

bTree.o: bTree.cpp bTree.h
	g++ -c bTree.cpp

bTreeNode.o: bTreeNode.cpp bTreeNode.h
	g++ -c bTreeNode.cpp

bTree_main.o: bTree_main.cpp bTree.h bTreeNode.h
	g++ -c bTree_main.cpp

clean:
	rm bTree bTree.o bTreeNode.o bTree_main.o
