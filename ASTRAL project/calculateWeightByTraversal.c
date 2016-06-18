#include "calculateWeightByTraversal.h"
#include <limits.h>
#include <stdio.h>
#define INPUT_DATA_LENGTH 30

//testing purposes only. getside will probably use a read only memory

struct Intersects * getSide(int in, struct Intersects * side) {
	if (in == 1 || in == 6) {
		side->s0 = 1;
		side->s1 = 0;
		side->s2 = 0;
	}
	else if (in == 3 || in == 5 || in == 8) {
		side->s0 = 0;
		side->s1 = 1;
		side->s2 = 0;
	}
	else if (in == 2 || in == 4 || in == 7) {
		side->s0 = 0;
		side->s1 = 0;
		side->s2 = 1;
	}
	return side;
}

//for intersections
addIntersects(struct Intersects * augend, struct Intersects * addend, struct Intersects * result) {
	result->s0 = augend->s0 + addend->s0;
	result->s1 = augend->s1 + addend->s1;
	result->s2 = augend->s2 + addend->s2;
}
subtractIntersects(struct Intersects * minuend, struct Intersects * subtrahend, struct Intersects * result) {
	result->s0 = minuend->s0 - subtrahend->s0;
	result->s1 = minuend->s1 - subtrahend->s1;
	result->s2 = minuend->s2 - subtrahend->s2;
}

//for intersection stack
push(struct IntersectsStack * stack, struct Intersects * item) {
	stack->array[++(stack->currentIndex)].s0 = item->s0;
	stack->array[(stack->currentIndex)].s1 = item->s1;
	stack->array[(stack->currentIndex)].s2 = item->s2;
}

pop(struct IntersectsStack * stack, struct Intersects * item) {
	item->s0 = stack->array[stack->currentIndex].s0;
	item->s1 = stack->array[stack->currentIndex].s1;
	item->s2 = stack->array[stack->currentIndex--].s2;
}

poll(struct IntersectsStack * stack, struct Intersects * item) {
	item->s0 = stack->array[stack->currentIndex].s0;
	item->s1 = stack->array[stack->currentIndex].s1;
	item->s2 = stack->array[stack->currentIndex].s2;
}

clear(struct IntersectsStack * stack) {
	stack->currentIndex = -1;
}

//F function
long F(int a, int b, int c) {
	if (a < 0 || b < 0 || c < 0) {
		return -1;
	}
	long ret = (a + b + c - 3);
	return ret*a*b*c;
	
}

long calculateWeightByTraversal() {
	//for testing only. Input data is the post-order traversal integer representation
	int inputdata[INPUT_DATA_LENGTH] = {1,3,-2,6,-2,7,5,4,-2,-2,-2,8,2,-2,-2, INT_MIN, 3,1,-2,5,2,-2,6,7,4,-2,-2,-2,8,-2};

	//actual program
	long weight = 0;

	struct Intersects allsides;

	//should be set to 0 and be actually set in the if newtree statement. set to some values for testing purposes.
	allsides.s0 = 2;
	allsides.s1 = 3;
	allsides.s2 = 3;

	struct IntersectsStack stack;
	stack.currentIndex = -1;

	int newTree = 1;
	int counter = 0;

	for (; counter <= INPUT_DATA_LENGTH; counter++) {

		if (newTree) {
			newTree = 0;
		}
		if (inputdata[counter] >= 0) {
			struct Intersects side;
			push(&stack, getSide(inputdata[counter], &side));
		}
		else if (inputdata[counter] == INT_MIN) {
			clear(&stack);
			newTree = 1;
		}
		else if (inputdata[counter] == -2) {
			struct Intersects side1;
			struct Intersects side2;
			struct Intersects newSide;
			struct Intersects side3;

			pop(&stack, &side1);
			pop(&stack, &side2);
			
			addIntersects(&side1, &side2, &newSide);

			push(&stack, &newSide);

			subtractIntersects(&allsides, &newSide, &side3);

			weight += F(side1.s0, side2.s1, side3.s2) +
				F(side1.s0, side2.s2, side3.s1) +
				F(side1.s1, side2.s0, side3.s2) +
				F(side1.s1, side2.s2, side3.s0) +
				F(side1.s2, side2.s0, side3.s1) +
				F(side1.s2, side2.s1, side3.s0);
		}
	}
	return weight;
}