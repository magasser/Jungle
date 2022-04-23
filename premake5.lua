workspace "Jungle"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Jungle"
	location "Jungle"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "jnglpch.h"
	pchsource "Jungle/src/jnglpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"JNGL_PLATFORM_WINDOWS",
			"JNGL_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "JNGL_CFG_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "JNGL_CFG_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "JNGL_CFG_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Jungle/src",
		"Jungle/vendor/spdlog/include"
	}

	links
	{
		"Jungle"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"JNGL_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "JNGL_CFG_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "JNGL_CFG_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "JNGL_CFG_DIST"
		optimize "On"
