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
#ifndef OPENXCOM_SELLSTATE_H
#define OPENXCOM_SELLSTATE_H

#include "../Engine/State.h"
#include "../Menu/OptionsBaseState.h"
#include "PurchaseState.h"
#include <vector>
#include <string>

namespace OpenXcom
{

class TextButton;
class Window;
class Text;
class TextList;
class Timer;
class Base;
class Soldier;
class Craft;
class ItemContainer;

/**
 * Sell/Sack screen that lets the player sell
 * any items in a particular base.
 */
class SellState : public State
{
private:
	Base *_base;
	TextButton *_btnOk, *_btnCancel, *_btnTab, *_btnPrev, *_btnNext;
	Window *_window;
	Text *_txtTitle, *_txtSales, *_txtFunds, *_txtItem, *_txtQuantity, *_txtSell, *_txtValue, *_txtSpace, *_txtSpaceUsed;
	TextList *_lstPersonnel, *_lstCraft, *_lstItems;
	TextList *_selList;
	std::vector< std::vector<int> > _quantities;
	std::vector<Soldier*> _soldiers;
	std::vector<Craft*> _crafts;
	std::vector< std::vector<std::string> > _items;
	std::vector<std::wstring> _tabs;
	std::vector<TextList*> _lists;
	std::vector<ItemContainer*> _containers;
	unsigned int _sel;
	size_t _selTab;
	int _total, _spaceChange;
	Timer *_timerInc, *_timerDec;
	ItemContainer *_tItems;
	bool _haveTransferItems;
	Uint8 _color, _color2, _color3, _colorAmmo;
	/// Gets selected price.
	int getPrice();
	/// Gets selected quantity.
	int getQuantity();
	/// Gets the index of selected item.
	int getItemIndex(unsigned selected) const;
	/// Updates the tab index.
	void updateIndex(size_t &index, std::vector<std::wstring> &list, int change);
	/// Adds item rows to the tab for the items in the container.
	void addRows(ItemContainer *container, int tab);
	/// Updates the displayed tab.
	void updateTab(int direction = 0);
	/// Changes the quantity of an item by the given value.
	void changeByValue(int change, int dir);
	/// Increases the quantity of an item by one.
	void increase();
	/// Decreases the quantity of an item by one.
	void decrease();
	/// Updates the quantity-strings, row colors and storage change.
	void updateUI();
public:
	/// Creates the Sell state.
	SellState(Game *game, Base *base, OptionsOrigin origin = OPT_GEOSCAPE);
	/// Cleans up the Sell state.
	~SellState();
	/// Runs the timers.
	void think();
	/// Handler for clicking the OK button.
	void btnOkClick(Action *action);
	/// Handler for clicking the Cancel button.
	void btnCancelClick(Action *action);
	/// Handler for clicking the Tab button.
	void btnTabClick(Action *action);
	/// Handler for clicking the Previous button.
	void btnPrevClick(Action *action);
	/// Handler for clicking the Next button.
	void btnNextClick(Action *action);
	/// Handler for pressing an Increase arrow in the list.
	void lstItemsLeftArrowPress(Action *action);
	/// Handler for releasing an Increase arrow in the list.
	void lstItemsLeftArrowRelease(Action *action);
	/// Handler for clicking an Increase arrow in the list.
	void lstItemsLeftArrowClick(Action *action);
	/// Handler for pressing a Decrease arrow in the list.
	void lstItemsRightArrowPress(Action *action);
	/// Handler for releasing a Decrease arrow in the list.
	void lstItemsRightArrowRelease(Action *action);
	/// Handler for clicking a Decrease arrow in the list.
	void lstItemsRightArrowClick(Action *action);
	/// Handler for pressing-down a mouse-button in the list.
	void lstItemsMousePress(Action *action);
};

}

#endif
