#include "polygon.h"
#include"line.h"
Polygon::Polygon(int ID_NUM,QString a, int*cf_temp,int LineWidth_temp,QPixmap*pix_temp,int**Gra,int l,int w)

{
    id=ID_NUM;
    algorithm=a;
    cf[0]=cf_temp[0];
    cf[1]=cf_temp[1];
    cf[2]=cf_temp[2];
    cf[3]=cf_temp[3];
     pix=pix_temp;
    pnts=NULL;
     LineWidth=LineWidth_temp;
       gra=Gra;
     Length=l;
     Width=w;
     alive=0;
}
void Polygon::draw(QPixmap*pix_temp)
{
    pix=pix_temp;
    pnts=gra;
    alive=1;
    for(int i=0;i<points.size()-1;i++)
    {
         Line l1(id,points[i].x(),points[i].y(),points[i+1].x(),points[i+1].y(),algorithm,cf,LineWidth,pix,pnts,Length,Width);
    }
}
void Polygon::draw()
{
    for(int i=0;i<points.size()-1;i++)
    {
         Line l1(id,points[i].x(),points[i].y(),points[i+1].x(),points[i+1].y(),algorithm,cf,LineWidth,pix,pnts,Length,Width);
    }
}
void Polygon::translate(int dx, int dy)
{
    for (int i = 0;i < points.size();i++)
    {
        points[i].setX(points[i].x()+dx);
         points[i].setY(points[i].y()+dy);
    }
}
 int Polygon::add_point(int x,int y)
 {

     if(!(x>=0&&x<Length&&y>=0&&y<Width))
     {
         return -1;
     }
    if(points.size()==0)
    {
        points.push_back(QPoint(x,y));

    }else
    {

        if(points.size()>1)
        {
            int a=x-(int)points[0].x();
            int b=y-(int)points[0].y();
            if((a*a+b*b)<=100)
            {
                points.push_back(QPoint((int)points[0].x(),(int)points[0].y()));
                int n=points.size();
                draw();
                return 1;
            }
            else
            {
                points.push_back(QPoint(x,y));
            }
        }else
        {
            points.push_back(QPoint(x,y));

        }

    draw();
    }
    return 0;

 }
 void Polygon::scale_one(double X, double Y, float r,int&x,int&y)
 {
     x = (double)x*r + X * (1 - r)+0.5;
     y = (double)y*r + Y * (1 - r)+0.5;
 }
 void Polygon::scale(int X, int Y, float r)
 {
     for (int i = 0;i < points.size();i++)
     {
     scale_one(X, Y, r, points[i].rx(), points[i].ry());
    }
 }
 void Polygon::rotate_one(double X, double Y, double R, int&x, int&y)
 {
     double cos_r = cos(R*pi_c);
     double sin_r = sin(R*pi_c);
     int x1 = x;
     int y1 = y;
     x = X + ((double)x1 - X)*cos_r - ((double)y1 - Y)*sin_r+0.5;
     y = Y + ((double)x1 - X)*sin_r + ((double)y1 - Y)*cos_r+0.5;
 }
 void Polygon::rotate(int X, int Y, double R)
 {
     for (int i = 0;i < points.size();i++)
     {
     rotate_one(X, Y, R, points[i].rx(), points[i].ry());
    }
 }

