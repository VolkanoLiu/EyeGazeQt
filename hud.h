#ifndef HUD_H
#define HUD_H
#include <QGraphicsItem>
#include <QPainter>
#include <QPen>
#include "directionindicator.h"

class HUD : public QGraphicsItem
{
public:
    HUD();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
private:
    DirectionIndicator *l, *r, *u, *d, *lu, *ld, *ru, *rd;
};

#endif // HUD_H
