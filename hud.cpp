#include "hud.h"

HUD::HUD()
{
    l = new DirectionIndicator(DI_L, this);
    l->setPos(360, 1230);
    r = new DirectionIndicator(DI_R, this);
    r->setPos(2200, 1230);
    u = new DirectionIndicator(DI_U, this);
    u->setPos(1280, 210);
    d = new DirectionIndicator(DI_D, this);
    d->setPos(1280, 1230);
    lu = new DirectionIndicator(DI_LU, this);
    lu->setPos(360, 720);
    ru = new DirectionIndicator(DI_RU, this);
    ru->setPos(2200, 720);
//    ld = new DirectionIndicator(DI_LD, this);
//    ld->setPos(360, 1230);
//    rd = new DirectionIndicator(DI_RD, this);
//    rd->setPos(2200, 1230);
}

QRectF HUD::boundingRect() const
{
    return QRectF(0, 0, 2560, 1440);
}

void HUD::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::white, 3));
    painter->drawRect(0, 0, 2560, 1440);
    painter->drawLine(0, 420, 2559, 420);
    painter->drawLine(0, 1020, 2559, 1020);
    painter->drawLine(720, 0, 720, 1439);
    painter->drawLine(1840, 0, 1840, 1439);
}

void HUD::updateIndicator(char s, bool b)
{
    l->setIFocus(false);
    r->setIFocus(false);
    u->setIFocus(false);
    d->setIFocus(false);
    lu->setIFocus(false);
    ru->setIFocus(false);
    switch (s) {
    case '4':
        l->setIFocus(b);
        break;
    case '6':
        r->setIFocus(b);
        break;
    case '8':
        u->setIFocus(b);
        break;
    case '2':
        d->setIFocus(b);
        break;
    case '7':
        lu->setIFocus(b);
        break;
    case '9':
        ru->setIFocus(b);
        break;
    case '1':
        lu->setIFocus(b);
        break;
    case '3':
        lu->setIFocus(b);
        break;
    default:
        break;
    }
    update();
}
