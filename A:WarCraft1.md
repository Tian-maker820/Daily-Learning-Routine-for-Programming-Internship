# Stem:
## Description:

There are two tribes in the world. The headquarter of Red tribe is in the west of the world and the Blue tribe’s is in the east. There are n cities between these two headquarters, denoted as:

Red headquarter -City 1 - City 2 - City 3, …  - City n -Blue headquarter

Headquarters can create warriors. There are five types of warriorsin total. They are dragon, ninja,iceman, lion, wolf. Every warrior has three properties: Number, strength, Attack.

In each headquarter, the Number of warriors starts from 1. For example, The Number of the warrioris n, if he was the Nth to be made in Red headquarter. Similarly, If the Blue headquarter made the Nth warrior, his Number is n.

Every warrior is born with a strength.

In every integral point, each headquarter will create a new warrior.

The order of warrior creation in Red headquarter: iceman, lion, wolf, ninja, dragon

The order of warrior creation in Blue headquarter: lion, dragon, ninja, iceman, wolf

The creation of a warrior will consume the strength of the headquarter. For example, if the Blue headquarter made a warrior with m strength, then the strength of the Blue headquarter will reduce m.

If the headquarter doesn’t have the enough strength to create the present warrior,it will move to the warrior of next type. When the headquarter cannot create any type of warriors, it stops.

## Requirement:

When the time and the initial strength of two headquarters are given, you need to list every event of two headquarters after 0:00.

There are two types of events:

(1)  A warrior is born

Sample:  004 blue lion 5 bornwith strength 5,2 lion in red headquarter

It means in 4:00, a lion was born in red headquarter, his Number is 5 and strength is 5. Now, there are 2 lions in the red headquarter.(notice: do not use plural form, for example it is 2 lionnot 2 lions)

(2)  headquarter stops making warriors

Sample: 010 red headquarter stops making warriors`

It means in 10:00, the red headquarter stops making warriors

When you list the events, it should output in chronological order. If some events happen at the same time, first output the event in the Red headquarter then Blue headquarter.

 

## input:
The first line is an integer, it means the number of test cases.
For every case:
The first line is an integer M, it means the initial strength of the two headquarters.
The second line are the strength of dragon, ninja, iceman, lion, wolf.
## output:
For every case:
You need to output every event starting from 0:00 until the two headquarters stop creating warriors.
First output “Case:n”, n is the number of the case, n is starting from 1 (The total number of cases is given in the first line of input).
Every event start with the timing, the timing is three-digit number (there is no 24 hours limited).
## sample input:
```
1

20

3 4 5 6 7
```
## sample output:

Case:1
```
000 red iceman 1 born with strength 5,1 iceman in red headquarter

000 blue lion 1 born with strength 6,1 lion in blue headquarter

001 red lion 2 born with strength 6,1 lion in red headquarter

001 blue dragon 2 born with strength 3,1 dragon in blue headquarter

002 red wolf 3 born with strength 7,1 wolf in red headquarter

002 blue ninja 3 born with strength 4,1 ninja in blue headquarter

003 red headquarter stops making warriors

003 blue iceman 4 born with strength 5,1 iceman in blue headquarter

004 blue headquarter stops making warriors
```

## My answer:(Not the standard answer)

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <climits>

using namespace std;

vector<string> types = {"dragon", "ninja", "iceman", "lion", "wolf"};
vector<int> RedTurns = {2, 3, 4, 1, 0};
vector<int> BlueTurns = {3, 0, 1, 2, 4};
vector<int> strength(5);

class soldier{
private:
    int type;
    string camp;
public:
    static vector<int> Rednum;
    static vector<int> Bluenum;
    static int Redindex;
    static int Blueindex;
    soldier (string camp, int type) {
        this -> type = type;
        this -> camp = camp;
        if (camp == "Red") {
            cout << setw(3) << setfill('0') << Redindex << ' ';
            Rednum[type] ++;
            Redindex ++;
            cout << "red " << types[type] << ' ' << Redindex << " born with strength ";
            cout << strength[type] << ',' << Rednum[type] << ' ' << types[type];
            cout << " in red headquarter" << endl;
        }
        else{
            cout << setw(3) << setfill('0') << Blueindex << ' ';
            Bluenum[type] ++;
            Blueindex ++;
            cout << "blue " << types[type] << ' ' << Blueindex << " born with strength ";
            cout << strength[type] << ',' << Bluenum[type] << ' ' << types[type];
            cout << " in blue headquarter" << endl;
        }
    }
};

vector<int> soldier::Rednum(5, 0);
vector<int> soldier::Bluenum(5, 0);
int soldier::Redindex = 0;
int soldier::Blueindex = 0;

int main (){
    int n = 0;
    cin >> n;
    for (int i = 0; i < n; i++){
        soldier::Rednum.assign(5, 0);
        soldier::Bluenum.assign(5, 0);
        soldier::Redindex = 0;
        soldier::Blueindex = 0;
        cout << "Case:" << i+1 << endl;
        int M = 0;
        cin >> M;
        int minstrength = INT_MAX;
        for (int j = 0; j < 5; j++){
            cin >> strength[j];
            minstrength = min(strength[j], minstrength);
        }
        
        int Blue = M, Red = M, rt = 0, bt = 0;
        bool Redstop = false, Bluestop = false;
        while (!Redstop || !Bluestop){
            if (!Redstop){
                if (minstrength > Red){
                    cout << setw(3) << setfill('0') << soldier::Redindex << ' ';
                    cout << "red headquarter stops making warriors" << endl;
                    Redstop = true;
                }
                else{
                    while (Red < strength[RedTurns[rt]]) rt = (rt+1)%5;
                    soldier temp1("Red", RedTurns[rt]);
                    Red -= strength[RedTurns[rt]];
                    rt = (rt+1)%5;
                }
            }
            
            if (!Bluestop){
                if (minstrength > Blue){
                    cout << setw(3) << setfill('0') << soldier::Blueindex << ' ';
                    cout << "blue headquarter stops making warriors" << endl;
                    Bluestop = true;
                }
                else{
                    while (Blue < strength[BlueTurns[bt]]) bt = (bt+1)%5;
                    soldier temp2("Blue", BlueTurns[bt]);
                    Blue -= strength[BlueTurns[bt]];
                    bt = (bt+1)%5;
                }
            }
        }
    }
    return 0;
}
```
