////////////////////////////////////////////////////////////////////////
// Monster.cpp
// Super Mario Project
// Copyright (C) 2011  
// Lionel Joseph lionel.r.joseph@gmail.com
// Olivier Guittonneau openmengine@gmail.com
////////////////////////////////////////////////////////////////////////

#include "Monster.hpp"
#include <fstream>
#include <sstream>

namespace Collisions
{
    Monster::Monster(const string& textureName, bool canBeKilledByFire, bool canBeKilledByJump, bool canBeJumpedOn) 
        : Resource("textures/monsters/" + textureName),
        _canBeKilledByFire(canBeKilledByFire),
        _canBeKilledByJump(canBeKilledByJump),
        _canBeJumpedOn(canBeJumpedOn),
		_points(0)
    {
        loadMonster();
    }

	int Monster::getBottomLeft()
	{
		return _bottomLeft;
	}

	bool Monster::getCanBeKilledByJump()
	{
		return _canBeKilledByJump;
	}

	bool Monster::getCanBeKilledByFire()
	{
		return _canBeKilledByFire;
	}

	bool Monster::getCanBeJumpedOn()
	{
		return _canBeJumpedOn;
	}

	vector<MonsterOccurrence*>& Monster::getMonsterOccurrences()
	{
		return _monsterOccurrences;
	}

	void Monster::addNewMonsterOccurrence(Vector2f& position, Vector2f& speed, MonsterOccurrence::State state, MonsterOccurrence::Side side)
    {
		_monsterOccurrences.push_back(new MonsterOccurrence(name(), position, speed, state, side, _nbSpritesByState, _frameDelayByState));
    }

    void Monster::removeMonsterOccurrence(const MonsterOccurrence* monster)
    {
        vector<MonsterOccurrence*>::iterator itMonsterOccurrence;

        for(itMonsterOccurrence = _monsterOccurrences.begin(); itMonsterOccurrence != _monsterOccurrences.end(); ++itMonsterOccurrence)
        {
            if((*itMonsterOccurrence) == monster)
                _monsterOccurrences.erase(itMonsterOccurrence);
        }
    }

    void Monster::loadMonster()
    {
        string fileName = name() + ".mstr";
        ifstream stream(fileName.c_str());

        if(stream)
        {
            string word;

            /* We read file to search the keyword and read his value */
            while(getline(stream, word))
            {
                int found = word.find("abscisse_bas=");
                if(found != string::npos)
                {
                    istringstream abscisseBas(word.substr(found + 13));
                    abscisseBas >> _bottomLeft;
                    continue;
                }

                found = word.find("can_be_jumped_on=");
                if(found != string::npos)
                {
                    istringstream canBeJumpedOn(word.substr(found + 17));
                    canBeJumpedOn >> _canBeJumpedOn;
                    continue;
                }

                found = word.find("can_be_killed_by_jump=");
                if(found != string::npos)
                {
                    istringstream canBeKilledByJump(word.substr(found + 21));
                    canBeKilledByJump >> _canBeKilledByJump;
                    continue;
                }

                found = word.find("can_be_killed_by_fire=");
                if(found != string::npos)
                {
                    istringstream canBeKilledByFire(word.substr(found + 21));
                    canBeKilledByFire >> _canBeKilledByFire;
                }

				found = word.find("points=");
                if(found != string::npos)
                {
                    istringstream points(word.substr(found + 7));
                    points >> _points;
                }
            }

        }
        else
        {
            string exceptionName = "Exception occured while opening " + fileName;
            throw exception(exceptionName.c_str());
        }
    }

    void Monster::update(RenderWindow& app)
    {
        vector<MonsterOccurrence*>::iterator itMonsters;

        /* MonsterOccurrences */
        for(itMonsters = this->_monsterOccurrences.begin(); itMonsters != this->_monsterOccurrences.end(); ++itMonsters)
        {
            (*itMonsters)->update(app);
        }
    }

    void Monster::render(RenderWindow& app)
    {
        vector<MonsterOccurrence*>::iterator itMonsters;

        /* MonsterOccurrences */
        for(itMonsters = this->_monsterOccurrences.begin(); itMonsters != this->_monsterOccurrences.end(); ++itMonsters)
        {
            (*itMonsters)->render(app);
        }
    }

    Monster::~Monster()
    {
        vector<MonsterOccurrence*>::iterator itMonsters;

        /* MonsterOccurrences */
        for(itMonsters = this->_monsterOccurrences.begin(); itMonsters != this->_monsterOccurrences.end(); ++itMonsters)
        {
            delete (*itMonsters);
        }

		release();
    }
} // namespace