#pragma once
#include <string>

namespace antares {
	class Resource {
	public:
		virtual ~Resource() = default;

		virtual bool Create(std::string filename, ...) = 0;
	protected:

	};
}