#include "SpriteAnimRenderComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"
#include "Framework/Resource/ResourceManager.h"

namespace antares {
	CLASS_DEFINITION(SpriteAnimRenderComponent);

	bool SpriteAnimRenderComponent::Initialize() {
		SpriteComponent::Initialize();

		SetSequence(defaultSequenceName, false);
		if (source.w == 0 && source.h == 0) {
			UpdateSource();
		}
		return true;
	}

	void SpriteAnimRenderComponent::Update(float dt) {
		frameTimer -= dt;
		if (frameTimer <= 0) {
			frameTimer = 1.0f / m_sequence->fps;
			frame++;
		}
		if (frame > m_sequence->endFrame) frame = (m_sequence->loop ? m_sequence->startFrame : m_sequence->endFrame);
		UpdateSource();
	}

	void SpriteAnimRenderComponent::SetSequence(const std::string& name, bool sourceUpdate) {
		//prevent setting to current sequence
		if (m_sequence && m_sequence->name == name) return;
		//check for finding sequence
		if (m_sequences.find(name) != m_sequences.end()) {
			//set new sequence
			m_sequence = &m_sequences[name];
			//set texture
			if (m_sequence->texture) m_texture = m_sequence->texture;
			//set frame info
			frame = m_sequence->startFrame;
			frameTimer = 1.0f / m_sequence->fps;
		}
		if (sourceUpdate) UpdateSource();
	}

	void SpriteAnimRenderComponent::UpdateSource() {
		vec2 cellsize = m_texture->GetSize() / vec2{m_sequence->numColumns, m_sequence->numRows};
		int column = (frame - 1) % m_sequence->numColumns;
		int row = (frame - 1) / m_sequence->numColumns;

		//Set source
		source.x = (int)(column * cellsize.x);
		source.y = (int)(row * cellsize.y);
		source.w = (int)(cellsize.x);
		source.h = (int)(cellsize.y);
	}

	void SpriteAnimRenderComponent::Draw(Renderer& renderer) {
		renderer.DrawTexture(m_texture.get(), source, m_owner->transform, origin, flipH);
	}

	void SpriteAnimRenderComponent::Read(const json_t& value) {
		SpriteComponent::Read(value);
		READ_NAME_DATA(value, "defaultSequence", defaultSequenceName);
		// read in animation sequences
		if (HAS_DATA(value, sequences) && GET_DATA(value, sequences).IsArray()) {
			for (auto& sequenceValue : GET_DATA(value, sequences).GetArray()) {
				AnimSequence sequence;

				READ_NAME_DATA(sequenceValue, "name", sequence.name);
				READ_NAME_DATA(sequenceValue, "fps", sequence.fps);
				READ_NAME_DATA(sequenceValue, "numColumns", sequence.numColumns);
				READ_NAME_DATA(sequenceValue, "numRows", sequence.numRows);
				READ_NAME_DATA(sequenceValue, "startFrame", sequence.startFrame);
				READ_NAME_DATA(sequenceValue, "endFrame", sequence.endFrame);

				// read texture
				std::string textureName;
				READ_DATA(sequenceValue, textureName);
				sequence.texture = GET_RESOURCE(Texture, textureName, g_renderer);

				m_sequences[sequence.name] = sequence;
			}
		}

		if (!READ_NAME_DATA(value, "defaultSequence", defaultSequenceName)) {
			// if default sequence not specified, use the first sequence in the sequences map
			defaultSequenceName = m_sequences.begin()->first;
		}
	}
}