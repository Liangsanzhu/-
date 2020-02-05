#ifndef CURVE_H
#define CURVE_H
#include"all.h"

class Curve
{
public:
    Curve(int ID_NUM,QString a, int*cf_temp,int LineWidth_temp,QPixmap*pix_temp,int**Gra,int l,int w);
    QPixmap*pix;

    int id;
    void draw();
    void draw(QPixmap*pix_t);


    /*绘制算法*/
    QString algorithm;

    /*颜色*/
    int cf[4];
    int Length;
    int Width;
    int**pnts;
    int alive=0;


    /*线宽*/
    int LineWidth;
    QVector<QPoint> points;
    int add_point(int x,int y);
    void translate(int dx, int dy);
    /*缩放*/
    void scale_one(double X, double Y, float r,int&x,int&y);
    void scale(int X, int Y, float r);
    void rotate_one(double X, double Y, double R, int&x, int&y);
    void rotate(int X, int Y, double R);


    void Add(int x,int y);
    QPoint bezier(double t);
    double Bkd(double k, double d, double u);
    QPoint B_spline(double u);
};

#endif // CURVE_H
