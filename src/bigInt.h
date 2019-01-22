#ifndef BIG_INT_H
#define BIG_INT_H

enum {
	PLUS,
	MINUS	
};

typedef struct BigInt{
	int sign;
	int *arr;
};


#endif // BIG_INT_H
