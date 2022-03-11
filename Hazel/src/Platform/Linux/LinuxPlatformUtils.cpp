#include <pch.h>
#include "src/Utils/PlatformUtils.h"
#include "src/Core/Application.h"

#include <nfd.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_X11
#include <GLFW/glfw3native.h>

namespace Hazel {

    std::string FileDialogs::OpenFile(const char* filter)
    {
        std::string ret;
        NFD_Init();
        nfdchar_t *outPath;
        nfdfilteritem_t filterItem[2] = {{ "Hazel Scene", "hazel" }};
        nfdresult_t result = NFD_OpenDialog(&outPath, filterItem, 1, NULL);
        if (result == NFD_OKAY)
        {
            puts("Success!");
            puts(outPath);
            ret = std::string(outPath);
            NFD_FreePath(outPath);
        }
        else 
        {
            printf("Error: %s\n", NFD_GetError());
            ret = std::string();
        }

        NFD_Quit();

        return ret;
    }

    std::string FileDialogs::SaveFile(const char* filter)
    {
        std::string ret;
        NFD_Init();
        nfdchar_t *outPath;
        nfdfilteritem_t filterItem[2] = {{ "Hazel Scene", "hazel" }};
        nfdresult_t result = NFD_SaveDialog(&outPath, filterItem, 1, NULL, NULL);
        if (result == NFD_OKAY)
        {
            puts("Success!");
            puts(outPath);
            ret = std::string(outPath);
            NFD_FreePath(outPath);
        }
        else 
        {
            printf("Error: %s\n", NFD_GetError());
            ret = std::string();
        }

        NFD_Quit();

        return ret;
    }


}