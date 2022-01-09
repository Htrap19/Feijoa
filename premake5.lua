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
IncludeDir["GLFW"] = "%{wks.location}/Feijoa/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/Feijoa/vendor/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/Feijoa/vendor/imgui"
IncludeDir["glm"] = "%{wks.location}/Feijoa/vendor/glm"
IncludeDir["stb_image"] = "%{wks.location}/Feijoa/vendor/stb_image"
IncludeDir["entt"] = "%{wks.location}/Feijoa/vendor/entt/include"
IncludeDir["yaml_cpp"] = "%{wks.location}/Feijoa/vendor/yaml-cpp/include"

group "Dependencies"
	include "Feijoa/vendor/GLFW"
	include "Feijoa/vendor/Glad"
	include "Feijoa/vendor/imgui"
	include "Feijoa/vendor/yaml-cpp"

group ""

include "Feijoa"
include "Sandbox"
include "Sellowiana"