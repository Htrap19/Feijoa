workspace "Fejioa"
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
IncludeDir["GLFW"] = "Fejioa/vendor/GLFW/include"
IncludeDir["Glad"] = "Fejioa/vendor/Glad/include"
IncludeDir["ImGui"] = "Fejioa/vendor/imgui"
IncludeDir["glm"] = "Fejioa/vendor/glm"
IncludeDir["stb_image"] = "Fejioa/vendor/stb_image"

group "Dependencies"
	include "Fejioa/vendor/GLFW"
	include "Fejioa/vendor/Glad"
	include "Fejioa/vendor/imgui"

group ""

project "Fejioa"
	location "Fejioa"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "fjpch.h"
	pchsource "Fejioa/src/fjpch.cpp"

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
		"Fejioa/vendor/spdlog/include",
		"Fejioa/src",
		"Fejioa/vendor/",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Fejioa"
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
