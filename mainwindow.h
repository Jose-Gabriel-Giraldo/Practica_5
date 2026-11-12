#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QTimer>
#include <vector>
#include "Simulacion.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void actualizar();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *escena;
    QTimer *timer;
    Simulacion sim;
    std::vector<QGraphicsEllipseItem*> circulos;   // indexado por id
};

#endif
