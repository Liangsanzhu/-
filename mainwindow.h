#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPainter>
#include <QColorDialog>
#include<QGridLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QTime>
#include <QDir>
#include <QFile>
#include"line.h"
#include"polygon.h"
#include"all.h"
#include"set_canvas.h"
#include"curve.h"
#include"ellipse.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
enum STATE{STATE_PEN,STATE_LINE,STATE_POLY,STATE_ELLI,STATE_CURVE,STATE_PICK};
enum Type {line_info, ellipse_info, polygon_info, curve_info};

public:
static int ID_NUM;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void Canvas(int x,int y);
    void Create_Toolbar();
    static int height_offset;
    static int width_offset;

    int Color[4];//颜色
    int LineWidth;//线宽
    int Length;//长度
    int Width;//宽度
    /*图元存储*/
    QMap<int,Type> Gra;//根据ID找类型
    QMap<int, Line*> M_line;
    QMap<int, Ellipse*> M_ellipse;
    QMap<int, Polygon*> M_polygon;
    QMap<int, Curve*> M_curve;

    /*画布*/
    int**pnt;//点阵
    Ui::MainWindow *ui;
    QPixmap pix;//画布
    QPixmap p_temp;//临时画布
    QPixmap p_pen;//涂鸦画布
    QPoint lastPoint;//鼠标涂鸦中上一个点
    QPoint endPoint;//鼠标涂鸦中当前点


    /*线段*/
     Line*l;
    int x1,x2,y1,y2;
    int line_step;
    int one;

    /*多边形*/
   Polygon*polygon;
   Polygon*p;


   /*曲线*/
    Curve*curve;


    /*椭圆*/
     Ellipse*elli;
     int e_x;
     int e_y;
     int rx;
     int ry;

   /*选择图元*/
    int finid(int**pnt,int x,int y);//寻找ID
    int pick_choice;//类型
    int pick_state;//剪裁
    int pick_control;//控制点
    QString al;//算法
     int xmin,ymin,xmax,ymax;//选择框
     QVector<QPoint> points;//选择图形的所有点


    /*系统状态*/
    STATE state;
    int ori;


protected:
    void setColor(int r,int g,int b,int a);
    void setLineWidth(int lw);
    void paintEvent(QPaintEvent *);//鼠标涂鸦绘制
    void mousePressEvent(QMouseEvent *);//鼠标按下事件捕捉
    void mouseMoveEvent(QMouseEvent *);//鼠标移动事件捕捉
    void mouseReleaseEvent(QMouseEvent *);//鼠标松开事件捕捉
    void mouseDoubleClickEvent(QMouseEvent *event);
    void change(QPoint&a);//相对坐标转换
    void change(int&x,int&y);
    void paint_all();
   void draw_virtual(QVector<QPoint> a);
    void draw_virtual_v(QVector<QPoint> a);
   bool Check(int x,int y,int x1,int y1);
   int Check_all(int x,int y);
private slots:
    void on_colorBtn_clicked();
    void on_widthSpinBox_editingFinished();
    void on_pushButton_5_clicked();
    void on_pushButton_2_clicked();

    void on_pen_clicked();
    void on_pushButton_9_clicked();

    void on_save_clicked();
    void on_reset_clicked();
    void idraw_canvas(int x,int y);//重置画布子窗口参数接收槽
    void on_ellipse_clicked();
    void on_curve_clicked();
    void on_del_clicked();
    void on_cut_clicked();
    void on_cut_clicked(bool checked);
    void on_al_activated(const QString &arg1);
};

#endif // MAINWINDOW_H
