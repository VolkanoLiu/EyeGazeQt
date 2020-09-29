#include "viewfinderitem.h"

ViewfinderItem::ViewfinderItem()
{
    setSize(QSizeF(1280, 720));
}

QRectF ViewfinderItem::boundingRect() const
{
    return QRectF(0, 0, 1280, 720);
}
