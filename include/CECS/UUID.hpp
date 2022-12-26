#ifndef CECS_UUID_HPP_0660
#define CECS_UUID_HPP_0660

#include <unordered_set>
#include <random>
#include <string>

namespace CECS {
	class UUIDPool {
	private:
		static std::unordered_set<std::string> uuidMap;
	public:
		static void Add(std::string& uuid) {
			uuidMap.insert(uuid);
		}
		static bool CheckCollision(std::string& uuid) {
			return uuidMap.count(uuid) > 0;
		}
	};
	std::unordered_set<std::string> UUIDPool::uuidMap;

	class UUID {
	private:
		std::string uuid;
		friend class UUIDPool;
	public:
		UUID() { uuid = Generate(); };
		UUID(const UUID& copy) : uuid(copy.uuid) { };

		std::string Get() noexcept { return uuid; }
	private:
		_NODISCARD std::string Generate() noexcept {
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<unsigned int> dis1;
			std::uniform_int_distribution<int> dis2('A', 'Z');

			while (true) {
				uuid = "UBI-";
				uuid += std::to_string(dis1(gen) % 100000);
				uuid += "-";
				for (int i = 0; i < 6; i++) {
					if (dis1(gen) % 2 == 0) {
						uuid += static_cast<char>('0' + dis1(gen) % 10);
					}
					else {
						uuid += static_cast<char>(dis2(gen));
					}
				}
				uuid += "-";
				for (int i = 0; i < 4; i++) {
					uuid += static_cast<char>('0' + dis1(gen) % 10);
				}
				uuid += "-";
				for (int i = 0; i < 3; i++) {
					uuid += static_cast<char>(dis2(gen));
				}

				if (!UUIDPool::CheckCollision(uuid)) {
					UUIDPool::Add(uuid);
					return uuid;
				}
			}
		}
	};
}

#endif // CECS_UUID_HPP_0660