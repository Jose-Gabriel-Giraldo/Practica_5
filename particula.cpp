#include "Particula.h"

Particula::Particula(int id, double x, double y, double vx, double vy, double m, double r)
    : id(id), x(x), y(y), vx(vx), vy(vy), m(m), r(r) {}

int Particula::getId() const { return id; }

void Particula::mover(double dt) {
    x += vx * dt;
    y += vy * dt;
}

bool Particula::rebotarParedes(double ancho, double alto) {
    bool choco = false;
    if (x - r < 0 && vx < 0)           { x = r;          vx = -vx; choco = true; }
    else if (x + r > ancho && vx > 0)  { x = ancho - r;  vx = -vx; choco = true; }
    if (y - r < 0 && vy < 0)           { y = r;          vy = -vy; choco = true; }
    else if (y + r > alto && vy > 0)   { y = alto - r;   vy = -vy; choco = true; }
    return choco;
}

void Particula::escribir(std::ostream& out, double t) const {
    out << t << ' ' << id << ' ' << x << ' ' << y << ' ' << r << '\n';
}