#pragma once
#define STACK_SIZE 1000
long calculateWeightByTraversal();

struct Intersects {
	int s0;
	int s1;
	int s2;
};

addIntersects(struct Intersects * augend, struct Intersects * addend, struct Intersects * result);
subtractIntersects(struct Intersects * minuend, struct Intersects * subtrahend, struct Intersects * result);

struct IntersectsStack {
	struct Intersects array [STACK_SIZE] ;
	int currentIndex;
};

push(struct IntersectsStack * stack, struct Intersects * item);
pop(struct IntersectsStack * stack, struct Intersects * item);
poll(struct IntersectsStack * stack, struct Intersects * item);
clear(struct IntersectsStack * stack);
