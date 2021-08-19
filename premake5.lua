workspace "Fejioa"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Fejioa/vendor/GLFW/include"
IncludeDir["Glad"] = "Fejioa/vendor/Glad/include"
IncludeDir["ImGui"] = "Fejioa/vendor/imgui"
IncludeDir["glm"] = "Fejioa/vendor/glm"

include "Fejioa/vendor/GLFW"
include "Fejioa/vendor/Glad"
include "Fejioa/vendor/imgui"

project "Fejioa"
	location "Fejioa"
	kind "SharedLib"
	language "C++"
	staticruntime "Off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "fjpch.h"
	pchsource "Fejioa/src/fjpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/**.hpp",
		"%{prj.name}/vendor/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"FJ_PLATFORM_WINDOWS",
			"FJ_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

		filter "configurations:Debug"
			defines "FJ_DEBUG"
			runtime "Debug"
			symbols "On"

		filter "configurations:Release"
			defines "FJ_RELEASE"
			runtime "Release"
			optimize "On"

		filter "configurations:Dist"
			defines "FJ_DIST"
			runtime "Release"
			optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "Off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Fejioa/vendor/spdlog/include",
		"Fejioa/src",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Fejioa"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"FJ_PLATFORM_WINDOWS"
		}

		filter "configurations:Debug"
			defines "FJ_DEBUG"
			buildoptions "/MDd"
			symbols "On"

		filter "configurations:Release"
			defines "FJ_RELEASE"
			buildoptions "/MD"
			optimize "On"

		filter "configurations:Dist"
			defines "FJ_DIST"
			buildoptions "/MD"
			optimize "On"