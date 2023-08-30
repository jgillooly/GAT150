#pragma once
#include "SpriteComponent.h"
#include <string>
#include <map>

namespace antares {
	class SpriteAnimRenderComponent : public SpriteComponent {
	public:
		CLASS_DECLARATION(SpriteAnimRenderComponent);
		struct AnimSequence
		{
			std::string name;

			float fps = 0;
			int numColumns = 0;
			int numRows = 0;

			int startFrame = 0;
			int endFrame = 0;

			bool loop = true;

			std::shared_ptr<Texture> texture;
		};
		// Inherited via RenderComponent
		bool Initialize() override;
		void Update(float dt) override;

		void SetSequence(const std::string& name, bool sourceUpdate = true);
		void UpdateSource();

		void Draw(Renderer& renderer) override;
		//virtual float GetRadius() override { return m_texture->GetSize().Length() * 0.5f; }

	public:
		int frame = 0;
		float frameTimer = 0;
	private:
		std::string defaultSequenceName;
		std::map<std::string, AnimSequence> m_sequences;
		AnimSequence* m_sequence = nullptr;
	};
}