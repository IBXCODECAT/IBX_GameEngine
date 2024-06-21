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

-- Include the premake5.lua file in the GLFW project (almost like a c++ style include)
include "IBX_Engine/vendor/GLFW"
include "IBX_Engine/vendor/Glad"

project "Sandbox"
    location "Sandbox"

    -- Console Application
    kind "ConsoleApp"

    language "C++"

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
        symbols "On"
    
    -- Only applies to the release configuration (for any platform)
    filter "configurations:Release"
        defines "IBX_RELEASE"
        optimize "On"
    
    -- Only applies to the dist configuration (for any platform)
    filter "configurations:Dist"
        defines "IBX_DIST"
        optimize "On"

project "IBX_Engine"
    location "IBX_Engine"
    
    -- SharedLib is *.dll Library
    kind "SharedLib"
    language "C++"

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
    }

    -- Link Libraries
    links
    {
        -- Link the GLFW project
        "GLFW",

        -- Link the Glad project
        "Glad",

        "opengl32.lib"
    }

    -- The following only applies to windows until another filter is reached
    filter "system:windows"
        -- 
        cppdialect "C++17"

        -- Has to do with linking runtime libraries
        staticruntime "On"

        -- Premake will Default to Windows 8.1 SDK, this ensures it will use the latest sdk version
        systemversion "latest"

        -- Defines or Preprosessor Directives
        defines
        {
            "IBX_PLATFORM_WINDOWS",
            "IBX_BUILD_DLL",
            "GLFW_INCLUDE_NONE" -- Prevents GLFW from including OpenGL headers
        }

        -- After we build the project run the following
        postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputDir .. "/Sandbox/\"")
		}

    -- Only applies to the debug configuration (for any platform)
    filter "configurations:Debug"
        defines "IBX_DEBUG"
        symbols "On"
        buildoptions "/MDd" -- /MDd for dynamic linking debug
    
    -- Only applies to the release configuration (for any platform)
    filter "configurations:Release"
        defines "IBX_RELEASE"
        optimize "On"
        buildoptions "/MD" -- /MD for dynamic linking
    
    -- Only applies to the dist configuration (for any platform)
    filter "configurations:Dist"
        defines "IBX_DIST"
        optimize "On"
        buildoptions "/MD" -- /MD for dynamic linking