#include "Simulacion.h"
#include <iomanip>
#include <stdexcept>

Simulacion::Simulacion(double ancho, double alto)
    : ancho(ancho), alto(alto), t(0) {}

void Simulacion::agregarParticula(const Particula& p) { particulas.push_back(p); }

void Simulacion::iniciar(const std::string& archivo) {
    out = std::ofstream(archivo);
    if (!out) throw std::runtime_error("No se pudo abrir " + archivo);
    out << std::fixed << std::setprecision(4);

    t = 0;
    out << "CAJA " << ancho << ' ' << alto << '\n';
    for (const Particula& p : particulas) { out << "P "; p.escribir(out, t); }
}

void Simulacion::paso(double dt) {
    t += dt;

    for (Particula& p : particulas) {
        p.mover(dt);
        if (p.rebotarParedes(ancho, alto))
            out << "C " << t << " pared " << p.getId() << '\n';
    }

    for (const Particula& p : particulas) { out << "P "; p.escribir(out, t); }
}

void Simulacion::terminar() { out << std::flush; }

double Simulacion::getTiempo() const { return t; }

const std::vector<Particula>& Simulacion::getParticulas() const { return particulas; }
