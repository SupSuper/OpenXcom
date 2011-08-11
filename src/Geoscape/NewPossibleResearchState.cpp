#include "NewPossibleResearchState.h"
#include "../Engine/Game.h"
#include "../Engine/Palette.h"
#include "../Engine/Language.h"
#include "../Resource/ResourcePack.h"
#include "../Interface/TextButton.h"
#include "../Interface/Window.h"
#include "../Interface/Text.h"
#include "../Interface/TextList.h"
#include "../Ruleset/RuleResearchProject.h"

namespace OpenXcom
{
NewPossibleResearchState::NewPossibleResearchState(Game * game, Base * base, const std::vector<RuleResearchProject *> & possibilities) : State (game), _base(base)
{
	_screen = false;

	// Create objects
	_window = new Window(this, 280, 180, 20, 10, POPUP_BOTH);
	_btnOk = new TextButton(180, 13, 70, 150);
	_btnSelect = new TextButton(180, 13, 70, 165);
	_txtTitle = new Text(200, 30, 60, 30);
	_possibilities = new TextList(160, 80, 80, 60);

	// Set palette
	_game->setPalette(_game->getResourcePack()->getPalette("BACKPALS.DAT")->getColors(Palette::blockOffset(6)), Palette::backPos, 16);

	add(_window);
	add(_btnOk);
	add(_btnSelect);
	add(_txtTitle);
	add(_possibilities);

	// Set up objects
	_window->setColor(Palette::blockOffset(8)+8);
	_window->setBackground(_game->getResourcePack()->getSurface("BACK05.SCR"));

	_btnOk->setColor(Palette::blockOffset(8)+8);
	_btnOk->setText(_game->getLanguage()->getString("STR_OK"));
	_btnOk->onMouseClick((ActionHandler)&NewPossibleResearchState::btnOkClick);
	_btnSelect->setColor(Palette::blockOffset(8)+8);
	_btnSelect->setText(_game->getLanguage()->getString("STR_ALLOCATE_RESEARCH"));
	_btnOk->onMouseClick((ActionHandler)&NewPossibleResearchState::btnSelectClick);

	_txtTitle->setColor(Palette::blockOffset(8)+5);
	_txtTitle->setBig();
	_txtTitle->setAlign(ALIGN_CENTER);
	_txtTitle->setText(_game->getLanguage()->getString("STR_WE_CAN_NOW_RESEARCH"));

	_possibilities->setColor(Palette::blockOffset(8)+10);
	_possibilities->setArrowColor(Palette::blockOffset(8)+8);
	_possibilities->setColumns(1, 160);
	_possibilities->setSelectable(false);
	_possibilities->setBackground(_window);
	_possibilities->setMargin(2);
	_possibilities->setBig();
	_possibilities->setAlign(ALIGN_CENTER);
	for(std::vector<RuleResearchProject *>::const_iterator iter = possibilities.begin ();
	    iter != possibilities.end ();
	    iter++)
	{
		_possibilities->addRow (1, (*iter)->getName ().c_str());
	}
}

void NewPossibleResearchState::btnOkClick(Action *action)
{
}

void NewPossibleResearchState::btnSelectClick(Action *action)
{
}
}
