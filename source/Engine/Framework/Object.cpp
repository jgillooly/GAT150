#include "Object.h"

namespace antares {
	bool Object::Read(const rapidjson::Value & value) {
		READ_DATA(value, name);
		return true;
	}
}