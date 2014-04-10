#ifndef CHECKERVIEW_H
#define CHECKERVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>

/**
@brief     Widget do wyswietlania modelu.
@author    Piotr Jastrzebski
@author    Lukasz Tomczak*/
class CheckerView : public QGraphicsView
{
public:
    /** Konstruktor.*/
    explicit CheckerView();

    /** Ustawia model.
    @param *scene Wskaznik na scene.*/
    void setScene(QGraphicsScene * scene);

protected:
    /** Obsluga zdarzenia zmiany rozmiaru okna.
    @param *even Wskaznik na event.*/
    void resizeEvent(QResizeEvent * event);
};

#endif // CHECKERVIEW_H
