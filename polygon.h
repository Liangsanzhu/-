#ifndef POLYGON_H
#define POLYGON_H
#include"all.h"

class Polygon
{
public:
    Polygon(int ID_NUM,QString a, int*cf_temp,int LineWidth,QPixmap*pix,int**Gra,int l,int w);
    QPixmap*pix;

    int id;
    void draw(QPixmap*pix_temp);
    void draw();

    /*绘制算法*/
    QString algorithm;

    /*颜色*/
    int cf[4];

    /*画布大小*/
    int Length;
    int Width;
    /*图元状态*/
    int alive=0;
    int**pnts;
    int**gra;

    /*线宽*/
    int LineWidth;
    QVector<QPoint> points;
    int add_point(int x,int y);
    void translate(int dx, int dy);
    /*缩放*/
    void scale_one(double X, double Y, float r,int&x,int&y);
    void scale(int X, int Y, float r);
    /*旋转*/
    void rotate_one(double X, double Y, double R, int&x, int&y);
    void rotate(int X, int Y, double R);

};

#endif // POLYGON_H
