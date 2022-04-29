include "premake/solution_items.lua"

workspace "Jungle"
	architecture "x64"
	configurations { "Debug", "Release", "Dist" }

	workspace_files
	{
		".gitignore",
		"premake5.lua",
		"README.md"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["spdlog"] =	"Jungle/vendor/spdlog/include"
IncludeDir["GLFW"] =	"Jungle/vendor/GLFW/include"
IncludeDir["GLAD"] =	"Jungle/vendor/GLAD/include"
IncludeDir["GLM"] =		"Jungle/vendor/GLM"
IncludeDir["ImGui"] =	"Jungle/vendor/ImGui"

include "Jungle/vendor/GLFW"
include "Jungle/vendor/GLAD"
include "Jungle/vendor/ImGui"

project "Jungle"
	location "Jungle"
	kind "SharedLib"
	language "C++"
	cppdialect "C++20"

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
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.GLM}",
		"%{IncludeDir.ImGui}"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNIGNS"
	}

	links
	{
		"GLFW",
		"GLAD",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		staticruntime "on"
		systemversion "latest"

		defines
		{
			"JNGL_PLATFORM_WINDOWS",
			"JNGL_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "JNGL_CFG_DEBUG"
		buildoptions "/MDd"
		symbols "on"

		defines
		{
			"JNGL_ENABLE_ASSERTS"
		}

	filter "configurations:Release"
		defines "JNGL_CFG_RELEASE"
		buildoptions "/MD"
		optimize "on"

	filter "configurations:Dist"
		defines "JNGL_CFG_DIST"
		buildoptions "/MD"
		optimize "on"

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
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.GLM}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"Jungle"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "on"
		systemversion "latest"

		defines
		{
			"JNGL_PLATFORM_WINDOWS",
			"IMGUI_API=__declspec(dllimport)"
		}

	filter "configurations:Debug"
		defines "JNGL_CFG_DEBUG"
		buildoptions "/MDd"
		symbols "on"

	filter "configurations:Release"
		defines "JNGL_CFG_RELEASE"
		buildoptions "/MD"
		optimize "on"

	filter "configurations:Dist"
		defines "JNGL_CFG_DIST"
		buildoptions "/MD"
		optimize "on"
