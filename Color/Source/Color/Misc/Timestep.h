#pragma once

namespace Color
{
	// Structure representing the step of time between two events. Used extensively for delta time within the engine.
	struct Timestep
	{
		// The time in seconds.
		float Time = 0.0f;

		Timestep() = default;
		Timestep(const Timestep&) = default;
		Timestep& operator=(const Timestep&) = default;
		Timestep(float time)
			: Time(time) { }

		operator float() const { return Time; }
		float operator()() const { return Time; }
	};
}
