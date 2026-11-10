#include "Simulacion.h"
#include <iomanip>
#include <stdexcept>

Simulacion::Simulacion(double ancho, double alto, double e)
    : ancho(ancho), alto(alto), e(e), t(0) {}

void Simulacion::agregarParticula(const Particula& p) { particulas.push_back(p); }

void Simulacion::agregarObstaculo(double x, double y, double lado) {
    obstaculos.push_back({x, y, lado});
}

void Simulacion::iniciar(const std::string& archivo) {
    out = std::ofstream(archivo);
    if (!out) throw std::runtime_error("No se pudo abrir " + archivo);
    out << std::fixed << std::setprecision(4);

    t = 0;
    out << "CAJA " << ancho << ' ' << alto << '\n';
    for (const auto& o : obstaculos) out << "O " << o[0] << ' ' << o[1] << ' ' << o[2] << '\n';
    for (const Particula& p : particulas) { out << "P "; p.escribir(out, t); }
}

void Simulacion::paso(double dt) {
    t += dt;

    for (Particula& p : particulas) {
        p.mover(dt);
        if (p.rebotarParedes(ancho, alto))
            out << "C " << t << " pared " << p.getId() << '\n';
        for (std::size_t j = 0; j < obstaculos.size(); ++j) {
            const auto& o = obstaculos[j];
            if (const char* lado = p.chocarObstaculo(o[0], o[1], o[2], e))
                out << "C " << t << " obstaculo " << p.getId() << ' ' << j << ' ' << lado << '\n';
        }
    }

    for (const Particula& p : particulas) { out << "P "; p.escribir(out, t); }
}

void Simulacion::terminar() { out << std::flush; }

double Simulacion::getTiempo() const { return t; }

const std::vector<Particula>& Simulacion::getParticulas() const { return particulas; }

const std::vector<std::array<double, 3>>& Simulacion::getObstaculos() const { return obstaculos; }
