#include "organisms.h"
using namespace std;

int main() {
    srand((unsigned int)time(NULL));
    World w(25, 80);
    w.ShowConsoleCursor(false);
    Owca o({ 0,0 }, &w);
    Zolw z({ 0,1 }, &w);
    w.addOrganism(&o);
    w.addOrganism(&z);
    /*for (int i = 0; i < 5; i++) {
        Organism* obj = new Owca({ 10,i }, &w);
        w.addOrganism(obj);
    }

    for (int i = 0; i < 5; i++) {
        Organism* obj = new Wilk({ 20,i }, &w);
        w.addOrganism(obj);
    }

    for (int i = 0; i < 5; i++) {
        Organism* obj = new Zolw({ 30,i }, &w);
        w.addOrganism(obj);
    }*/

    w.drawWorld();

    while (true) {
        w.nextTurn();
    }

    return EXIT_SUCCESS;
}
