#include "animal.h"
#include<windows.h>

using namespace std;

int main() {
    srand((unsigned int)time(NULL));
    World w(20, 30);
    for (int i = 0; i < 20; i++) {
        Animal* a;
        if (i % 2) a = new Animal({ i,0 }, 'A', &w);
        else a = new Animal({ i,10 }, 'A' + 1, &w);
        w.addOrganism(a);
    }
    /*Animal a[] = {
        {{1,1},'A',&w},
        {{0,1},'A',&w},
        {{0,2},'A',&w},
        {{1,3},'A',&w},
        {{2,2},'A',&w},
        {{2,1},'A',&w},
        {{1,0},'A',&w},
        {{1,2},'A',&w},
    };
    for (int i = 0; i < 8; i++) {
        w.addOrganism(&(a[i]));
    }*/
    w.drawWorld();
    int i = 0;
    while (i < 30) {
        Sleep(100);
        w.nextTurn();
        w.drawWorld();
        i++;
    }
    return EXIT_SUCCESS;
}
