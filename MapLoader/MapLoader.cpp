#include <fstream>
#include <string>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include "MapLoader.h"
#include "../Map/Map.h"
#include "../Map/Continent.h"
#include "../Map/Country.h"

using namespace std;

MapLoader::MapLoader() {
}

MapLoader::MapLoader(string textFileName) {
    parseMap(textFileName);
}

// Helper function for getting whole lines without carriage returns
string MapLoader::readLine(ifstream &fileReader) {
    string line;
    if (getline(fileReader, line)) {
        return this->strip(line);
    } else {
        return "";
    }
}

// Helper function to strip \r or \n at the right end of the string
string MapLoader::strip(string s) {
    while (s[s.length() - 1] == '\r' || s[s.length() - 1] == '\n') {
        s.pop_back();
    }

    return s;
}

// Helper function to split strings
vector<string> MapLoader::split(string s, char delim) {
    stringstream ss(s);
    string input;
    vector<string> result;

    while (getline(ss, input, delim)) {
        result.push_back(input);
    }

    return result;
}

Map MapLoader::getMap() {
    return loadedMap;
}

void MapLoader::parseMap(string textFileName) {
    string line;
    ifstream fileReader(textFileName);
    Map gameMap;

    // Verify that [Map] exists but skip over it to continents
    if ((line = this->readLine(fileReader)) != "[Map]") {
        throw invalid_argument("Map file is invalid, missing [Map] section.");
    }

    while ((line = this->readLine(fileReader)) != "[Continents]" && !fileReader.eof()) {}

    // Parse the continents until we reach territories
    if (line != "[Continents]") {
        throw invalid_argument("Map file is invalid, missing [Continents] section.");
    }

    while ((line = this->readLine(fileReader)) != "[Territories]" && !fileReader.eof()) {
        vector<string> continentInfo = this->split(line, '=');

        // Only parse valid lines with format [continent]=[value]
        if (continentInfo.size() == 2) {
            Continent* continent;
            try {
                continent = new Continent(stoi(continentInfo[1]), continentInfo[0]);
            } catch (invalid_argument e) {
                throw invalid_argument("Expected integer value for continent but got something else.");
            }
            gameMap.addContinent(continent);
        }
    } 

    // Parse the territories until the end of the map file
    if (line != "[Territories]") {
        throw invalid_argument("Map file is invalid, missing [Territories] section.");
    }

    // Add bordering country names to a 2d vector so we can add them once all countries are initialized
    vector<vector<string> > borderingCountries;

    line = this->readLine(fileReader);
    while (!fileReader.eof()) {
        if (line != "") {
            vector<string> countryInfo = this->split(line, ',');

            if (countryInfo.size() > 4) {
                Country* country = new Country(countryInfo[0], countryInfo[3]);

                // Add country to it's respective continent
                bool addedToContinent = false;
                for (int i = 0; i < gameMap.getContinents().size(); i++) {
                    if (gameMap.getContinents()[i]->getName() == countryInfo[3]) {
                        addedToContinent = true;
                        gameMap.getContinents()[i]->addCountry(country);
                        break;
                    }
                }

                if (!addedToContinent) {
                    throw invalid_argument("Map file is invalid, continent for country '" + countryInfo[0] + "' does not exist.");
                }

                gameMap.addCountry(country);

                // Add bordering countries for later processing
                vector<string> bordering;
                for (int i = 4; i < countryInfo.size(); i++) {
                    bordering.push_back(countryInfo[i]);
                }
                borderingCountries.push_back(bordering);
            } else {
                throw invalid_argument("Map file is invalid, missing properties for a territory.");
            }
        }

        line = this->readLine(fileReader);
    }

    // Go over every country and add the proper bordering countries
    for (int countryIndex = 0; countryIndex < borderingCountries.size(); countryIndex++) {
        for (int borderingCountryIndex = 0; borderingCountryIndex < borderingCountries[countryIndex].size(); borderingCountryIndex++) {
            string borderingCountryName = borderingCountries[countryIndex][borderingCountryIndex];

            bool addedBorderingCountry = false;
            for (int allCountriesIndex = 0; allCountriesIndex < gameMap.getCountries().size(); allCountriesIndex++) {
                if (gameMap.getCountries()[allCountriesIndex]->getName() == borderingCountryName) {
                    addedBorderingCountry = true;
                    gameMap.getCountries()[countryIndex]->addBorderingCountry(gameMap.getCountries()[allCountriesIndex]);
                    break;
                }
            }
            
            if (!addedBorderingCountry) {
                throw invalid_argument("Map file is invalid, bordering country '" + borderingCountryName + "' "
                                       "for country '" + gameMap.getCountries()[countryIndex]->getName() + "' does not exist");
            }
        }
    }

    loadedMap = gameMap;
    fileReader.close();
}