#ifndef AIOOBJECT_H
#define AIOOBJECT_H

#include <QObject>
#include <QPoint>
#include <deque>
#include "aiothread.h"

class AIOObject : public QObject
{
    Q_OBJECT
public:
    explicit AIOObject(QObject *parent = nullptr);

signals:
    void updateCursorsDirectly(eye_data_t);
    void setIndicator(char s, bool b);
public slots:
    void updateData(eye_data_t data ,time_t time);
private:
    AIOThread *th;
    bool adjust_top_left = false;
    bool adjust_right_bottom = false;
    float width_offset_a, height_offset_a;
    float width_offset_b, height_offset_b;
    QPoint resolution;
    std::deque<QPointF> former_points;
};

#endif // AIOOBJECT_H
