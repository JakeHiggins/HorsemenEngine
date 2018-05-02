Visual Studio Configs:

General:
	Output Directory: 			$(SolutionDir)..\..\Lib\$(PlatformName)$(Configuration)\
	Intermediate Directory:		$(SolutionDir)..\..\Temp\$(ProjectName)$(PlatformName)$(Configuration)\
	Target Name:				$(ProjectName)$(PlatformName)$(Configuration)

VC++ Directories:
	Include Directories:		$(SolutionDir)..\External\include;$(IncludePath)
	Library Directories:		$(SolutionDir)..\External\lib;$(LibraryPath)

C/C++:
	General:
		Additional Incude Directories:		$(SolutionDir)..\External\include;%(AdditionalIncludeDirectories)

Linker:
	General:
		Additional Library Dependencies:	$(SolutionDir)..\External\lib;%(AdditionalLibraryDirectories)
	Input:
		Additional Dependencies:			glew32.lib;glew32s.lib;glfw3.lib;glfw3dll.lib;OpenGL32.lib;%(AdditionalDependencies)