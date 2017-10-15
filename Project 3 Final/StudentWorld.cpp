

#include "StudentWorld.h"
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

#include "Actor.h"

#include "Level.h"


GameWorld* createStudentWorld(string assetDir)
{
    return new StudentWorld(assetDir);
}

StudentWorld::StudentWorld(std::string assetDir)
: GameWorld(assetDir), m_hostages(0), m_jewels(0), m_subLevel(0), m_health (20), m_ammo(0), m_timeLeft(1500), m_finishedLevel(false)
{
}
// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp

int StudentWorld::getCurrentSubLevel()
{
    return m_subLevel;
}

void StudentWorld::setCurrentSubLevel (int l)
{
    m_subLevel = l;
}

int StudentWorld::init()
{
    for (int i = 0; i < MAX_SUB_LEVEL; i++)
    {
        ostringstream levelmaker; //set up file names
        if (getLevel() < 10)
            levelmaker << "level0" << getLevel(); //If level is less than 10, make sure there is a 0 before level digit in file name
        else
            levelmaker << "level" << getLevel();
        if (i == 0) //If loading a main level,
            levelmaker << ".dat";
        else //Loading a sublevel
            levelmaker << "_" << i << ".dat";
        string levelname = levelmaker.str();
        //cerr << levelname << endl;
        
        //Finished formatting file names
        Level lev(assetDirectory());
        Level::LoadResult result = lev.loadLevel(levelname, i);
        if (result == Level::load_fail_file_not_found)
            return GWSTATUS_PLAYER_WON;
        else if (result == Level::load_fail_bad_format || result == Level::load_sublevel_fail_bad_format)
            return GWSTATUS_LEVEL_ERROR;
        else if (result == Level :: load_success || result == Level :: load_sublevel_success)
        {
            cerr << "Successfully loaded level \n";
            vector<Actor*> tempActor;
            Player* tempPlayer;
            if (i == 0) //If loading main level, reset number of hostages and jewels
            {
                m_hostages = 0;
                m_jewels = 0;
                m_finishedLevel = false;
                m_ammo = 0;
                m_timeLeft = 1500;
                restoreHealth();
                if (getLevel() == 0) //If loading for the first time...
                {
                    increaseScore(-getScore());
                    setCurrentSubLevel(0);
                }
            }
            //Setting up map and allocating players
            for (int j = 0; j < 15; j++)
            {
                for (int k = 0; k < 15; k++)
                {
                    Level::MazeEntry ge = lev.getContentsOf (j,k,i);
                    switch (ge)
                    {
                        case Level::empty:
                            break;
                        case Level::exit:
                            tempActor.push_back(new Exit(this, j, k, i));
                            break;
                        case Level::player:
                            tempPlayer = new Player (this, j, k, i);
                            break;
                        case Level::horiz_snarlbot:
                            tempActor.push_back(new SnarlBot(this, j, k, i, Actor::right));
                            break;
                        case Level::vert_snarlbot:
                            tempActor.push_back(new SnarlBot(this, j, k, i, Actor::down));
                            break;
                        case Level::hostage:
                            tempActor.push_back(new Hostage(this, j, k, i));
                            m_hostages++;
                            break;
                        case Level::jewel:
                            tempActor.push_back(new Jewel(this, j, k, i));
                            m_jewels++;
                            break;
                        case Level::ammo:
                            tempActor.push_back(new Ammo(this, j, k, i));
                            break;
                        case Level::restore_health:
                            tempActor.push_back(new RestoreHealth(this, j, k, i));
                            break;
                        case Level::extra_life:
                            tempActor.push_back(new ExtraLife(this, j, k, i));
                            break;
                        case Level::wall:
                            tempActor.push_back(new Wall (this, j, k, i));
                            break;
                        case Level::kleptobot_factory:
                            tempActor.push_back(new KleptoFactory (this, j, k, i));
                        default:
                            if (ge >=0 && ge <= 5)
                                tempActor.push_back(new Gate (this, j, k, i, ge));
                            break;
                    }
                }
            }
            m_player.push_back(tempPlayer);
            m_actors.push_back(tempActor);
        }
    }
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    if (m_timeLeft > 0)
        m_timeLeft--;
    setDisplayText();
    if (!m_player[getCurrentSubLevel()]->isAlive() || m_timeLeft <= 0)
    {
        decLives(); // Called when player presses ESC (which calls setDead())
        restoreHealth();
        m_timeLeft = 1500;
        setCurrentSubLevel(0);
        return GWSTATUS_PLAYER_DIED;
    }
    else if (m_player[getCurrentSubLevel()]->isAlive())
    {
        int currentSize = m_actors[getCurrentSubLevel()].size();
        for (int i = 0; i < currentSize; i++)
        {
            Actor* obj = m_actors[getCurrentSubLevel()][i];
            if (obj->isAlive()) //If the object is alive, do something
            {
                if (obj->getID() == IID_GATE && getPlayer(obj->getX(), obj->getY()) != nullptr)
                {
                    obj->doSomething();
                    break;
                }
                obj->doSomething();
            }
        }
        m_player[getCurrentSubLevel()]->doSomething(); //Move the player
    }
    //Delete dead objects
    int subLevel = getCurrentSubLevel();
    for (size_t i=0; i < m_actors[subLevel].size();)
    {
        if (!m_actors[subLevel][i]->isAlive())
        {
            delete m_actors[subLevel][i];
            if (m_actors[subLevel].size() > 1)
                m_actors[subLevel][i] = m_actors[subLevel][m_actors[subLevel].size()-1];
            m_actors[subLevel].pop_back();
        }
        else
            i++;
    }
    if (m_finishedLevel == true)
        return GWSTATUS_FINISHED_LEVEL;
    
    return GWSTATUS_CONTINUE_GAME;
    
}


