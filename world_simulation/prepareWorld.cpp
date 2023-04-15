#include "prepareWorld.h"

void prepareWorld(World* w) {
    Organism* o;
    for (int i = 0; i < 1; i++) {
        o = new Czlowiek({ 0, 0 }, w);
        w->addOrganism(o);
    }
    for (int i = 0; i < 3; i++) {
        o = new Wilk({ 10, i }, w);
        w->addOrganism(o);
    }
    for (int i = 0; i < 3; i++) {
        o = new Owca({ 20, i, }, w);
        w->addOrganism(o);
    }
    for (int i = 0; i < 3; i++) {
        o = new Zolw({ 30, i }, w);
        w->addOrganism(o);
    }
    for (int i = 0; i < 3; i++) {
        o = new Antylopa({ 40, i }, w);
        w->addOrganism(o);
    }
    for (int i = 0; i < 1; i++) {
        o = new Trawa({ 15, i }, w);
        w->addOrganism(o);
    }
    for (int i = 0; i < 1; i++) {
        o = new Mlecz({ 25, i }, w);
        w->addOrganism(o);
    }
    for (int i = 0; i < 1; i++) {
        o = new Guarana({ 5, i }, w);
        w->addOrganism(o);
    }
    for (int i = 0; i < 1; i++) {
        o = new WilczeJagody({ 35, i }, w);
        w->addOrganism(o);
    }
    for (int i = 0; i < 1; i++) {
        o = new BarszczSosnowskiego({ 45, i }, w);
        w->addOrganism(o);
    }
}