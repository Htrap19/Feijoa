project "Sellowiana"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"%{wks.location}/Feijoa/vendor/spdlog/include",
		"%{wks.location}/Feijoa/src",
		"%{wks.location}/Feijoa/vendor/",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.ImGuizmo}",
		"%{IncludeDir.Assimp}"
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