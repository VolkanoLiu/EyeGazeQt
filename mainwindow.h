#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QCamera>
#include <QCameraViewfinder>
#include <QTimer>
#include <QGraphicsVideoItem>
#include "viewfinderitem.h"
#include "cursor.h"
#include "aioobject.h"
#include "hud.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void setCursors(eye_data_t);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    Cursor *c_left, *c_right;

    QCamera *camera;
    ViewfinderItem *VFI;

    AIOObject *ob;
    HUD *hud;
};

#endif // MAINWINDOW_H
