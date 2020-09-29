#ifndef DIRECTIONINDICATOR_H
#define DIRECTIONINDICATOR_H

#include <QGraphicsItem>
#include <QPainter>
#include <QPen>
#include <QGraphicsSceneMouseEvent>

typedef enum {
    DI_L = 0,
    DI_R,
    DI_U,
    DI_D,
    DI_LU,
    DI_RU,
    DI_LD,
    DI_RD
} directions_t;

class DirectionIndicator : public QGraphicsItem
{
public:
    explicit DirectionIndicator(QGraphicsItem *parent);
    DirectionIndicator(directions_t dir, QGraphicsItem *parent);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    directions_t direction = DI_L;
    QPen pen;
    void setIFocus(bool focus);
};

#endif // DIRECTIONINDICATOR_H
