#ifndef PARTICULA_H
#define PARTICULA_H

#include <ostream>

class Particula {
private:
    int id;
    double x, y, vx, vy, m, r;

public:
    Particula(int id, double x, double y, double vx, double vy, double m, double r);

    int getId() const;
    void mover(double dt);
    bool rebotarParedes(double ancho, double alto);
    void escribir(std::ostream& out, double t) const;
};

#endif