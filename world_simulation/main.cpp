#include "animal.h"

using namespace std;

int main() {
    srand((unsigned int)time(NULL));
    World w(20, 60);
    w.ShowConsoleCursor(false);
    for (int i = 0; i < 15; i++) {
        Animal* a;
        if (i % 3 == 1) a = new Animal({ i,0 }, 'A', &w);
        else if(i%3 == 2) a = new Animal({ i,1 }, 'A' + 1, &w);
        else a = new Animal({ i,2 }, 'A' + 2, &w);
        w.addOrganism(a);
    }
    /*Animal a[] = {
        {{1,1},'A',&w},
        {{0,1},'B',&w},
        {{0,2},'C',&w},
        {{1,3},'D',&w},
        {{2,2},'A',&w},
        {{2,1},'B',&w},
        {{1,0},'C',&w},
        {{1,2},'D',&w},
    };*/
    /*for (int i = 0; i < 8; i++) {
        w.addOrganism(&(a[i]));
    }*/
    /*Animal* a = new Animal({ 0,0 }, 'A', &w);
    w.addOrganism(a);*/
    w.drawWorld();
    while (true) {
        Sleep(200);
        w.nextTurn();
        //cin.get();
        w.drawWorld();
    }
    return EXIT_SUCCESS;
}
