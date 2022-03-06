#pragma once

#include "Scene.h"

namespace Hazel
{
	class SceneSerializer
	{
	public:
		SceneSerializer(const std::shared_ptr<Scene>& scene);
		~SceneSerializer() = default;

        void Serialize(const std::string& filepath);
        void SerializeRuntime(const std::string& filepath);

        bool Deserialize(const std::string& filepath);
        bool DeserializeRuntime(const std::string& filepath);

	private:
		std::shared_ptr<Scene> m_Scene;
	};

} // namespace Hazel