#include <thread>
#include <iostream>
#include <vector>
using namespace std;

class Player {
public:
    Player(string name): name(name) {}
    virtual ~Player() = default;
    virtual void attack() = 0;
    virtual void deffence() = 0;

protected:
    string name;
};
class Forwards: public Player {
public:
    Forwards(string name): Player(name) {}
    virtual void attack() {
        std::cout << this->name << " Forwards attack." << std::endl;
    }
    virtual void deffence() {
        std::cout << this->name << " Forwards deffence." << std::endl;
    }
};
class Center: public Player {
public:
    Center(string name): Player(name) {}
    virtual void attack() {
        std::cout << this->name << " Center attack." << std::endl;
    }
    virtual void deffence() {
        std::cout << this->name << " Center deffence." << std::endl;
    }
};

class Translater: public Player {
public:
    Translater(string name): Player(name) {
        this->player = new Center(name);
    }
    virtual ~Translater() {
        delete this->player;
    }

    virtual void attack() {
        this->player->attack();
    }
    virtual void deffence() {
        this->player->deffence();
    }

private:
    Player* player;
};

int main() {

    Player* player = new Translater("Ronaldo");
    player->attack();
    player->deffence();

    delete player;
}