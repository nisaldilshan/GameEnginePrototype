#include <pch.h>

namespace Hazel
{
    std::filesystem::path getAssetPath()
    {
        static std::filesystem::path assetPath = "assets";
        return assetPath;
    }
}