#include "ColorPCH.h"
#include "ECS.h"

#include "Misc/Random.h"

namespace Color
{
	namespace ECS
	{
		EntityID GenerateEntityID()
		{
			static RandomGenerator RNG = RandomGenerator::SeededWithTime();
			return RNG.Range<EntityID>();
		}
	}
}
