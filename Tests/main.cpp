#include "World.h"
#include "Components/TransformComponent.h"

#define BOOST_TEST_MODULE World
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(Parenting)
{
	World world;
	
	// Parenting
	EntityID ent1 = world.CreateEntity();
	BOOST_CHECK(ent1 != 0); // 0 is reserved for world
	BOOST_CHECK(ent1 == 1);
	BOOST_CHECK(world.GetEntityParent(ent1) == 0);
	EntityID ent2 = world.CreateEntity(ent1);
	BOOST_CHECK(ent2 != 0);
	BOOST_CHECK(ent2 == ent1 + 1);
	BOOST_CHECK(world.GetEntityParent(ent2) == ent1);
}

BOOST_AUTO_TEST_CASE(SceneGraphTraversal)
{
	World world;

	EntityID ent1 = world.CreateEntity();
	auto t1 = world.AddComponent<Components::Transform>(ent1, "Transform");
	t1->Position[0] = 1.0f;
	t1->Position[1] = 1.0f;
	t1->Position[2] = 1.0f;
	EntityID ent2 = world.CreateEntity(ent1);
	auto t2 = world.AddComponent<Components::Transform>(ent2, "Transform");
	t2->Position[0] = 1.0f;
	t2->Position[1] = 1.0f;
	t2->Position[2] = 1.0f;

	world.Update(0.0);

	LOG_INFO("ent1: %f %f %f", t1->Position[0], t1->Position[1], t1->Position[2]);
	LOG_INFO("ent2: %f %f %f", t2->Position[0], t2->Position[1], t2->Position[2]);
}

BOOST_AUTO_TEST_CASE(Recycling)
{
	World world;

	// EntityID recycling
	EntityID ent11 = world.CreateEntity(); // 1
	world.RemoveEntity(ent11);
	EntityID ent12 = world.CreateEntity(); // 1
	BOOST_REQUIRE(ent11 == ent12);
}