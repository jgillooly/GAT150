#pragma once
#include "MathUtils.h"
#include <cstdint>
#include <iostream>
#include <string>

namespace antares {
	class Color {
	public:
		float r, g, b, a;

	public:
		Color() : r{0}, g{0}, b{0}, a{0} {}
		Color(float r, float g, float b, float a = 1) : r{ r }, g{ g }, b{ b }, a{ a } {}

		float operator [] (size_t index) const { return (&r)[index]; }
		float& operator [] (size_t index) { return (&r)[index]; }

		static uint8_t toInt(float f) { return static_cast<uint8_t>(Clamp(f, 0.0f, 1.0f) * 255); }

	};

	inline std::istream& operator >> (std::istream& stream, Color& c) {
		std::string line;
		std::getline(stream, line);
		//{ #, #, # }

		std::string str = line.substr(line.find("{") + 1, line.find(",") - line.find("{") - 1);
		c.r = std::stof(str);

		line = line.substr(line.find(",") + 1);
		str = line.substr(1, line.find(",") - 1);
		c.g = std::stof(str);

		str = line.substr(line.find(",") + 2, line.find("}") - line.find(",") - 2);
		c.b = std::stof(str);

		c.a = 1;



		return stream;
	}
}