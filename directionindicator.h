#ifndef DIRECTIONINDICATOR_H
#define DIRECTIONINDICATOR_H

#include <QGraphicsItem>
#include <QPainter>
#include <QPen>
#include <QGraphicsSceneMouseEvent>

typedef enum {
    DI_BRAKE = 0,
    DI_LD,
    DI_D,
    DI_RD,
    DI_L,
    DI_STOP,
    DI_R,
    DI_LU,
    DI_U,
    DI_RU
} directions_t;

class DirectionIndicator : public QGraphicsItem
{
public:
    explicit DirectionIndicator(QGraphicsItem *parent);
    DirectionIndicator(directions_t dir, QGraphicsItem *parent);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setIFocus(bool focus);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    directions_t direction = DI_L;
    QPen pen;

};

#endif // DIRECTIONINDICATOR_H
