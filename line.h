#ifndef LINE_H
#define LINE_H

#include"all.h"



class Line
{

public:
     ~Line();
    /*ID*/
    int id;
    QPixmap*pix;
    int**pnts;

    void draw_virtual();

    int static step;
    /*端点*/
    int x1;
    int y1;
    int x2;
    int y2;
    int alive;


    /*绘制算法*/
    QString algorithm;

    /*颜色*/
    int cf[4];

    /*线宽*/
    int LineWidth;

    /*初始化*/

    Line(int ID_NUM,int X1, int Y1, int X2, int Y2, QString a, int*cf_temp,int LineWidth,QPixmap*pix,int**Gra,int l,int w);
    Line(int X1, int Y1, int X2, int Y2, QString a, int*cf_temp,int LineWidth_temp,QPixmap&pix_temp);
    Line(int X1, int Y1, int X2, int Y2, QPixmap*pix_temp);
    /*平移*/
    void translate(int dx, int dy);
    /*剪裁*/
    void getcs_code(int x, int y, int xmin, int xmax, int ymin, int ymax, int&rc);
    void cs_code(int X1,int Y1,int X2,int Y2);
    void get_u(int X1, int Y1, int X2, int Y2);
    void get_lb(int X1, int Y1, int X2, int Y2);
    void clip(int X1, int Y1,int X2,int Y2,QString algorithm);
    /*旋转*/
    void rotate_one(double X, double Y, double R, int&x, int&y);
    void rotate(int X, int Y, int R);
    /*缩放*/
    void scale_one(double X, double Y, float r,int&x,int&y);
    void scale(int X, int Y, float r);
    /*绘制*/
    void draw();
    void draw(QPixmap&pix_temp);
    void Add(int x,int y);
    int Length,Width;
};

#endif // LINE_H
