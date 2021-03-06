workspace "ChappyEngine"
	architecture "x64"
	
	configurations {
		"Debug",
		"Release",
		"Dist"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "ChappyEngine/vendors/GLFW/include"
IncludeDir["GLAD"] = "ChappyEngine/vendors/GLAD/include"
IncludeDir["ImGui"] = "ChappyEngine/vendors/imgui"

include "ChappyEngine/vendors/GLFW"
include "ChappyEngine/vendors/GLAD"
include "ChappyEngine/vendors/ImGui"

project "ChappyEngine"
	location "ChappyEngine"
	kind "SharedLib"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "cepch.h"
	pchsource "ChappyEngine/src/cepch.cpp"
	
	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
		
	}
	
	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/vendors/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.ImGui}"

	}
	
	links {
		"GLFW",
		"GLAD",
		"ImGui",
		"opengl32.lib"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines {
			"CE_PLATFORM_WINDOWS",
			"CE_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}
		
		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
		
	filter "configurations:Debug"
		defines "CE_DEBUG"
		buildoptions "/MDd"
		symbols "On"
		
	filter "configurations:Release"
		defines "CE_RELEASE"
		buildoptions "/MD"
		optimize "On"
		
	filter "configurations:Dist"
		defines "CE_DIST"
		buildoptions "/MD"
		optimize "On"
	
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
		
	}
	
	includedirs {
		"ChappyEngine/vendors/spdlog/include",
		"ChappyEngine/src"
	}
	
	links {
		"ChappyEngine"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines {
			"CE_PLATFORM_WINDOWS"
		}
		
	filter "configurations:Debug"
		defines "CE_DEBUG"
		buildoptions "/MDd"
		symbols "On"
		
	filter "configurations:Release"
		defines "CE_RELEASE"
		buildoptions "/MD"
		optimize "On"
		
	filter "configurations:Dist"
		defines "CE_DIST"
		buildoptions "/MD"
		optimize "On"