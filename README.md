#Dependencies

1. glew - 2.1.0
1. glfw - 3.2.1
1. glm - 0.9.8.5

#First time setup
1. Create Lib directory at top level
1. Ensure glew32.dll is in %SystemRoot%
1. Organize the structure of Source/External as follows:
	1. glew-2.1.0
		1. <Extract glew 2.1.0 zip here>
	1. glfw-3.2.1
		1. include
		1. libs
			1. Win32
				1. <Win32 Binaries>
			1. x64
				1. <64 Bit Binaries>
	1. glm
		1. <Extract glm zip here>