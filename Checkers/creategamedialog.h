#ifndef CREATEGAMEDIALOG_H
#define CREATEGAMEDIALOG_H

#include <QDialog>
#include <QIntValidator>
#include <QRegExpValidator>
#include <QHostAddress>

namespace Ui {
class CreateGameDialog;
}

/**
@brief     Tworzy okienko do komunikacji sieciowej.
@details   Zapewnia mozliwosc podania portu i adresu serwera do nasluchu lub podlaczenia.
@author    Piotr Jastrzebski
@author    Lukasz Tomczak*/
class CreateGameDialog : public QDialog
{
    Q_OBJECT
    
public:
    /** Konstruktor.
    @param &dialogTitle Referencja na tytul.
    @param *parent Wskaznik na rodzica.*/
    explicit CreateGameDialog(const QString & dialogTitle, QWidget *parent = 0);

    ~CreateGameDialog();

    /** Zamienia port podany w polu tekstowym na reprezentacje calkowita.
    @return Port w postaci liczby calkowitej.*/
    int getServerPort();

    /** Zamienia adres podany w polu tekstowym na string, argument serwera.
    @return Adres w postaci string.*/
    QHostAddress getServerAddress();

private:
    Ui::CreateGameDialog *ui;
    QIntValidator *portValidator;
    QRegExpValidator *regExpIPValidator;
};

#endif // CREATEGAMEDIALOG_H
