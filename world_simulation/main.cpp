#include "organisms.h"
using namespace std;

int main() {
    srand((unsigned int)time(NULL));
    World w(25, 100);
    w.ShowConsoleCursor(false);
    Czlowiek c({ 0, 0 }, &w);
    Wilk wi({ 10, 0 }, &w);
    Mlecz g({ 20, 0 }, &w);
    w.addOrganism(&c);
    w.addOrganism(&wi);
    w.addOrganism(&g);
    
    w.drawWorld();

    while (true) {
        w.nextTurn();
    }
    return EXIT_SUCCESS;
}
