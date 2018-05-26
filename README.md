# Editing Horseman
## Visual Studio Setup

1. Create empty solution
2. Import `Source/Msvc/Horseman.vcxproj`
3. Import `Tests/Source/Msvc/HorsemanTests.vcxproj`
4. Build Horseman first (Can only be built in x64 at this time)
5. Build HorsemanTest and run  (Can only be built in x64 at this time)

NOTE: You may have to change the Visual Studio project settings to have your Windows SDK and Visual Studio version. 

# Using Horseman
## Game Setup
*NOTE* You will need to go through step 4 of Editing Horseman to be able to use Horseman

### Directory Structure
Your directory should look like the one for HorsemanEngine itself
```
|
|- Assets
|- Docs
|- Lib
|- Source
|- Temp
```
1. Assets is where all assets should be placed and drawn from
1. Docs is documentation
1. Lib is where your game will build it's executables to
1. Source is where all the code lives
1. Temp is an intermediate dumping ground during the build process

## Link Horseman Engine
1. A file in the Source of your project will be a horseman_config.txt. (use template at root of this repo)
1. Edit assetsDir to the location of Assets from this project