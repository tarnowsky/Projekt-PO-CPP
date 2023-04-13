#include "animal.h"

using namespace std;

int main() {
    srand((unsigned int)time(NULL));
    World w(20, 60);
    w.ShowConsoleCursor(false);

    //Animal a({ 0,0 }, 'A', &w), b({ 0,1 }, 'B', &w), c({ 0,2 }, 'C', &w), d({ 0,3 }, 'D', &w);

    //a.setInitiative(5);
    //for (int i = 0; i < 7; i++) a.incrementAge();
    //b.setInitiative(10);
    //for (int i = 0; i < 8; i++) b.incrementAge();
    //c.setInitiative(10);
    //for (int i = 0; i < 5; i++) c.incrementAge();
    //d.setInitiative(6);
    //for (int i = 0; i < 10; i++) d.incrementAge();

    //w.addOrganism(&a);
    //w.addOrganism(&b);
    //w.addOrganism(&c);
    //w.addOrganism(&d);

    //cout << endl;
    //for (int i = 0; i < 4; i++)
    //    printf("%c\n", w.getOrganismArr()[i]->getID());
    for (int i = 0; i < 30; i++) {
        Animal* a;
        if (i % 3 == 1) {
            a = new Animal({ i,0 }, 'A', &w);
        }
        else if(i%3 == 2) 
        {
            a = new Animal({ i,1 }, 'A' + 1, &w);
        }
        else 
        {
            a = new Animal({ i,2 }, 'A' + 2, &w);
        }
        w.addOrganism(a);
    }
    /*Animal a[] = {
        {{1,1},'A',&w},
        {{2,2},'B',&w},
        {{3,3},'C',&w},
        {{4,4},'D',&w},
        {{5,5},'E',&w},
        {{6,6},'F',&w},
        {{7,7},'G',&w},
    };
    for (int i = 0; i < 7; i++) {
        a[i].setPower(i);
        w.addOrganism(&(a[i]));
    }*/
    /*Animal* a = new Animal({ 0,0 }, 'A', &w);
    w.addOrganism(a);*/
    w.drawWorld();
    while (true) {
        Sleep(50);
        w.nextTurn();
        //cin.get();
    }
    return EXIT_SUCCESS;
}
