#ifndef CLEGINE_CORE_UUID_HPP
#define CLEGINE_CORE_UUID_HPP

#include <EntryPoint.hpp>

namespace Clegine {
	class UUID : public Singleton<UUID>{
	public:
		UUID() = default;
		~UUID() = default;

		void Generate() = default;
	};
}

#endif // CLEGINE_CORE_UUID_HPP