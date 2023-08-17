#include "Object.h"

namespace antares {
	void Object::Read(const rapidjson::Value & value) {
		READ_DATA(value, name);
	}
}