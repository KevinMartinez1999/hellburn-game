#ifndef BOLAFUEGO_H
#define BOLAFUEGO_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QBrush>
#include <cmath>
#include <QTimer>
#include "jugadorbatalla.h"

class bolaFuego : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit bolaFuego(QObject *parent = nullptr,
                       short int estado = 2,
                       short int tipo = 1);

    inline void setX0(int x) {x0 = x;}
    inline void setY0(int y) {y0 = y;}
    inline int getX0() {return x0;}
    inline int getY0() {return y0;}

    void colision(JugadorBatalla * obj);

    QPixmap Pixmap;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

signals:

public slots:
    void move1();
    void move2();
    void colision_con_boss();
    void colision_con_jugador();
    void Actualizacion();

private:
    double X, Y, w, r, t;
    int m, x0, y0;
    QTimer timer, animacion;
    short int ultimoEstado, Tipo;
    float columnas,ancho,alto;
};

#endif // BOLAFUEGO_H
