#include "checkerview.h"

CheckerView::CheckerView() :
    QGraphicsView()
{
    setRenderHint(QPainter::Antialiasing);
}

void CheckerView::resizeEvent(QResizeEvent * event)
{
    QGraphicsView::resizeEvent(event);
    fitInView(sceneRect(), Qt::KeepAspectRatio);
}

void CheckerView::setScene(QGraphicsScene * scene)
{
    QGraphicsView::setScene(scene);
}
