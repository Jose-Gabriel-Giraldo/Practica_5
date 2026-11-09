#ifndef SIMULACION_H
#define SIMULACION_H

#include <fstream>
#include <string>
#include <vector>
#include "Particula.h"

class Simulacion {
private:
    double ancho, alto, t;
    std::vector<Particula> particulas;
    std::ofstream out;

public:
    Simulacion(double ancho, double alto);

    void agregarParticula(const Particula& p);
    void iniciar(const std::string& archivo);
    void paso(double dt);
    void terminar();

    double getTiempo() const;
    const std::vector<Particula>& getParticulas() const;
};

#endif
