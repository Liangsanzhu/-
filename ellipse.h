#ifndef ELLIPSE_H
#define ELLIPSE_H
#include "all.h"

class Ellipse
{
public:
    Ellipse(int ID_NUM,int x_t,int y_t,int rx_t,int ry_t,int*cf_temp,int LineWidth_temp,QPixmap*pix_temp,int**p_t,int l,int w);
    Ellipse(int x_t,int y_t,int rx_t,int ry_t,QPixmap*pix_temp,int cf);
    void draw_virtual();
    void draw_Ellipse_v(int x,int y,int center_x,int center_y);
    QPixmap*pix;

    int id;
    void draw();
    void draw(QPixmap*pix_t);
        int x;//圆心
        int y;
        double rx;//长短轴
        double ry;


    /*颜色*/
    int cf[4];
    int Length;
    int Width;
    int**pnts;
    int**gra;
    int alive=0;
    int choice;


    /*线宽*/
    int LineWidth;

    void translate(int dx, int dy);
    void draw_Ellipse(double x,double y,int center_x,int center_y);
    /*缩放*/
    void scale_one(double X, double Y, double r,int&x,int&y);
    void scale(int X, int Y, double r);
    void rotate();
    void Add(int x,int y);
};

#endif // ELLIPSE_H
