#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "checkerview.h"
#include "networkmanager.h"
#include "gamestate.h"
#include "consts.h"
#include "checkerview.h"

namespace Ui {
    class MainWindow;
}

/**
@brief     Klasa glownego okna.
@details   Zapewnia obsluge okna glownego. Klikniec menu, odswiezanie stanu punktowego.
@author    Piotr Jastrzebski
@author    Lukasz Tomczak*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /** Konstruktor.
    @param *parent Wskaznik na rodzica.*/
    explicit MainWindow(QWidget *parent);

    ~MainWindow();

    /** Ustawia scene.
    @param *board Wskaznik na plansze.*/
    void setScene(QGraphicsScene *board);
private:
    Ui::MainWindow *ui;
    CheckerView view;
    NetworkManager *nm;
    GameState gs;

private slots:
    void aboutWindow();
    void youLost();
    void youWon();
    void createGame();
    void joinToGame();
signals:
    /** Wywoluje sygnal obslugi sytuacji, gdy gracz wygral.*/
    void won();

    /** Wywoluje sygnal obslugi sytuacji, gdy gracz przegral.*/
    void lost();

public slots:
    /** Zwieksza stan punktow gracza "bialego".
    @return "true", gdy "bialy" wygral, w przeciwnym wypadku "false". */
    bool whitePointsInc(bool ifTest);

    /** Zwieksza stan punktow gracza "czarnego".
    @return "true", gdy "czarny" wygral, w przeciwnym wypadku "false". */
    bool blackPointsInc(bool ifTest);

    /** Obsluguje nadany ruch.
    @param move Ruch w postaci R1C1R2C2R3C3. [1-skad, 2-dokad, 3-opcjonalnie, co zbite, .-znak konca].*/
    void sendMove(QString move);

    /** Obsluguje odebrany ruch.
    @param move Ruch w postaci R1C1R2C2R3C3. [1-skad, 2-dokad, 3-opcjonalnie, co zbite, .-znak konca].*/
    void receiveMove(QString move);
};

#endif // MAINWINDOW_H
