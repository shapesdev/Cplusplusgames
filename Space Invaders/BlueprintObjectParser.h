#pragma once
#include "GameObjectBlueprint.h"
#include <string>

using namespace std;

class BlueprintObjectParser
{
public:
	void ParseNextObjectForBlueprint(ifstream& reader, GameObjectBlueprint& bp);

private:
	string ExtractStringBetweenTags(string stringToSearch, string startTag, string endTag);
};

