#include "World.h"
#include "Components/Transform.h"

#define BOOST_TEST_MODULE MyTest
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(my_test)
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

	// EntityID recycling
	world.RemoveEntity(ent2);
	EntityID ent3 = world.CreateEntity();
	BOOST_CHECK(ent2 == ent3);
}