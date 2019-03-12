WORKSPACE SETTINGS VISUAL STUDIO 2017:

C/C++ GENERAL:$(SolutionDir)Dependencies\GLFW\include;$(SolutionDir)Dependencies\GLEW\include;$(SolutionDir)Dependencies\glm;$(SolutionDir)Dependencies\SDL\include;%(AdditionalIncludeDirectories)
C/C++ PREPROCESSOR:GLEW_STATIC;_MBCS;%(PreprocessorDefinitions)

LINKER GENERAL:$(SolutionDir)Dependencies\GLFW\lib-vc2015;$(SolutionDir)Dependencies\GLEW\lib\Release\Win32;$(SolutionDir)Dependencies\SDL\lib\x86;%(AdditionalLibraryDirectories)
LINKER INPUT:glew32s.lib;glfw3.lib;opengl32.lib;SDL2.lib;SDL2main.lib;%(AdditionalDependencies)