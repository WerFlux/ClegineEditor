#ifndef CLEGINE_CORE_SINGLETON_HPP
#define CLEGINE_CORE_SINGLETON_HPP

namespace Clegine {
	template<class T>
	class Singleton {
	public:
		Singleton() = default;
		~Singleton() = default;

		inline static T& Get()
		{
			static T Instance;
			return Instance;
		}
	private:
		Singleton(const Singleton&) = delete;
		Singleton& operator=(const Singleton&) = delete;
	};
}

#endif // CLEGINE_CORE_SINGLETON_HPP