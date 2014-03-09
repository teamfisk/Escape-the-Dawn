#include "RenderSystem.h"
#include "World.h"



void Systems::RenderSystem::OnComponentCreated( std::string type, std:: shared_ptr<Component> component )
{
	if(type == "Model")
	{
		auto modelComponent = std::static_pointer_cast<Components::Model>(component);
		
		if (m_CachedModels.find(modelComponent->ModelFile) != m_CachedModels.end()) {
			m_CachedModels[modelComponent->ModelFile] = new Model(modelComponent->ModelFile);
		}
	}
}

void Systems::RenderSystem::UpdateEntity( double dt, EntityID entity, EntityID parent )
{
	auto modelComponent = m_World->GetComponent<Components::Model>(entity, "Model");
	if (modelComponent == nullptr)
		return;
	auto transformComponent = m_World->GetComponent<Components::Transform>(entity, "Transform");
	if (transformComponent == nullptr)
		return;

	Model* model = m_CachedModels[modelComponent->ModelFile];
	m_Renderer->AddModelToDraw(model, transformComponent->Position, transformComponent->Orientation);
}




