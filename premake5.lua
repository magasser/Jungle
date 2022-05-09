include "premake/solution_items.lua"

workspace "Jungle"
	architecture "x64"
	startproject "JungleEditor"
	configurations { "Debug", "Profile", "Release", "Dist" }

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
IncludeDir["EnTT"] =	"Jungle/vendor/EnTT"
IncludeDir["ImGui"] =	"Jungle/vendor/ImGui"
IncludeDir["stb"] =		"Jungle/vendor/stb"

group "Dependencies"
	include "Jungle/vendor/GLFW"
	include "Jungle/vendor/GLAD"
	include "Jungle/vendor/ImGui"

group ""

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
		"%{prj.name}/src/**.cpp",

		"%{prj.name}/vendor/stb/**.h",
		"%{prj.name}/vendor/stb/**.cpp",

		"%{prj.name}/vendor/GLM/glm/**.hpp",
		"%{prj.name}/vendor/GLM/glm/**.inl",

		"%{prj.name}/vendor/EnTT/entt/**.hpp",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.GLM}",
		"%{IncludeDir.EnTT}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.stb}"
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
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox"),
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/JungleEditor")
		}

	filter "configurations:Debug"
		buildoptions "/MDd"
		symbols "on"

		defines
		{
			"JNGL_CFG_DEBUG",
			"JNGL_ENABLE_ASSERTS"
		}

	filter "configurations:Profie"
		buildoptions "/MDd"
		symbols "on"

		defines
		{
			"JNGL_CFG_DEBUG",
			"JNGL_ENABLE_ASSERTS",
			"JNGL_ENABLE_PROFILING"
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
	cppdialect "C++20"

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
		"%{IncludeDir.EnTT}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"Jungle"
	}

	filter "system:windows"
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

	filter "configurations:Profile"
		defines "JNGL_CFG_PROFILE"
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

project "JungleEditor"
	location "JungleEditor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"

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
		"%{IncludeDir.EnTT}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"Jungle"
	}

	filter "system:windows"
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

	filter "configurations:Profile"
		defines "JNGL_CFG_PROFILE"
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
