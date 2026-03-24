//Exercise on virtual functions
#include <iostream>
using namespace std;

class Man;

class bug {
public:
    int blood;
    bug(int n): blood(n) {};
    virtual ~bug(){
        cout << "虫子被消灭了！" << endl;
    }
    virtual void attack (Man& a) = 0;
    void attacked(int n) {
        cout << "虫子：werwerwer" << endl;
        blood -= n;
    }
    
    bool AliveOrNot () {
        return (blood > 0);
    }
};

class Man{
public:
    int strength;
    Man (int n): strength(n) {};
    ~Man () {
        cout << "人：What can I say!" << endl;
    }
    void fight_back (bug *p) {
        p -> attacked(strength);
    }
    
    void attacked (int n, bug *attacker){
        cout << "人：八嘎牙路" << endl;
        strength -= n;
        this -> fight_back(attacker);
    }
    
    bool AliveOtNot () {
        return (strength > 0);
    }
};

class mosquito: public bug {
public:
    int aggressivity;
    mosquito(int b, int a): bug(b), aggressivity(a) {};
    ~ mosquito() {cout << "蚊子被消灭了，人类赢了！" << endl;}
    void attack (Man &a) override {
        cout << "蚊子：hiahiahia" << endl;
        a.attacked (aggressivity, this);
    }
};


int main () {
    Man a(100);
    mosquito m(500, 50);
    while(a.AliveOtNot() && m.AliveOrNot()){
        m .attack(a);
    }
    return 0;
}
