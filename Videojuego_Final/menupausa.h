#ifndef MENUPAUSA_H
#define MENUPAUSA_H

#include <QWidget>
#include <QLabel>
#include <QMovie>

namespace Ui {
class MenuPausa;
}

class MenuPausa : public QWidget
{
    Q_OBJECT

public:
    explicit MenuPausa(QWidget *parent = nullptr);
    ~MenuPausa();
    bool cerrar_sesion;

private slots:
    void on_Guardar_clicked();

    void on_Controles_clicked();

    void on_Cerrar_Sesion_clicked();

    void on_Reanudar_clicked();

private:
    Ui::MenuPausa *ui;
    QMovie *movie;
    QLabel *w;
};

#endif // MENUPAUSA_H