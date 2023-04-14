#include "organisms.h"
using namespace std;

int main() {
    srand((unsigned int)time(NULL));
    World w(25, 80);
    w.ShowConsoleCursor(false);
    for (int i = 0; i < 3; i++) {
        Organism* obj = new Antylopa({ 10,i }, &w);
        w.addOrganism(obj);
    }

    for (int i = 0; i < 3; i++) {
        Organism* obj = new Wilk({ 20,i }, &w);
        w.addOrganism(obj);
    }

    for (int i = 0; i < 3; i++) {
        Organism* obj = new Zolw({ 30,i }, &w);
        w.addOrganism(obj);
    }

    for (int i = 0; i < 3; i++) {
        Organism* obj = new Lis({ 40,i }, &w);
        w.addOrganism(obj);
    }

    for (int i = 0; i < 3; i++) {
        Organism* obj = new Owca({ 50,i }, &w);
        w.addOrganism(obj);
    }
    
    for (int i = 0; i < 3; i++) {
        Organism* obj = new Mlecz({ 60,i }, &w);
        w.addOrganism(obj);
    }

    for (int i = 0; i < 3; i++) {
        Organism* obj = new Trawa({ 0,i }, &w);
        w.addOrganism(obj);
    }

    w.drawWorld();

    while (true) {
        //cin.get();
        w.nextTurn();
    }

    return EXIT_SUCCESS;
}
