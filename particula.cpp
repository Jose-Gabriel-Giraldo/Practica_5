#include "Particula.h"
#include <cmath>

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

// (ox, oy) es la esquina inferior izquierda del cuadrado
const char* Particula::chocarObstaculo(double ox, double oy, double lado, double e) {
    double cx = x < ox ? ox : (x > ox + lado ? ox + lado : x);
    double cy = y < oy ? oy : (y > oy + lado ? oy + lado : y);
    double dx = x - cx, dy = y - cy;
    double d2 = dx * dx + dy * dy;
    if (d2 >= r * r) return nullptr;

    double nx, ny;
    if (d2 > 0) {
        double d = std::sqrt(d2);
        nx = dx / d;
        ny = dy / d;
    } else {
        double izq = x - ox, der = ox + lado - x, inf = y - oy, sup = oy + lado - y;
        double minX = izq < der ? izq : der, minY = inf < sup ? inf : sup;
        if (minX < minY) { nx = izq < der ? -1 : 1; ny = 0; cx = izq < der ? ox : ox + lado; }
        else             { nx = 0; ny = inf < sup ? -1 : 1; cy = inf < sup ? oy : oy + lado; }
    }

    x = cx + nx * r;
    y = cy + ny * r;

    double vn = vx * nx + vy * ny;
    if (vn >= 0) return nullptr;
    vx -= (1 + e) * vn * nx;
    vy -= (1 + e) * vn * ny;

    if (std::fabs(nx) >= std::fabs(ny)) return nx < 0 ? "izquierdo" : "derecho";
    return ny < 0 ? "inferior" : "superior";
}

void Particula::escribir(std::ostream& out, double t) const {
    out << t << ' ' << id << ' ' << x << ' ' << y << ' ' << r << '\n';
}