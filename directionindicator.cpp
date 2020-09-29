#include "directionindicator.h"

DirectionIndicator::DirectionIndicator(QGraphicsItem *parent) : QGraphicsItem(parent), pen(Qt::white, 3)
{
    // setParentItem(parent);
}

DirectionIndicator::DirectionIndicator(directions_t dir, QGraphicsItem *parent) : direction(dir), QGraphicsItem(parent), pen(Qt::white, 3)
{
    // setParentItem(parent);
}

QRectF DirectionIndicator::boundingRect() const
{
    return QRectF(-100, -100, 200, 200);

}

#define DL(a, b, c, d) painter->drawLine(50 * a, 50 * b, 50 * c, 50 * d)

void DirectionIndicator::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(pen);
    switch (direction) {
    case DI_L:
        DL(-2, 0, 2, 0);
        DL(-2, 0, -1, 1);
        DL(-2, 0, -1, -1);
        break;
    case DI_R:
        DL(-2, 0, 2, 0);
        DL(2, 0, 1, 1);
        DL(2, 0, 1, -1);
        break;
    case DI_U:
        DL(0, -2, 0, 2);
        DL(0, -2, -1, -1);
        DL(0, -2, 1, -1);
        break;
    case DI_D:
        DL(0, -2, 0, 2);
        DL(0, 2, -1, 1);
        DL(0, 2, 1, 1);
        break;
    case DI_LU:
        DL(-2, -2, 2, 2);
        DL(-2, -2, -2, -1);
        DL(-2, -2, -1, -2);
        break;
    case DI_LD:
        DL(2, -2, -2, 2);
        DL(-2, 2, -2, 1);
        DL(-2, 2, -1, 2);
        break;
    case DI_RU:
        DL(2, -2, -2, 2);
        DL(2, -2, 1, -2);
        DL(2, -2, 2, -1);
        break;
    case DI_RD:
        DL(-2, -2, 2, 2);
        DL(2, 2, 2, 1);
        DL(2, 2, 1, 2);
        break;
    default:
        break;
    }
}

void DirectionIndicator::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
    setIFocus(true);
}

void DirectionIndicator::setIFocus(bool focus)
{
    if(focus){
        pen = QPen(Qt::red, 20);
    } else {
        pen = QPen(Qt::white, 3);
    }
    update();
}
