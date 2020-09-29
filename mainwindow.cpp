#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCameraViewfinderSettings>
#include <iostream>
#include <QGLWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
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
    // camera = new QCamera();
    // VFI = new ViewfinderItem;
    // VFI->setScale(1);
    // camera->setViewfinder(VFI);
    // camera->start();

    // Configure eye cursors
    c_left = new Cursor(QPen(Qt::red, 3));
    c_left->setPos(128, 128);
    c_right = new Cursor(QPen(Qt::green, 3));
    c_right->setPos(256, 256);

    // Add a HUD display
    hud = new HUD;

    // Add all the items
    // scene->addItem(VFI);
    scene->addItem(hud);
    scene->addItem(c_left);
    scene->addItem(c_right);

    // Add AIO Objects
    // ob = new AIOObject();
    // connect(ob, SIGNAL(updateCursorsDirectly(eye_data_t)), this, SLOT(setCursors(eye_data_t)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setCursors(eye_data_t data)
{
    c_left->setPos(data.l_x, data.l_y);
    c_right->setPos(data.r_x, data.r_y);
    std::cout << time(nullptr) << std::endl;
}
