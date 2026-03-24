# Description

To the west of the World of Warcraft lies the headquarters of the Red Army, and to the east lies the headquarters of the Blue Army. Between the two headquarters are several cities arranged in sequence.

Red Headquarters, City 1, City 2, …, City n, Blue Headquarters

Both headquarters will produce warriors. There are five types of warriors: dragon, ninja, iceman, lion, and wolf. Each type of warrior has two attributes: a serial number and health points.
Some warriors can possess weapons. There are three types of weapons: sword, bomb, and arrow, with serial numbers 0, 1, and 2 respectively.

The serial numbers for warriors on both sides start from 1. The nth warrior produced by the Red side has serial number n. Similarly, the nth warrior produced by the Blue side also has serial number n.

Different warriors have different characteristics.
A dragon can possess one weapon. A dragon with serial number n receives weapon number n % 3 upon birth. A dragon also has an attribute called "morale", which is a floating-point number equal to the remaining health points in its headquarters after its birth divided by the health points required to produce the dragon.
A ninja can possess two weapons. A ninja with serial number n receives weapons numbered n % 3 and (n + 1) % 3 upon birth.
An iceman has one weapon. An iceman with serial number n receives weapon number n % 3 upon birth.
A lion has an attribute called "loyalty", which is equal to the number of health points remaining in its headquarters after its birth.
A wolf has no special characteristics.
Please note that in future problems, a warrior's morale, health points, and loyalty may change during its lifetime and have effects. The attack power of a warrior's weapons may also change with use.

A warrior has a certain number of health points when first born.

At each hour on the hour, one warrior is born in each headquarters.

The Red headquarters produces warriors in a cyclic order: iceman, lion, wolf, ninja, dragon.

The Blue headquarters produces warriors in a cyclic order: lion, dragon, ninja, iceman, wolf.

Producing warriors consumes health points.

To produce a warrior with initial health points m, the headquarters' health points are reduced by m.

If the headquarters does not have enough health points to produce the next warrior in sequence, it attempts to produce the following one. If none of the warriors can be produced, the headquarters stops producing warriors.

Given a specific time and the initial health points of both headquarters, output all events in chronological order from 00:00 until both headquarters stop producing warriors.

There are two types of events, with output examples as follows:

Warrior Birth
Example output: 004 blue lion 5 born with strength 5,2 lion in red headquarter
This means that at 4:00, a Blue lion warrior with serial number 5 was born. It had 5 health points at birth. After its birth, the Blue headquarters had a total of 2 lion warriors. (For simplicity, plural forms of words are not considered.) Note that each time a new warrior is produced, the current total count of that warrior type in the headquarters must be output.
If a dragon is produced, an additional line should be output, for example:
It has a arrow,and it's morale is 23.34
This means that the dragon received an arrow at birth, and its morale is 23.34. (For simplicity, in this problem, the article before "arrow" is "a", not "an", and morale is rounded to two decimal places.)
If a ninja is produced, an additional line should be output, for example:
It has a bomb and a arrow
This means that the ninja received a bomb and an arrow at birth.
If an iceman is produced, an additional line should be output, for example:
It has a sword
This means that the iceman received a sword at birth.
If a lion is produced, an additional line should be output, for example:
It's loyalty is 24
This means that the lion's loyalty at birth was 24.
Headquarters stops producing warriors
Example output: 010 red headquarter stops making warriors
This means that at 10:00, the Red headquarters stopped producing warriors.
When outputting events:

First output events in chronological order;

If events occur at the same time, output events from the Red headquarters first, followed by those from the Blue headquarters.

# Input
The first line is an integer representing the number of test cases.

Each test case consists of two lines.

The first line contains an integer M, meaning that each headquarters initially has M health points (1 <= M <= 10000).

The second line contains five integers, representing the initial health points of dragon, ninja, iceman, lion, and wolf respectively. Each of these values is greater than 0 and less than or equal to 10000.

# Output
For each test case, output all events from 00:00 until both headquarters have stopped producing warriors.

For each test case, first output "Case:n", where n is the test case number starting from 1.

Then output all events in the appropriate order and format. Each event begins with the time at which it occurred, with the time expressed in hours, using three digits.

# Sample Input

```text
1
20
3 4 5 6 7
```
# Sample Output

```text
Case:1
000 red iceman 1 born with strength 5,1 iceman in red headquarter
It has a bomb
000 blue lion 1 born with strength 6,1 lion in blue headquarter
It's loyalty is 14
001 red lion 2 born with strength 6,1 lion in red headquarter
It's loyalty is 9
001 blue dragon 2 born with strength 3,1 dragon in blue headquarter
It has a arrow,and it's morale is 3.67
002 red wolf 3 born with strength 7,1 wolf in red headquarter
002 blue ninja 3 born with strength 4,1 ninja in blue headquarter
It has a sword and a bomb
003 red headquarter stops making warriors
003 blue iceman 4 born with strength 5,1 iceman in blue headquarter
It has a bomb
004 blue headquarter stops making warriors
```

# My answer(adapted from the WarCraft1)
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
vector<string> weapon = {"sword", "bomb", "arrow"};
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
    soldier (string camp, int type, int left) {
        this -> type = type;
        this -> camp = camp;
        if (camp == "Red") {
            cout << setw(3) << setfill('0') << Redindex << ' ';
            Rednum[type] ++;
            Redindex ++;
            cout << "red " << types[type] << ' ' << Redindex << " born with strength ";
            cout << strength[type] << ',' << Rednum[type] << ' ' << types[type];
            cout << " in red headquarter" << endl;
            switch (type){
                case 0:
                    cout << "It has a " << weapon[Redindex % 3] << ",and it's morale is ";
                    cout << fixed << setprecision(2) << float(left)/float(strength[0]) << endl;
                    return;
                case 1:
                    cout << "It has a " << weapon[Redindex % 3] << " and a " << weapon[(Redindex + 1) % 3] << endl;
                    return;
                case 2:
                    cout << "It has a " << weapon[Redindex % 3] << endl;
                    return;
                case 3:
                    cout << "It's loyalty is " << left << endl;
            }
        }
        else{
            cout << setw(3) << setfill('0') << Blueindex << ' ';
            Bluenum[type] ++;
            Blueindex ++;
            cout << "blue " << types[type] << ' ' << Blueindex << " born with strength ";
            cout << strength[type] << ',' << Bluenum[type] << ' ' << types[type];
            cout << " in blue headquarter" << endl;
            switch (type){
                case 0:
                    cout << "It has a " << weapon[Blueindex % 3] << ",and it's morale is ";
                    cout << fixed << setprecision(2) << float(left)/float(strength[0]) << endl;
                    return;
                case 1:
                    cout << "It has a " << weapon[Blueindex % 3] << " and a " << weapon[(Blueindex + 1) % 3] << endl;
                    return;
                case 2:
                    cout << "It has a " << weapon[Blueindex % 3] << endl;
                    return;
                case 3:
                    cout << "It's loyalty is " << left << endl;
            }
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
                    Red -= strength[RedTurns[rt]];
                    soldier temp1("Red", RedTurns[rt], Red);
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
                    Blue -= strength[BlueTurns[bt]];
                    soldier temp2("Blue", BlueTurns[bt], Blue);
                    bt = (bt+1)%5;
                }
            }
        }
    }
    return 0;
}
```
