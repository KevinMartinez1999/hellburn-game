#ifndef MAPA_GAMEPLAY_H
#define MAPA_GAMEPLAY_H

#include <QWidget>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <fstream>
#include <iostream>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QMediaPlayer>
#include <QPushButton>
#include <QLabel>
#include <QList>
#include <QMediaPlaylist>
#include <QMessageBox>
#include "jugador.h"

using namespace std;

namespace Ui {
class Mapa_GamePlay;
}

class Mapa_GamePlay : public QWidget
{
    Q_OBJECT

public:
    explicit Mapa_GamePlay(QWidget *parent = nullptr);
    ~Mapa_GamePlay();

    void CargarPartida();

    //Funciones detectoras de del teclado
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private: //Atributos de la clase
    Ui::Mapa_GamePlay *ui;
    QMediaPlayer botonSound, ambiente, jugadorMuerto;
    QTimer timer, dead;
    QPushButton boton;
    QString nombre;
    QMediaPlaylist lista;
    QCursor cursor;
    QPixmap Pixmap_Cursor;
    QGraphicsScene *escena;
    QGraphicsPixmapItem * muros;
    QGraphicsPixmapItem *mapa;
    QGraphicsPixmapItem *objetos;  
    QLabel *aviso,*advertencia;
    int BossesMuertos;
    int PosX0,PosY0,PosX02,PosY02,cont=0;
    int Xpos,YPos;
    int EnemigosTotales;
    bool pj2,freeze,tutorial;

 private slots:    
    void Tutorial();
    void Nivel();
    void spawn();
    void ingreso_batalla();
    void Contador_Enemigos();
    void ActualizarEscena(); //Centra constantemente la grafica en el jugador
    void verificar_muerte();
    void on_Opciones_clicked();
    void Cerrar_Ventana();

};

#endif // MAPA_GAMEPLAY_H
