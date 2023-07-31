#pragma once
#include <random>

namespace antares {
	inline void seedRandom(unsigned int seed) { srand(seed); }
	inline int random() { return rand(); }
	inline int random(unsigned int max) { return random() % max; }
	inline int random(unsigned int min, unsigned int max) { return min + random(max - min + 1); }
	inline int randomex(unsigned int min, unsigned int max) { return min + random(max - min); }

	inline float randomf() { return (float)random() / RAND_MAX; }
	inline float randomf(float max) { return randomf() * max; }
	inline float randomf(float min, float max) { 
		//original code here was giving me warnings for data loss so I looked up a better one on stack overflow
		float random = ((float)rand()) / (float)RAND_MAX;
		float range = max - min;
		return (random * range) + min;
	}
}