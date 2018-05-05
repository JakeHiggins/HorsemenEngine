Visual Studio Configs:

General:
	Output Directory: 			$(SolutionDir)\Engine\Lib\$(PlatformName)$(Configuration)\
	Intermediate Directory:		$(SolutionDir)\Engine\Temp\$(ProjectName)$(PlatformName)$(Configuration)\
	Target Name:				$(ProjectName)$(PlatformName)$(Configuration)

VC++ Directories:
	Include Directories:		$(SolutionDir)\Engine\Source\External\include;$(IncludePath)
	Library Directories:		$(SolutionDir)\Engine\Source\External\lib;$(LibraryPath)
	Source Directories:			$(SolutionDir)\Engine\Source\;$(SourcePath);

C/C++:
	General:
		Additional Incude Directories:		$(SolutionDir)\Engine\Source\External\include;%(AdditionalIncludeDirectories)
	Preprocessor:
		Preprocessor Definitions:			_CRT_SECURE_NO_WARNINGS;_MBCS;%(PreprocessorDefinitions)    

Linker:
	General:
		Additional Library Dependencies:	$(SolutionDir)\Engine\Source\External\lib;%(AdditionalLibraryDirectories)
	Input:
		Additional Dependencies:			glew32.lib;glew32s.lib;glfw3.lib;glfw3dll.lib;OpenGL32.lib;%(AdditionalDependencies)