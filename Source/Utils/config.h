#ifndef CONFIG_H
#define CONFIG_H

#include <fstream>
#include <sstream>

class HorsemanConfig {
public:
	HorsemanConfig() {}
	~HorsemanConfig() {}

	bool LoadHorsemanConfig(const char * path) {
		NearDraw = 0.1f;
		FarDraw = 100.0f;

		std::ifstream configStream(path, std::ios::in);

		if (configStream.is_open()) {
			string line;
			while (std::getline(configStream, line)) {
				std::istringstream iss(line);
				string gb;
				if (line.find("fieldOfView") != string::npos) { iss >> gb >> FOV; }
				else if (line.find("screenWidth") != string::npos) { iss >> gb >> ScreenWidth; }
				else if (line.find("screenHeight") != string::npos) { iss >> gb >> ScreenHeight; }
				else if (line.find("displayMode") != string::npos) { iss >> gb >> DisplayMode; }
				else if (line.find("engineAssetsDir") != string::npos) { iss >> gb >> EngineAssets; }
			}
			configStream.close();
		}
		else {
			printf("Horseman Config Load Error [%s]: Config file could not be loaded.\n", path);
			return false;
		}

		return true;
	}

public:
	float FOV, ScreenWidth, ScreenHeight, NearDraw, FarDraw;
	string EngineAssets;
	int DisplayMode;
};

#endif