void StudentWorld::cleanUp()
{
    
    for (int p = 0; p < m_player.size(); p++)
    {
        delete m_player[p];
        m_player[p]=nullptr;
    }
    m_player.clear();
    
    for (int j = 0; j < m_actors.size(); j++)
    {
        for (int k = 0; k < m_actors[j].size(); k++)
        {
            delete m_actors[j][k];
        }
        m_actors[j].clear();
    }
    m_actors.clear();
}

void StudentWorld::setDisplayText()
{
    //string s = formatDisplay(getScore(), getLevel(), getCurrentSubLevel(), getLives(), m_health, m_ammo, m_timeLeft);
    ostringstream output;
    output.fill('0');
    output << "Score: " <<  setw(7) << getScore() << "  ";
    output.fill('0');
    output << "Level: " << setw(2) << getLevel();
    output.fill('0');
    output << "-" << setw(2) << getCurrentSubLevel() << "  ";
    output.fill(' ');
    output << "Lives: " << setw(2) << getLives() << "  ";
    output.fill(' ');
    output << "Health: " << setw(3) << m_health*5 << "%  ";
    output.fill(' ');
    output << "Ammo: " << setw(3) << m_ammo << "  ";
    output << "TimeLimit: " << setw(4) << m_timeLeft << "  ";
    
    string display = output.str();
    setGameStatText(display);
    
}

void StudentWorld::decCount(int ID) //For goodies: if something is picked up, decrease its count appropriately
{
    switch (ID){
        case IID_HOSTAGE:
            m_hostages--;
            break;
        case IID_JEWEL:
            m_jewels--;
            break;
        default:
            break;
    }
    
}
bool StudentWorld::revealExit() //Only reveals exit if all the jewels and hostages were picked up
{
    return (m_jewels == 0 && m_hostages == 0);
}

void StudentWorld::addAmmo(int amount)
{
    m_ammo += amount;
}
void StudentWorld::restoreHealth()
{
    m_health = 20;
}
//void StudentWorld::addLife()
//{
//    incLives();
//}
void StudentWorld::getHit(int hit)
{
    m_health -= hit;
    
}
int StudentWorld::getHealth()
{
    return m_health;
}
int StudentWorld::getAmmo()
{
    return m_ammo;
}

void StudentWorld::makeNew(Actor *thing)
{
    m_actors[getCurrentSubLevel()].push_back(thing);
}

int StudentWorld::bonusTime()
{
    return m_timeLeft;
}
void StudentWorld::finishedLevel()
{
    m_finishedLevel = true;
}

vector<Actor*> StudentWorld::getContents(int x, int y)
{
    vector<Actor*> vec_temp;
    for (int i = 0; i < m_actors[getCurrentSubLevel()].size(); i++)
    {
        if (m_actors[getCurrentSubLevel()][i]->getX() == x && m_actors[getCurrentSubLevel()][i]->getY() == y)
            vec_temp.push_back(m_actors[getCurrentSubLevel()][i]);
    }
    return vec_temp;
}

Player* StudentWorld::getPlayer(int x, int y)
{
    Player* getter = nullptr;
    if (m_player[getCurrentSubLevel()]->getX() == x && m_player[getCurrentSubLevel()]->getY() == y)
        getter = m_player[getCurrentSubLevel()];
    return getter;
}

StudentWorld::~StudentWorld()
{
    cleanUp();
}


