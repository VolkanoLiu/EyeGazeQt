#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCameraViewfinderSettings>
#include <iostream>
#include <QGLWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Get all the cameras' info
    QCameraInfo front_cam_info;
    const QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    for(auto item : cameras) {
        std::cout << item.deviceName().toStdString() << std::endl;
        if(item.deviceName() == "/dev/video0") {
            front_cam_info = item;
            break;
        }
    }


    // Auto generated initialization code
    ui->setupUi(this);

    // Use OpenGL
    ui->graphicsView->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    // Configure scene and view
    scene = new QGraphicsScene;
    scene->setSceneRect(0, 0, 800, 600);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setScene(scene);

    // Configure camera and viewfinder item
     camera = new QCamera(front_cam_info);
     VFI = new ViewfinderItem;
     VFI->setScale(2);
     camera->setViewfinder(VFI);
     camera->start();

    // Configure eye cursors
    c_left = new Cursor(QPen(Qt::blue, 10));
    c_left->setPos(128, 128);
    // c_right = new Cursor(QPen(Qt::green, 3));
    // c_right->setPos(256, 256);

    // Add a HUD display
    hud = new HUD;

    // Add all the items
    scene->addItem(VFI);
    scene->addItem(hud);
    scene->addItem(c_left);
    // scene->addItem(c_right);

    // Add AIO Objects
     ob = new AIOObject();
     connect(ob, SIGNAL(updateCursorsDirectly(eye_data_t)), this, SLOT(setCursors(eye_data_t)));
     connect(ob, SIGNAL(setIndicator(char,bool)), hud, SLOT(updateIndicator(char,bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setCursors(eye_data_t data)
{
    int x = (data.l_x + data.r_x) / 2;
    int y = (data.l_y + data.r_y) / 2;
    c_left->setPos(x, y);
    // c_left->setPos(data.l_x, data.l_y);
    // c_right->setPos(data.r_x, data.r_y);
    std::cout << time(nullptr) << std::endl;
}
