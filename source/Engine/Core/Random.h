#pragma once
#include <random>

namespace antares {
	inline void seedRandom(unsigned int seed) { srand(seed); }
	inline int random() { return rand(); }
	inline int random(unsigned int max) { return random() % max; }
	inline int random(unsigned int min, unsigned int max) { return min + random(max - min + 1); }
	inline int randomex(unsigned int min, unsigned int max) { return min + random(max - min); }

	inline float randomf() { return (float)random() / RAND_MAX; }
	inline float randomf(float max) { return randomf() + random(max); }
	inline float randomf(float min, float max) { return randomf() + randomex(min, max); }
}