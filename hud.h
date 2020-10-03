#ifndef HUD_H
#define HUD_H
#include <QGraphicsItem>
#include <QPainter>
#include <QPen>
#include "directionindicator.h"

class HUD : public QGraphicsObject
{
    Q_OBJECT
public:
    HUD();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    DirectionIndicator *l, *r, *u, *d, *lu, *ld, *ru, *rd;
public slots:
    void updateIndicator(char s, bool b);
private:

};

#endif // HUD_H
