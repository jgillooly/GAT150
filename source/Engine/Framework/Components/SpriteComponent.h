#pragma once
#include "RenderComponent.h"
#include "Renderer/Texture.h"
#include "Framework/Factory.h"
#include <string>
namespace antares {
	class SpriteComponent : public RenderComponent {
	public:
		CLASS_DECLARATION(SpriteComponent);
		// Inherited via RenderComponent
		bool Initialize() override;
		void Update(float dt) override;

		void Draw(Renderer& renderer) override;
		virtual float GetRadius() override { return m_texture->GetSize().Length()*0.5f; }

	public:
		res_t<Texture> m_texture;
		std::string textureName = "";
		Rect source;
		bool flipH = false;
		vec2 origin{ 0.5f, 0.5f };
	};
}