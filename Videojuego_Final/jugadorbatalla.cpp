#include "jugadorbatalla.h"
#include <QDebug>
#define t 0.03

JugadorBatalla::JugadorBatalla(QObject *parent) : QObject(parent)
{
    banLeft = false;
    banRight = false;

    vx=5;
    xFinal=x0;

    QTimer *timer1 = new QTimer;
    connect(timer1, SIGNAL(timeout()), this, SLOT(moveLeft()));
    connect(timer1, SIGNAL(timeout()), this, SLOT(moveRight()));
    connect(timer1, SIGNAL(timeout()), this, SLOT(setX()));
    timer1->start(30);

    //Timer para las actualización y dibujo del sprite.
    timer = new QTimer(this);
    columnas = 0;
    fila = 0;

    //Ancho y alto del sprite del jugador
    ancho = 84;
    alto  = 84;
    connect(timer,SIGNAL(timeout()),this,SLOT(Actualizacion()));
    /*Este timer nos permitira la constante actualizacion de la imagen de nuestro jugador*/
    timer->start(150);
}

QRectF JugadorBatalla::boundingRect() const
{
    /*La funcion propia de qt bodingRect, crea y retorna el rectangulo que conforma la figura del jugador y en el cual pintaremos nuestra
    imagen. -ancho/2,-alto/2 permite que el punto de origen del rectangulo siempre sea le centro de la imagen y no la esquina superior.*/
    return QRectF(-ancho/2,-alto/2,ancho,alto);
}

void JugadorBatalla::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    /*Funcion propia de Qt que nos permite dibujar dentro del boundingRect la imagen que queramos, para hacer esto debemos introducirle
    al drawPixmap algunos datos como el punto en el que queremos que empiece a dibujar, el pixmap a dibujar, el ancho y alto de
    lo que se dibujara y tambien, se le pasara constantemente en la funcion actualizar la columna que representara el cuadro 84x84
    que se dibujara en el momento. La variable fila representa el grupo de frames que se quiere realizar dependiendo a las acciones del
    jugador, esta variable cambia cuando el usuario activa un KeyEvent.*/
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(-ancho/2,-alto/2,*pixmap,columnas,fila,ancho,alto);
}

void JugadorBatalla::setX(){
    if(xFinal>=5){
        return;
    }
    xFinal+=(vx*t)-(0.5*pow(t,2));
    if(fila==168 or fila==252) xFinal=0;
}

void JugadorBatalla::Actualizacion()
{
    /*La imagen sprite del jugador es una imagen que estaba dividida por filas y por columnas, cada fila determina un movimiento o
    accion diferente hecha por el jugador, y las columnas son frames que permiten que esa accion se vea con movimiento, entonces mediante
    un timer estaremos constantemente interactuando en las columnas de determinada fila para asi ir generando una animacion fluida y
    continua.*/
    if(columnas >= 336 or (fila >= 672 and columnas >= 168))//El archivo consta de 6 columnas de 84x84, cuando se llegue a la sexta columna se iniciara de nuevo
    {
        columnas = 84;
    }
    else{
        columnas += 84;
    }
    this->update(-ancho/2,-alto/2,ancho,alto);/*La funcion update constantemente actualiza el boundingRect del jugador para que su
    origen siempre sea la mitad de la imagen actual.*/
}

void JugadorBatalla::moveLeft()
{
    if (banLeft)
    {
        if(fila!=420 and fila!=168) xFinal=0;
        fila=420;
        if(x()>0){
        setPos(x()-xFinal,y());
        }
    }
}

void JugadorBatalla::moveRight()
{
    if (banRight)
    {
        if(fila!=504 and fila!=252) xFinal=0;
        fila = 504;
        if(x()<930){
        setPos(x()+xFinal,y());
    }
    }
}
