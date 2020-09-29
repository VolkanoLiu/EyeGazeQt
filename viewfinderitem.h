#ifndef VIEWFINDERITEM_H
#define VIEWFINDERITEM_H

#include <QGraphicsVideoItem>

class ViewfinderItem : public QGraphicsVideoItem
{
public:
    ViewfinderItem();
    QRectF boundingRect() const override;
};

#endif // VIEWFINDERITEM_H
