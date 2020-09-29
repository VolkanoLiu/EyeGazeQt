#include "aioobject.h"
#include <QMetaType>

AIOObject::AIOObject(QObject *parent) : QObject(parent), resolution(2560, 1440)
{
    th = new AIOThread;
    qRegisterMetaType<eye_data_t>("EyeData");
    qRegisterMetaType<timeval>("time_t");
    connect(th, SIGNAL(dataUpdated(eye_data_t, timeval)), this, SLOT(updateData(eye_data_t, timeval)));
    th->start();
}

#define CHECK_X_INRANGE(x) (x < -1000 || x > 3560) ? 0 : 1
#define CHECK_Y_INRANGE(y) (y < -1000 || y > 2440) ? 0 : 1

#define CHECK_POINT_INRANGE(xm, xM, ym, yM) \
[](QPointF a)->bool{                                                          \
    if(a.x() >= 0 && a.x() < 0 && a.y() >= 0 && a.y() < 0) {   \
        return true;                                    \
    } else {                                            \
        return false;                                   \
    }                                                   \
}

#define DEF_VALID_POINT_NUM(dir, xm, xM, ym, yM) int valid_num_##dir =  \
    std::count_if(former_points.begin(), former_points.end(), CHECK_POINT_INRANGE(xm, xM, ym, yM))

//#define CHECK_POINT_INRANGE(xm, xM, ym, yM) \
//    xm > xM

void AIOObject::updateData(eye_data_t data, time_t time)
{
    // TODO:PointF
    Q_UNUSED(time);
    // find if there are any wrong data
    if(!CHECK_X_INRANGE(data.l_x) && !CHECK_X_INRANGE(data.r_x)){
        if(former_points.size() == 20){
            former_points.pop_front();
            former_points.push_back(QPointF(9999, 9999));
        } else {
            former_points.push_back(QPointF(9999, 9999));
        }
        return;
    }
    if(!CHECK_X_INRANGE(data.l_x)){
        data.l_x = data.r_x;
    }
    if(!CHECK_X_INRANGE(data.r_x)){
        data.r_x = data.l_x;
    }
    if(!CHECK_Y_INRANGE(data.l_y) && !CHECK_Y_INRANGE(data.r_y)){
        if(former_points.size() == 20){
            former_points.pop_front();
            former_points.push_back(QPointF(9999, 9999));
        } else {
            former_points.push_back(QPointF(9999, 9999));
        }
        return;
    }
    if(!CHECK_Y_INRANGE(data.l_y)){
        data.l_y = data.r_y;
    }
    if(!CHECK_Y_INRANGE(data.r_y)){
        data.r_y = data.l_y;
    }
    data.l_y = 1440 - data.l_y;
    data.r_y = 1440 - data.r_y;
    if(former_points.size() == 20){
        former_points.pop_front();
        former_points.push_back(QPointF(data.l_x, data.l_y));
    } else {
        former_points.push_back(QPointF(data.l_x, data.l_y));
    }
    emit updateCursorsDirectly(data);

    // Control the motor

    // Count the valid points
    int valid_num = std::count_if(former_points.begin(), former_points.end(), CHECK_POINT_INRANGE(0, 720, 420, 1840));
    DEF_VALID_POINT_NUM(l, 0, 720, 420, 1840);
    DEF_VALID_POINT_NUM(r, 1840, 2560, 420, 1840);
    DEF_VALID_POINT_NUM(u, 720, 1840, 0, 420);
    DEF_VALID_POINT_NUM(d, 720, 1840, 1020, 1440);
    DEF_VALID_POINT_NUM(lu, 0, 720, 0, 420);
    DEF_VALID_POINT_NUM(ru, 1840, 2560, 0, 420);
    DEF_VALID_POINT_NUM(ld, 0, 720, 1020, 1440);
    DEF_VALID_POINT_NUM(rd, 1840, 2560, 1020, 1440);
    DEF_VALID_POINT_NUM(r, 420, 1020, 720, 1840);
    DEF_VALID_POINT_NUM(oor, 0, 2560, 0, 1440);

    if(valid_num_l > 16) {
        // do something ...
    }
    if(valid_num_r > 16) {
        // do something ...
    }
    if(valid_num_u > 16) {
        // do something ...
    }
    if(valid_num_d > 16) {
        // do something ...
    }


//    int valid_num = std::count_if(former_points.begin(), former_points.end(), [](QPointF a){
//        if(a.x() >= 0 && a.x() < 720 && a.y() >= 420 && a.y() < 1840) {
//            return true;
//        } else {
//            return false;
//        }
//    });
}
