#ifndef CURSOR_H
#define CURSOR_H
#include <QGraphicsItem>
#include <QPainter>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>


class Cursor : public QGraphicsItem
{
public:
    Cursor();
    Cursor(QPen p);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    // void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);

private:
    QPen pen;
};

#endif // CURSOR_H
