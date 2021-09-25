workspace "Feijoa"
	architecture "x86_64"
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
IncludeDir["GLFW"] = "Feijoa/vendor/GLFW/include"
IncludeDir["Glad"] = "Feijoa/vendor/Glad/include"
IncludeDir["ImGui"] = "Feijoa/vendor/imgui"
IncludeDir["glm"] = "Feijoa/vendor/glm"
IncludeDir["stb_image"] = "Feijoa/vendor/stb_image"

group "Dependencies"
	include "Feijoa/vendor/GLFW"
	include "Feijoa/vendor/Glad"
	include "Feijoa/vendor/imgui"

group ""

project "Feijoa"
	location "Feijoa"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "fjpch.h"
	pchsource "Feijoa/src/fjpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/**.hpp",
		"%{prj.name}/vendor/glm/**.inl",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"FJ_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		filter "configurations:Debug"
			defines "FJ_DEBUG"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			defines "FJ_RELEASE"
			runtime "Release"
			optimize "on"

		filter "configurations:Dist"
			defines "FJ_DIST"
			runtime "Release"
			optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Feijoa/vendor/spdlog/include",
		"Feijoa/src",
		"Feijoa/vendor/",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Feijoa"
	}

	filter "system:windows"
		systemversion "latest"

		filter "configurations:Debug"
			defines "FJ_DEBUG"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			defines "FJ_RELEASE"
			runtime "Release"
			optimize "on"

		filter "configurations:Dist"
			defines "FJ_DIST"
			runtime "Release"
			optimize "on"