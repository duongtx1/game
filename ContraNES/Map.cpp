#include "Map.h"
#include "Game.h"
#include "Camera.h"

#define MAP_INFO_SECTION 1
#define MAP_TILE_SECTION 2
#define MAP_UNKNOWN_SECTION -1

CMap::CMap(wstring path)
{
	Load(path);
}

void CMap::Load(wstring path)
{
	ifstream f;
	f.open(path);

	// current resource section flag
	int section = MAP_UNKNOWN_SECTION;
	char str[MAX_MAP_LINE];
	while (f.getline(str, MAX_MAP_LINE)) {
		string line(str);
		if (line[0] == '#') continue;
		if (line == "[Info]") {
			section = MAP_INFO_SECTION;
			continue;
		}
		if (line == "[Map]") {
			section = MAP_TILE_SECTION;
			continue;
		}
		if (line[0] == '[') {
			section = MAP_UNKNOWN_SECTION;
			continue;
		}

		switch (section) {
		case MAP_INFO_SECTION:
			_ParseSection_Info(line);
			break;
		case MAP_TILE_SECTION:
			_ParseSection_MapTile(line);
			break;
		}
	}
	f.close();
	_LoadMapTiles();
}

void CMap::Render()
{
	D3DXVECTOR2 pos = Camera::GetInstance()->getCamPosition();
	int startX = (int)(pos.x / width * column - 2);
	int startY = (int)(pos.y / height * row);
	if (startX < 0) startX = 0;
	if (startY < 0) startY = 0;
	int endX = startX + offsetW > column ? column : startX + offsetW;
	int endY = startY + offsetH > row ? row : startY + offsetH;
	for (int i = startY; i < endY; i++) {
		for (int j = startX; j < endX; j++) {
			int id = tiles[i][j];
			CSprites::GetInstance()->Get(id)->Draw((float)(tileSize * j), (float)(tileSize * i));
		}
	}
}

bool CMap::IsVertical()
{
	return isVertical > 0;
}

void CMap::_ParseSection_MapTile(string line)
{
	vector<string> tokens = split(line);

	size_t size = tokens.size();
	if (size < column) return;
	for (int i = 0; i < column; i++) {
		tiles[currentRow][i] = atoi(tokens[i].c_str()) - 1;
	}
	currentRow++;
}

void CMap::_ParseSection_Info(string line)
{
	vector<string> tokens = split(line);
	size_t size = tokens.size();

	if (size < 6) return;
	row = atoi(tokens[0].c_str());
	column = atoi(tokens[1].c_str());
	tileRow = atoi(tokens[2].c_str());
	tileColumn = atoi(tokens[3].c_str());
	tileSize = atoi(tokens[4].c_str());
	isVertical = atoi(tokens[6].c_str());

	width = column * tileSize;
	height = row * tileSize;

	int texID = atoi(tokens[5].c_str());
	tex = CTextures::GetInstance()->Get(texID);

	// Resize the matrix to the size of the map with default value to zero
	tiles.resize(row, vector<int>(column, 0));

	offsetW = 40;// CGame::GetInstance()->GetBackBufferWidth() / tileSize + EXTRA_TILE;
	offsetH = 40;// CGame::GetInstance()->GetBackBufferHeight() / tileSize + EXTRA_TILE;
}

void CMap::_LoadMapTiles() {
	int id = 0;
	for (int i = 0; i < tileRow; i++)
	{
		for (int j = 0; j < tileColumn; j++)
		{
			RECT r;
			r.left = id % tileColumn * tileSize;
			r.top = (id / tileColumn) * tileSize;
			r.right = r.left + tileSize;
			r.bottom = r.top + tileSize;
			CSprites::GetInstance()->Add(id, r.left, r.top, r.right - 1, r.bottom - 1, tex);
			id++;
		}
	}
}

CMap::~CMap()
{
}