#include <QtGui/QApplication>
#include "mainwindow.h"
#include "tests.h"
#include "board.h"

/** Klasa glowna programu, wywoluje aplikacje i tworzy scene.*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w(0);
    Board* board = new Board(&w);

    w.setScene(board);
    w.show();

    Tests::runTests(board); 

    return a.exec();
}
