workspace "CVNT"
	architecture "x86_64"
	startproject "Playground"
	staticruntime "on"
	language "C++"
	cppdialect "C++20"
	
	targetdir ("%{wks.location}/Binaries/%{prj.name}/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}")
	objdir ("%{wks.location}/Binaries/%{prj.name}/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}")
	
	configurations
	{
		"Debug",
		"Release"
	}
	
	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
	}
	
	includedirs
	{
		"%{wks.location}/Include",
	}
	
	filter "system:windows"
		systemversion "latest"
		
	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Release"
		runtime "Release"
		optimize "on"
		
project "Network"
	location "Source"
	kind "StaticLib"
	
	files
	{
		"Source/**.c",
		"Source/**.cpp",
		"Include/**/**.h",
		"Include/**/**.hpp"
	}
	
include "Examples"