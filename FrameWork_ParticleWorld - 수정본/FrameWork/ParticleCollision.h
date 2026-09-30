#pragma once
#include "plinks.h"
#include "particle.h"
#include <vector>
namespace cyclone {
	class ParticleCollision : public ParticleLink
	{
	public:
		/**
		* Holds the length of the rod.
		*/

	public:
		/**
		* Fills the given contact structure with the contact needed
		* to keep the rod from extending or compressing.
		*/
		virtual unsigned addContact(ParticleContact* contact,
			unsigned limit) const;
	};
}
