#pragma once
#include <string>
#include <fstream>
#include "Textures.h"
#include "debug.h"
#include "Sprites.h"

#define MAX_MAP_LINE			1024
#define MAP_TEXTURE				30
#define EXTRA_TILE				6

class CMap {
	int column, row = 0;
	int tileSize = 0;
	int tileColumn, tileRow = 0;
	// Map matrix
	vector<vector<int>> tiles;
	// Util for parsing from text.
	int currentRow = 0;
	// Map Tiles texture
	LPTEXTURE tex = NULL;

	int offsetW, offsetH;	// number of tile need to render
	int width, height;
	int isVertical = -1;

	void _LoadMapTiles();
	void _ParseSection_MapTile(string line);
	void _ParseSection_Info(string line);
public:
	CMap(wstring path);
	~CMap();

	int getMapWidth() { return width; }
	int getMapHeight() { return height; }
	void Load(wstring path);
	void Render();
	bool IsVertical();
};