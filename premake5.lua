workspace "IBX"
    architecture "x64"
    
    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

ENGINE_NAME = "IBX_Engine"

-- Include Directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "IBX_Engine/vendor/GLFW/include"
IncludeDir["Glad"] = "IBX_Engine/vendor/Glad/include"
IncludeDir["ImGui"] = "IBX_Engine/vendor/ImGui"
IncludeDir["glm"] = "IBX_Engine/vendor/glm"
IncludeDir["stb_image"] = "IBX_Engine/vendor/stb_image"

-- Include the premake5.lua file in the GLFW project (almost like a c++ style include)
include "IBX_Engine/vendor/GLFW"
include "IBX_Engine/vendor/Glad"
include "IBX_Engine/vendor/ImGui"

project "Sandbox"
    location "Sandbox"

    -- Console Application
    kind "ConsoleApp"

    -- C++ Language Settings and Standard
    language "C++"
    cppdialect "C++17"

    -- Has to do with linking runtime libraries
    -- Should not be used for dynamic libraries because dynamic linking requires runtime libraries prelinked (can't be static runtime)
    staticruntime "on"

    -- Output directory for our binary
    targetdir ("bin/" ..outputDir .. "/%{prj.name}")

    -- Intermediates output directory
    objdir ("bin-int/" ..outputDir .. "/%{prj.name}")

    -- Defines the files to include
    files
    {
        -- Recursive search for *.h files in source directory
        "%{prj.name}/src/**.h",

        -- Recursive search for *.cpp files in source directory
        "%{prj.name}/src/**.cpp",
    }

    -- Include directories
    includedirs
    {
        -- Include the source directory (prevents ../../ in includes)
        "%{prj.name}/src",
        
        -- Include spdlog
        "" .. ENGINE_NAME .. "/vendor/spdlog/include",

        -- Include IBX Engine
        "IBX_Engine/src/",

        "IBX_Engine/vendor/",

        -- Include glm
        "%{IncludeDir.glm}",
    }

    -- Defines or Preprocessor Directives
    defines
    {
        "IBX_PLATFORM_WINDOWS"
    }

    -- Link IBX_Engine.dll as a reference
    links
    {
        "IBX_Engine",
    }

    -- Only applies to the debug configuration (for any platform)
    filter "configurations:Debug"
        defines "IBX_DEBUG"
        symbols "on"
    
    -- Only applies to the release configuration (for any platform)
    filter "configurations:Release"
        defines "IBX_RELEASE"
        optimize "on"
    
    -- Only applies to the dist configuration (for any platform)
    filter "configurations:Dist"
        defines "IBX_DIST"
        optimize "on"


-- ======================================================== IBX Engine Project ======================================================== --

project "IBX_Engine"
    location "IBX_Engine"
    
    -- SharedLib is *.dll Library
    -- StaticLib is *.lib Library
    kind "StaticLib"
    
    -- C++ Language Settings and Standard
    language "C++" 
    cppdialect "C++17"

    -- Has to do with linking runtime libraries
    -- Should not be used for dynamic libraries because dynamic linking requires runtime libraries prelinked (can't be static runtime)
    staticruntime "on"

    -- Output directory for our binary
    targetdir ("bin/" ..outputDir .. "/%{prj.name}")

    -- Intermediates output directory
    objdir ("bin-int/" ..outputDir .. "/%{prj.name}")

    -- Precompiled Headers (PCH)
    pchheader "ibxpch.h"
    pchsource "IBX_Engine/src/ibxpch.cpp"

    -- Defines the files to include
    files
    {
        -- Recursive search for *.h files in source directory
        "%{prj.name}/src/**.h",

        -- Recursive search for *.cpp files in source directory
        "%{prj.name}/src/**.cpp",

        --------------------------------- Vendor ---------------------------------

        -- STB Image --
        "%{prj.name}/vendor/stb_image/**.h",
        "%{prj.name}/vendor/stb_image/**.cpp",

        -- GLM --
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl"
    }

    defines
    {
        -- Suppresses warnings for the CRT Secure Warnings
        "_CRT_SECURE_NO_WARNINGS"
    }

    -- Include directories
    includedirs
    {
        -- Include the source directory (prevents ../../ in includes)
        "%{prj.name}/src",
        
        -- Include spdlog
        "%{prj.name}/vendor/spdlog/include",

        -- Include GLFW
        "%{IncludeDir.GLFW}",

        -- Include Glad
        "%{IncludeDir.Glad}",

        -- Include ImGui
        "%{IncludeDir.ImGui}",

        -- Include glm
        "%{IncludeDir.glm}",

        -- Include stb_image
        "%{IncludeDir.stb_image}"
    }

    -- Link Libraries
    links
    {
        -- Link the GLFW project
        "GLFW",

        -- Link the Glad project
        "Glad",

        -- Link the ImGui project
        "ImGui",

        "opengl32.lib"
    }

    -- The following only applies to windows until another filter is reached
    filter "system:windows"

        -- Has to do with linking runtime libraries
        staticruntime "on"

        -- Premake will Default to Windows 8.1 SDK, this ensures it will use the latest sdk version
        systemversion "latest"

        -- Defines or Preprosessor Directives
        defines
        {
            "IBX_PLATFORM_WINDOWS",
            "IBX_BUILD_DLL",
            "GLFW_INCLUDE_NONE" -- Prevents GLFW from including OpenGL headers
        }

    -- Only applies to the debug configuration (for any platform)
    filter "configurations:Debug"
        defines "IBX_DEBUG"
        symbols "on"
    
    -- Only applies to the release configuration (for any platform)
    filter "configurations:Release"
        defines "IBX_RELEASE"
        optimize "on"
    
    -- Only applies to the dist configuration (for any platform)
    filter "configurations:Dist"
        defines "IBX_DIST"
        optimize "on"