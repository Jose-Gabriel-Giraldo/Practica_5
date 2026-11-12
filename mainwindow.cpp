#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QGraphicsView>
#include <QMessageBox>
#include <stdexcept>

const double ANCHO = 100, ALTO = 60;
const double RESTITUCION = 0.7;
const double DT = 0.005, T_TOTAL = 20;
const double ESCALA = 8;            // pixeles por unidad
const int INTERVALO_MS = 15;
const int PASOS_POR_FRAME = 3;      // 3 * 5 ms = 15 ms -> tiempo real

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), sim(ANCHO, ALTO, RESTITUCION)
{
    ui->setupUi(this);

    escena = new QGraphicsScene(0, 0, ANCHO * ESCALA, ALTO * ESCALA, this);
    QGraphicsView *vista = new QGraphicsView(escena, this);
    vista->setRenderHint(QPainter::Antialiasing);
    setCentralWidget(vista);
    escena->addRect(escena->sceneRect(), QPen(Qt::black, 2));

    sim.agregarObstaculo(20, 12, 8);
    sim.agregarObstaculo(70, 12, 8);
    sim.agregarObstaculo(20, 40, 8);
    sim.agregarObstaculo(70, 40, 8);

    //                       id   x   y    vx    vy   m    r
    sim.agregarParticula(Particula(1, 10, 30,  14,   6,  2, 1.5));
    sim.agregarParticula(Particula(2, 50, 50,  -9, -12,  3, 2.0));
    sim.agregarParticula(Particula(3, 90, 10, -16,   8,  1, 1.2));
    sim.agregarParticula(Particula(4, 50, 10,  10,  15,  4, 2.2));
    sim.agregarParticula(Particula(5, 85, 50, -12, -10,  2, 1.5));

    for (const auto& o : sim.getObstaculos())
        escena->addRect(o[0] * ESCALA, (ALTO - o[1] - o[2]) * ESCALA, o[2] * ESCALA, o[2] * ESCALA,
                        QPen(Qt::NoPen), QBrush(Qt::gray));

    const QColor colores[] = {Qt::blue, Qt::red, Qt::darkGreen, Qt::magenta, Qt::darkYellow, Qt::cyan};
    for (const Particula& p : sim.getParticulas()) {
        std::size_t id = static_cast<std::size_t>(p.getId());
        if (id >= circulos.size()) circulos.resize(id + 1, nullptr);
        circulos[id] = escena->addEllipse(0, 0, 0, 0, QPen(Qt::NoPen), QBrush(colores[id % 6]));
    }

    try {
        sim.iniciar("simulacion.txt");
    } catch (const std::exception& ex) {
        QMessageBox::critical(this, "Error", ex.what());
        return;
    }

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::actualizar);
    timer->start(INTERVALO_MS);
    actualizar();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::actualizar()
{
    for (int k = 0; k < PASOS_POR_FRAME && sim.getTiempo() < T_TOTAL - DT / 2; ++k)
        sim.paso(DT);

    for (QGraphicsEllipseItem *c : circulos)
        if (c) c->hide();

    for (const Particula& p : sim.getParticulas()) {
        double r = p.getR();
        QGraphicsEllipseItem *c = circulos[static_cast<std::size_t>(p.getId())];
        c->setRect((p.getX() - r) * ESCALA, (ALTO - p.getY() - r) * ESCALA, 2 * r * ESCALA, 2 * r * ESCALA);
        c->show();
    }

    setWindowTitle(QString("Colisiones múltiples  —  t = %1 s").arg(sim.getTiempo(), 0, 'f', 2));

    if (sim.getTiempo() >= T_TOTAL - DT / 2) {
        timer->stop();
        sim.terminar();
    }
}
