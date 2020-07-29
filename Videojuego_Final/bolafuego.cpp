#include "bolafuego.h"
#include "boss.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define g 9.81
#define b 0.47
#define pi 3.14159265
#define e 0.7
#define u 0.8
#define G 1
#define T 1

extern Boss *boss;
extern JugadorBatalla *jugadorBatalla, *jugadorBatalla2;
extern short int num_jugadores;
extern QList<bolaFuego *> bolas;

bolaFuego::bolaFuego(QObject *parent, short int estado, short int tipo)
    : QObject(parent), ultimoEstado(estado), Tipo(tipo)
{
    //Inicializar constantes del mov
    t = 0;
    m = 5;
    r = 15;
    w = 7;

    //Dimensiones del sprite
    columnas = 0;
    ancho = 40;
    alto = 40;

    //crear box
    box.setRect(0,0,10,10);

    //Definicion de los timers
    switch (Tipo) {
    case 1:
        connect(&timer, SIGNAL(timeout()), this, SLOT(move1()));
        connect(&timer, SIGNAL(timeout()), this, SLOT(colision_con_boss()));
        dano = 6;
        break;
    case 2:
        connect(&timer, SIGNAL(timeout()), this, SLOT(move2()));
        connect(&timer, SIGNAL(timeout()), this, SLOT(colision_con_jugador()));
        dano = 6;
        break;
    case 3:
        connect(&timer, SIGNAL(timeout()), this, SLOT(move3()));
        connect(&timer, SIGNAL(timeout()), this, SLOT(colision_con_jugador()));
        dano = 10;
        break;
    case 4:
        connect(&timer, SIGNAL(timeout()), this, SLOT(move4()));
        connect(&timer, SIGNAL(timeout()), this, SLOT(colision_con_jugador()));
        dano = 10;
        break;
    case 5:
        connect(&timer, SIGNAL(timeout()), this, SLOT(move5()));
        connect(&timer, SIGNAL(timeout()), this, SLOT(colision_con_jugador()));
        dano = 20;
        break;
    }
    timer.start(30);

    connect(&animacion, SIGNAL(timeout()), this, SLOT(Actualizacion()));
    animacion.start(150);
}

QRectF bolaFuego::boundingRect() const
{
    return QRectF(-ancho/2,-alto/2,ancho,alto);
}

void bolaFuego::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(-ancho/2,-alto/2,Pixmap,columnas,0,ancho,alto);
}

void bolaFuego::move1() //Golpe del jugador
{
    t += 0.1;
    X += r*cos(w*t) + m;
    Y += -r*sin(w*t);
    setPos(X,Y);
    box.setPos(x()-5, y()-5);
}

void bolaFuego::move2() //Caida libre con rozamiento con el aire
{
    t += 0.1;
    Y += g*exp(-t*b/masa);
    setY(Y);
    box.setPos(x()-5, y()-5);
    if (y() > 670)
        delete this;
}

void bolaFuego::move3() //Bolas del enemigo con MRUA
{
    t += 0.1;
    X += -((Vx*t) + (0.5*Ax*t*t));
    setX(X);
    box.setPos(x()-5, y()-5);
    if (x() < -40)
        delete this;
}

void bolaFuego::move4() //Bolas parabolicas del enemigo
{
    if (y() > 530){
        setY(529);
        t = 0.5;
        Vy *= e;
        Vx *= u;
        if (abs(Vx) < 0.1)
            delete this;
    }

    t += 0.1;
    X = (Vx*t); // => cos(45°)
    Y = (Vy*t)-(0.5*g*t*t); // => sen(45°)
    setPos(x()-X,y()-Y);
    box.setPos(x()-5, y()-5);
}

void bolaFuego::move5()
{
    double ax = 0.00, ay = 0.00;
    int len = bolas.size();
    for (int i = 0; i < len; i++)
    {
        if (bolas[i] == 0){
            setPos(boss->x(), boss->y());
            return;
        }
        if (bolas[i] != this)
        {
            double r = sqrt(pow(bolas[i]->X-X, 2)+pow(bolas[i]->Y-Y, 2));
            ax += G*bolas[i]->masa*(bolas[i]->X-X)/(pow(r, 3));
            ay += G*bolas[i]->masa*(bolas[i]->Y-Y)/(pow(r, 3));
        }
    }
    Vx += ax*T;
    Vy += ay*T;
    X += Vx*T;
    Y += Vy*T;
    setPos(X,Y);
    box.setPos(x()-5, y()-5);
}

void bolaFuego::colision_con_boss()
{
    if (abs(x() - boss->x()) < 50){
        boss->health -= dano;
        boss->vida.setRect(0,0,boss->health, 40);
        delete this;
    }
    else if (x() < -10 or x() > 1010)
        delete this;
}

void bolaFuego::colision_con_jugador()
{
    if (num_jugadores == 2){
        if(colision(jugadorBatalla) and colision(jugadorBatalla2))
            delete this;
        else if(colision(jugadorBatalla) or colision(jugadorBatalla2))
            delete this;
    }
    else
        if(colision(jugadorBatalla))
            delete this;
}

bool bolaFuego::colision(JugadorBatalla *obj)
{
    if (box.collidesWithItem(&obj->box)){
        if(obj->health>1)
            obj->JugadorAtacado->play();
        obj->health -= dano;
        obj->vida.setRect(0,0,obj->health,40);
        if(!obj->muerto)
                    return true;
                else return false;
    }
    else return false;
}

void bolaFuego::Actualizacion()
{
    if (columnas >= 160)
        columnas = 0;
    else
        columnas += 40;
    this->update(-ancho/2,-alto/2,ancho,alto);
}


