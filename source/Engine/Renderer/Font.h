#pragma once
#include <string>
#include "Framework/Resource/Resource.h"
struct _TTF_Font;
namespace antares {
	class Font : public Resource
	{
	public:
		Font() = default;
		Font(const std::string& filename, int fontSize);
		~Font();
		bool Load(const std::string& filename, int fontSize);
		virtual bool Create(std::string filename, ...) override;
		friend class Text;
	private:
		_TTF_Font* m_ttfFont = nullptr;

		// Inherited via Resource
	};
}