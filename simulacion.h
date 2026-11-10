#ifndef SIMULACION_H
#define SIMULACION_H

#include <array>
#include <fstream>
#include <string>
#include <vector>
#include "Particula.h"

class Simulacion {
private:
    double ancho, alto, e, t;
    std::vector<Particula> particulas;
    std::vector<std::array<double, 3>> obstaculos;   // {x, y, lado}
    std::ofstream out;

public:
    Simulacion(double ancho, double alto, double e);

    void agregarParticula(const Particula& p);
    void agregarObstaculo(double x, double y, double lado);
    void iniciar(const std::string& archivo);
    void paso(double dt);
    void terminar();

    double getTiempo() const;
    const std::vector<Particula>& getParticulas() const;
    const std::vector<std::array<double, 3>>& getObstaculos() const;
};

#endif
