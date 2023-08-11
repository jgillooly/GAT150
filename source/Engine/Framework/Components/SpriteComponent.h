#pragma once
#include "RenderComponent.h"
#include "Renderer/Texture.h"
namespace antares {
	class SpriteComponent : public RenderComponent {
	public:
		// Inherited via RenderComponent
		void Update(float dt) override;

		void Draw(Renderer& renderer) override;
		float GetRadius() override { return m_texture->GetSize().Length()*0.5f; }
	public:
		res_t<Texture> m_texture;

	};
}