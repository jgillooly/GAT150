#pragma once
#include "RenderComponent.h"
#include "Renderer/Texture.h"
namespace antares {
	class SpriteComponent : public RenderComponent {
	public:
		// Inherited via RenderComponent
		void Update(float dt) override;

		void Draw(Renderer& renderer) override;
	public:
		res_t<Texture> m_texture;

	};
}