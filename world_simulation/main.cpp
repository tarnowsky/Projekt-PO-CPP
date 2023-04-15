#include "prepareWorld.h"
using namespace std;

int main() {
    srand((unsigned int)time(NULL));
    World w(20, 100);
    w.ShowConsoleCursor(false);
    prepareWorld(&w);
    w.drawWorld();
    while (true) {
        w.nextTurn();
    }

    return EXIT_SUCCESS;
}
