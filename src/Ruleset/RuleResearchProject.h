/*
 * Copyright 2011 OpenXcom Developers.
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
#ifndef OPENXCOM_RULRESEARCHPROJECT_H
#define OPENXCOM_RULRESEARCHPROJECT_H

#include <string>
#include <vector>

namespace OpenXcom
{
/**
   Represent one research project
*/
class RuleResearchProject
{
 private:
	std::string _name;
	std::wstring _description;
	int _cost;
	std::vector<RuleResearchProject *> _dependencys;
	bool _discovered;
	bool _needItem;
public:
	RuleResearchProject(const std::string & name, int cost);
	bool isAvailable () const;
	void addDependency (RuleResearchProject * rp);
	bool isDiscovered () const;
	int getCost() const;
	void setDiscovered (bool b);
	const std::string & getName () const;
	const std::vector<RuleResearchProject *> & getDependencys () const;
	bool needItem() const;
	void setNeedItem(bool b);
};

}

#endif
