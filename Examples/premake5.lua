group "Examples"
	project "Sever"
		location "Server"
		kind "ConsoleApp"
		
		files
		{
			"Server/**.h",
			"Server/**.hpp",
			"Server/**.c",
			"Server/**.cpp"
		}
		
		links
		{
			"Network"
		}
		
	project "Client"
		location "Client"
		kind "ConsoleApp"
		
		files
		{
			"Client/**.h",
			"Client/**.hpp",
			"Client/**.c",
			"Client/**.cpp"
		}
		
		links
		{
			"Network"
		}