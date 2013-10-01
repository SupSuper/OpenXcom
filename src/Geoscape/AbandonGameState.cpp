/*
 * Copyright 2010-2013 OpenXcom Developers.
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
#include "AbandonGameState.h"
#include <sstream>
#include "../Engine/Game.h"
#include "../Resource/ResourcePack.h"
#include "../Engine/Language.h"
#include "../Engine/Palette.h"
#include "../Interface/TextButton.h"
#include "../Interface/Window.h"
#include "../Interface/Text.h"
#include "../Savegame/SavedGame.h"
#include "../Menu/MainMenuState.h"
#include "../Engine/Options.h"
#include "../Menu/SaveState.h"

namespace OpenXcom
{

/**
 * Initializes all the elements in the Abandon Game screen.
 * @param game Pointer to the core game.
 */
AbandonGameState::AbandonGameState(Game *game) : State(game)
{
	_screen = false;

	// Create objects
	_window = new Window(this, 216, 160, 20, 20, POPUP_BOTH);
	_btnYes = new TextButton(50, 20, 38, 140);
	_btnNo = new TextButton(50, 20, 168, 140);
	_txtTitle = new Text(206, 15, 25, 70);

	// Set palette
//	_game->setPalette(_game->getResourcePack()->getPalette("BACKPALS.DAT")->getColors(Palette::blockOffset(0)), Palette::backPos, 16);
	bool isGeoscape = game->getSavedGame()->getSavedBattle() == 0;
	Uint8 color = isGeoscape? Palette::blockOffset(15)-1 : Palette::blockOffset(0);

	add(_window);
	add(_btnYes);
	add(_btnNo);
	add(_txtTitle);

	centerAllSurfaces();

	// Set up objects
	_window->setColor(color);
	_window->setBackground(_game->getResourcePack()->getSurface(isGeoscape? "BACK01.SCR" : "TAC00.SCR"));

	_btnYes->setColor(color);
	_btnYes->setText(tr("STR_YES"));
	_btnYes->onMouseClick((ActionHandler)&AbandonGameState::btnYesClick);
	_btnYes->onKeyboardPress((ActionHandler)&AbandonGameState::btnYesClick, (SDLKey)Options::getInt("keyOk"));

	_btnNo->setColor(color);
	_btnNo->setText(tr("STR_NO"));
	_btnNo->onMouseClick((ActionHandler)&AbandonGameState::btnNoClick);
	_btnNo->onKeyboardPress((ActionHandler)&AbandonGameState::btnNoClick, (SDLKey)Options::getInt("keyCancel"));

	_txtTitle->setColor(color);
	_txtTitle->setAlign(ALIGN_CENTER);
	_txtTitle->setBig();

	if (!isGeoscape)
	{
		_window->setHighContrast(true);
		_btnYes->setHighContrast(true);
		_btnNo->setHighContrast(true);
		_txtTitle->setHighContrast(true);
	}

	std::wstringstream ss;
	ss << tr("STR_ABANDON_GAME_QUESTION");
	_txtTitle->setText(ss.str());
}

/**
 *
 */
AbandonGameState::~AbandonGameState()
{

}

/**
 * Goes back to the Main Menu.
 * @param action Pointer to an action.
 */
void AbandonGameState::btnYesClick(Action *)
{
	if (Options::getInt("autosave") == 3)
	{
		SaveState *ss = new SaveState(_game, true, false);
		delete ss;
	}

	_game->setState(new MainMenuState(_game));
	_game->setSavedGame(0);
}

/**
 * Closes the window.
 * @param action Pointer to an action.
 */
void AbandonGameState::btnNoClick(Action *)
{
	_game->popState();
}

}
