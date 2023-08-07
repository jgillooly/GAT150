#include "Texture.h"
#include "Renderer.h"
#include "Core/Logger.h"
#include <SDL2-2.28.1/include/SDL_image.h>

namespace antares {
	Texture::~Texture() {
		if (m_texture) SDL_DestroyTexture(m_texture);
	}
	bool Texture::Load(const std::string& filename, class Renderer& renderer) {
		SDL_Surface* surface = IMG_Load(filename.c_str());
		if (!surface) {
			WARNING_LOG("File not found" << filename);
			return false;
		}
		m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);
		SDL_FreeSurface(surface);
		if (!m_texture) {
			WARNING_LOG("Texture creation failure using " << filename);
			return false;
		}
		return true;
	}
	vec2 Texture::GetSize() {
		ASSERT_LOG(m_texture, "Texture is null!!!");
		SDL_Point point;
		// https://wiki.libsdl.org/SDL2/SDL_QueryTexture
		SDL_QueryTexture(m_texture, NULL, NULL, &point.x, &point.y);
		return vec2{ point.x, point.y};
	}
	bool Texture::Create(std::string filename, ...) {
		va_list args;

		va_start(args, filename);

		Renderer& renderer = va_arg(args, Renderer);

		va_end(args);

		return Load(filename, renderer);
	}
}
