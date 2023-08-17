#pragma once
#include "RenderComponent.h"
#include "Renderer/Model.h"
#include <string>
namespace antares {
	class ModelRenderComponent : public RenderComponent {
	public:
		CLASS_DECLARATION(ModelRenderComponent);
		// Inherited via RenderComponent
		bool Initialize() override;
		void Update(float dt) override;

		void Draw(Renderer& renderer) override;
		float GetRadius() override { return m_model->GetRadius(); }
	public:
		std::string modelName;
		res_t<Model> m_model;
	};
}