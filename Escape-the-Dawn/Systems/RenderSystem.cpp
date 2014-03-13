#include "RenderSystem.h"
#include "World.h"

void Systems::RenderSystem::OnComponentCreated( std::string type, std:: shared_ptr<Component> component )
{
	if(type == "Model")
	{
		auto modelComponent = std::static_pointer_cast<Components::Model>(component);
		
	}
}

void Systems::RenderSystem::UpdateEntity( double dt, EntityID entity, EntityID parent )
{
	auto transformComponent = m_World->GetComponent<Components::Transform>(entity, "Transform");
	if (transformComponent == nullptr)
		return;

	// Draw models
	auto modelComponent = m_World->GetComponent<Components::Model>(entity, "Model");
	if (modelComponent != nullptr)
	{
		if (m_CachedModels.find(modelComponent->ModelFile) == m_CachedModels.end()){
			m_CachedModels[modelComponent->ModelFile] = std::make_shared<Model>(OBJ(modelComponent->ModelFile));
		}

		auto model = m_CachedModels[modelComponent->ModelFile];
		m_Renderer->AddModelToDraw(model, transformComponent->Position, transformComponent->Orientation, transformComponent->Scale);
	}

	// Debug draw bounds
#ifdef DEBUG
	auto bounds = m_World->GetComponent<Components::Bounds>(entity, "Bounds");
	if (bounds != nullptr) {
		glm::vec3 origin = transformComponent->Position + (transformComponent->Scale * bounds->Origin);
		glm::vec3 volumeVector = transformComponent->Scale * bounds->VolumeVector;
		m_Renderer->AddAABBToDraw(origin, volumeVector, true);
	}
#endif

	auto pointLightComponent = m_World->GetComponent<Components::PointLight>(entity, "PointLight");
	if (pointLightComponent != nullptr)
	{
		m_Renderer->AddPointLightToDraw(
			transformComponent->Position, 
			pointLightComponent->Specular,
			pointLightComponent->Diffuse,
			pointLightComponent->constantAttenuation,
			pointLightComponent->linearAttenuation,
			pointLightComponent->quadraticAttenuation,
			pointLightComponent->spotExponent);
	}
	auto cameraComponent = m_World->GetComponent<Components::Camera>(entity, "Camera");
	if (cameraComponent != nullptr)
	{
		m_Renderer->GetCamera()->Position(transformComponent->Position);
		m_Renderer->GetCamera()->Orientation(transformComponent->Orientation);

		m_Renderer->GetCamera()->FOV(cameraComponent->FOV);
		m_Renderer->GetCamera()->NearClip(cameraComponent->NearClip);
		m_Renderer->GetCamera()->FarClip(cameraComponent->FarClip);
	}
}




