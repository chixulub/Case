#ifndef DRAGONSEGGS_HPP
#define DRAGONSEGGS_HPP
/*
 You have been hired by a dragon that is about to lay eggs. She wants to nest on a balcony on a highrise.
 But she () a dilemma. Since she is a dragon she wants the nest to be as high up as possible, but if an egg
 were to roll off the balcony she wants it to survive. She gives you two unfirtilized eggs to use as your test objects.

 Now.
 The building she have choosen has 100 floors.

 * How do you use the test eggs to find out the highest floor of the
 building from which an egg would survive a fall?

 * What is the lowest number of tests you can guarantee that you will find the floor in?

 */

#include <iostream>

constexpr static int NumFloors = 100;
constexpr static int N = 10;

int testLevel(int level) {
	int numTests    = 0; // How many eggs have we dropped so far.
	int lastTested  = 0; // Last floor dropped from.
	int lastHeld    = 0; // Last floor dropped from without breaking.
	int brokenFloor = 0; // The floor it broke from.
	int n           = 0; // The chunk to look for
	int testFloor   = 0; // The floor to test.

	// Find out in which vertical chunk to look for the floor.
	for(; n <= N; n++) {
		testFloor  = lastTested + (14 - n);
		lastTested = testFloor;
		numTests++;
		if(testFloor > level) {
			brokenFloor = testFloor;
			break;
		}

		lastHeld = testFloor;
	}

	if(n == N + 1) // We just survived from floor 99, final test tells us if the 100:th floor is safe. Sad for dragon if not :(
		return numTests + 1;
	else
		lastHeld++;

	// Find the floor by linear search up through the chunk.
	for(; lastHeld < brokenFloor; lastHeld++) {
		numTests++;
		if(lastHeld > level)
			break;
	}

	return numTests;
}

void confirm() {
	int total  = 0;
	int max    = 0;
	int i      = 1;
	int val    = 0;

	for(; i <= NumFloors; ++i) {
		val = testLevel(i);
		total += val;
		max = std::max(max,val);
		std::cout << "Floor " << i << ": " << val << " tests." << std::endl;
	}

	std::cout << "Mean = " << total/float(NumFloors) << std::endl;
	std::cout << "Worst = " << max << std::endl;
}

int main(int, char**) {
    confirm();
}


#endif // DRAGONSEGGS_HPP
