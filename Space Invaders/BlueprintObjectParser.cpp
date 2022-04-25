#include "BlueprintObjectParser.h"
#include "ObjectTags.h"
#include <iostream>
#include <fstream>

void BlueprintObjectParser::ParseNextObjectForBlueprint(ifstream& reader, GameObjectBlueprint& bp) {
	string lineFromFile;
	string value = "";

	while (getline(reader, lineFromFile)) {
		if (lineFromFile.find(ObjectTags::COMPONENT) != string::npos) {
			value = ExtractStringBetweenTags(lineFromFile, ObjectTags::COMPONENT, ObjectTags::COMPONENT_END);
			bp.AddToComponentList(value);
		}
		else if (lineFromFile.find(ObjectTags::NAME) != string::npos) {
			value = ExtractStringBetweenTags(lineFromFile, ObjectTags::NAME, ObjectTags::NAME_END);
			bp.SetName(value);
		}
		else if (lineFromFile.find(ObjectTags::WIDTH) != string::npos) {
			value = ExtractStringBetweenTags(lineFromFile, ObjectTags::WIDTH, ObjectTags::WIDTH_END);
			bp.SetWidth(stof(value));
		}
		else if (lineFromFile.find(ObjectTags::HEIGHT) != string::npos) {
			value = ExtractStringBetweenTags(lineFromFile, ObjectTags::HEIGHT, ObjectTags::HEIGHT_END);
			bp.SetHeight(stof(value));
		}
		else if (lineFromFile.find(ObjectTags::LOCATION_X) != string::npos) {
			value = ExtractStringBetweenTags(lineFromFile, ObjectTags::LOCATION_X, ObjectTags::LOCATION_X_END);
			bp.SetLocationX(stof(value));
		}
		else if (lineFromFile.find(ObjectTags::LOCATION_Y) != string::npos) {
			value = ExtractStringBetweenTags(lineFromFile, ObjectTags::LOCATION_Y, ObjectTags::LOCATION_Y_END);
			bp.SetLocationY(stof(value));
		}
		else if (lineFromFile.find(ObjectTags::BITMAP_NAME) != string::npos) {
			value = ExtractStringBetweenTags(lineFromFile, ObjectTags::BITMAP_NAME, ObjectTags::BITMAP_NAME_END);
			bp.SetBitmapName(value);
		}
		else if (lineFromFile.find(ObjectTags::ENCOMPASSING_RECT_COLLIDER) != string::npos) {
			value = ExtractStringBetweenTags(lineFromFile, ObjectTags::ENCOMPASSING_RECT_COLLIDER, ObjectTags::ENCOMPASSING_RECT_COLLIDER_END);
			bp.SetEncompassingRectCollider(value);
		}
		else if (lineFromFile.find(ObjectTags::END_OF_OBJECT) != string::npos) {
			return;
		}
	}
}

string BlueprintObjectParser::ExtractStringBetweenTags(string stringToSearch, string startTag, string endTag) {
	int start = startTag.length();
	int count = stringToSearch.length() - startTag.length() - endTag.length();

	string stringBetweenTags = stringToSearch.substr(start, count);

	return stringBetweenTags;
}