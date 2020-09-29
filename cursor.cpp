#include "cursor.h"

Cursor::Cursor() : pen(QPen(Qt::white, 3))
{
    // setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemIsMovable);
    // setAcceptHoverEvents(true);
    // setAcceptedMouseButtons(Qt::LeftButton);
}

Cursor::Cursor(QPen p)
{
    pen = p;
}

QRectF Cursor::boundingRect() const
{
    return QRectF(-64, -64, 128, 128);
}

void Cursor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(pen);
    painter->drawArc(-64, -64, 128, 128, 0, 360 * 16);
    painter->drawLine(QPointF(0, 46), QPointF(0, 62));
    painter->drawLine(QPointF(0, -46), QPointF(0, -62));
    painter->drawLine(QPointF(46, 0), QPointF(62, 0));
    painter->drawLine(QPointF(-46, 0), QPointF(-62, 0));
}

