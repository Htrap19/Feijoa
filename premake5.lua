workspace "Feijoa"
	architecture "x86_64"
	startproject "Sellowiana"

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
IncludeDir["entt"] = "Feijoa/vendor/entt/include"
IncludeDir["Assimp"] = "Feijoa/vendor/Assimp/assimp/include"

group "Dependencies"
	include "Feijoa/vendor/GLFW"
	include "Feijoa/vendor/Glad"
	include "Feijoa/vendor/imgui"
	include "Feijoa/vendor/Assimp"

group ""

include "Feijoa"
include "Sandbox"
include "Sellowiana"