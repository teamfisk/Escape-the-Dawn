#ifndef RenderSystem_h__
#define  RenderSystem_h__

#include "System.h"
#include "Model.h"
#include "Texture.h"
#include "Components/Model.h"
#include "Components/Transform.h"
#include "Renderer.h"
#include <unordered_map>

namespace Systems
{

	class  RenderSystem : public System
	{
	public:
		RenderSystem(World* world, std::shared_ptr<Renderer> renderer)
			: System(world), m_Renderer(renderer) {}

		std::unordered_map<std::string, Model*> m_CachedModels;

		void OnComponentCreated(std::string type, std::	shared_ptr<Component> component) override;
		void UpdateEntity(double dt, EntityID entity, EntityID parent) override;

	private:
		std::shared_ptr<Renderer> m_Renderer;

	};


}




#endif //RenderSystem_h__