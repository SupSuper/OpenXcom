/*
 * Copyright 2010 OpenXcom Developers.
 *
 * This file is part of OpenXcom.
 *
 * OpenXcom is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenXcom is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenXcom.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef OPENXCOM_MAP_H
#define OPENXCOM_MAP_H

#include "../Engine/InteractiveSurface.h"
#include <set>

namespace OpenXcom
{

class ResourcePack;
class SavedBattleGame;
class Timer;
class Surface;
class MapData;
class Position;
class Tile;
class BattleUnit;
class BulletSprite;
class Projectile;
class Explosion;
class BattlescapeMessage;

enum CursorType { CT_NONE, CT_NORMAL, CT_AIM, CT_PSI, CT_WAYPOINT, CT_THROW };

/**
 * Interactive map of the battlescape
 */
class Map : public InteractiveSurface
{
private:
	static const int SCROLL_BORDER = 5;
	static const int SCROLL_DIAGONAL_EDGE = 60;
	static const int SCROLL_INTERVAL = 50;
	Game *_game;
	SavedBattleGame *_save;
	ResourcePack *_res;
	Timer *_scrollTimer;
	Surface *_arrow;
	int _mapOffsetX, _mapOffsetY, _viewHeight;
	int _RMBClickX, _RMBClickY;
	int _spriteWidth, _spriteHeight;
	int _selectorX, _selectorY;
	CursorType _cursorType;
	int _animFrame;
	int _scrollX, _scrollY;
	bool _RMBDragging;
	int _centerX, _centerY;
	BulletSprite *_bullet[36];
	Projectile *_projectile;
	std::set<Explosion *> _explosions;
	bool _cameraFollowed;
	int _visibleMapHeight;
	BattlescapeMessage *_message;

	void minMaxInt(int *value, const int minValue, const int maxValue) const;
	void convertScreenToMap(int screenX, int screenY, int *mapX, int *mapY) const;
	void drawTerrain(Surface *surface);
public:
	/// Creates a new map at the specified position and size.
	Map(Game *game, int width, int height, int x, int y, int visibleMapHeight);
	/// Cleans up the map.
	~Map();
	/// sets stuff up
	void init();
	/// handle timers
	void think();
	/// draw the surface
	void draw();
	/// Sets the palette.
	void setPalette(SDL_Color *colors, int firstcolor = 0, int ncolors = 256);
	/// Special handling for mouse clicks.
	void mouseClick(Action *action, State *state);
	/// Special handling for mous over
	void mouseOver(Action *action, State *state);
	/// Special handling for key presses.
	void keyboardPress(Action *action, State *state);
	/// Scrolls the view (eg when mouse is on the edge of the screen)
	void scroll();
	/// rotate the tileframes 0-7
	void animate(bool redraw);
	/// move map layer up
	void up();
	/// move map layer down
	void down();
	/// set view height
	void setViewHeight(int viewheight);
	/// Center map on a unit.
	void centerOnPosition(const Position &pos, bool redraw = true);
	/// Converts map coordinates to screen coordinates.
	void convertMapToScreen(const Position &mapPos, Position *screenPos) const;
	/// Converts voxel coordinates to screen coordinates.
	void convertVoxelToScreen(const Position &voxelPos, Position *screenPos) const;
	/// Sets the battlescape selector position relative to mouseposition.
	void setSelectorPosition(int mx, int my);
	/// Get the currently selected position.
	void getSelectorPosition(Position *pos) const;
	/// Calculate the offset of a soldier, when it is walking in the middle of 2 tiles.
	void calculateWalkingOffset(BattleUnit *unit, Position *offset);
	/// Set the 3D cursor type.
	void setCursorType(CursorType type);
	/// Get the 3D cursor type.
	CursorType getCursorType() const;
	/// Cache units.
	void cacheUnits();
	/// Cache unit.
	void cacheUnit(BattleUnit *unit);
	/// Set projectile
	void setProjectile(Projectile *projectile);
	/// Get projectile
	Projectile *getProjectile() const;
	/// Get explosion set
	std::set<Explosion*> *getExplosions();
	/// Check if the camera was following a bullet.
	bool didCameraFollow();
	int getViewHeight() const;
	int getCenterX() const;
	int getCenterY() const;
};

}

#endif
