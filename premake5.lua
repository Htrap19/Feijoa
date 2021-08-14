workspace "Fejioa"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Fejioa"
	location "Fejioa"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "fjpch.h"
	pchsource "Fejioa/src/fjpch.cpp"

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
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"FJ_PLATFORM_WINDOWS",
			"FJ_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

		filter "configurations:Debug"
			defines "FJ_DEBUG"
			symbols "On"

		filter "configurations:Release"
			defines "FJ_RELEASE"
			optimize "On"

		filter "configurations:Dist"
			defines "FJ_DIST"
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
		"Fejioa/vendor/spdlog/include",
		"Fejioa/src"
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
			symbols "On"

		filter "configurations:Release"
			defines "FJ_RELEASE"
			optimize "On"

		filter "configurations:Dist"
			defines "FJ_DIST"
			optimize "On"