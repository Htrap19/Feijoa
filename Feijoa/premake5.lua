project "Feijoa"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "fjpch.h"
	pchsource "src/fjpch.cpp"

	files
	{
		"src/**.h",
		"src/**.cpp",
		"vendor/glm/**.hpp",
		"vendor/glm/**.inl",
		"vendor/stb_image/**.h",
		"vendor/stb_image/**.cpp"
	}

	includedirs
	{
		"src",
		"vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.yaml_cpp}"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE",
		"YAML_CPP_STATIC_DEFINE"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"yaml-cpp",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
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