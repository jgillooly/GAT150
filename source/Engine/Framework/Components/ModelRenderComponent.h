#pragma once
#include "RenderComponent.h"
#include "Renderer/Model.h"
namespace antares {
	class ModelRenderComponent : public RenderComponent {
	public:
		// Inherited via RenderComponent
		void Update(float dt) override;

		void Draw(Renderer& renderer) override;
	public:
		res_t<Model> m_model;
	};
}