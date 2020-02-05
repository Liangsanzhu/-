#include "ellipse.h"

Ellipse::Ellipse(int ID_NUM,int x_t,int y_t,int rx_t,int ry_t,int*cf_temp,int LineWidth_temp,QPixmap*pix_temp,int**p_t,int l,int w)
{
    id=ID_NUM;
    cf[0]=cf_temp[0];
    cf[1]=cf_temp[1];
    cf[2]=cf_temp[2];
    cf[3]=cf_temp[3];
     pix=pix_temp;
    pnts=NULL;
    gra=p_t;
     LineWidth=LineWidth_temp;
     Length=l;
     Width=w;
     alive=0;
       x=x_t;
       y=y_t;
       rx=rx_t;
       ry=ry_t;
       draw();
}
Ellipse::Ellipse(int x_t,int y_t,int rx_t,int ry_t,QPixmap*pix_temp,int cf_temp)
{

     pix=pix_temp;
    pnts=NULL;

     alive=0;
       x=x_t;
       y=y_t;
       rx=rx_t;
       ry=ry_t;
       choice=cf_temp;
       draw_virtual();
}
void Ellipse::draw_virtual()
    {
        int rx2 = rx * rx;
        int ry2 = ry * ry;
        int tworx2 = 2 * rx2;
        int twory2 = 2 * ry2;
        int p;
        int x_temp = 0;
        int y_temp = ry;
        int px = 0;
        int py = tworx2 * y_temp;

        draw_Ellipse_v(x_temp, y_temp, x, y);

        p = ry2 - (rx2 * ry) + rx2 / 4;//区域2决策参数的初始值
        while (px < py) {//直到切线斜率为1
            x_temp++;//x增量
            px += twory2;//决策参数中与x有关的部分
            if (p < 0) {//决策参数小于0
                p += ry2 + px;//修改参数
            }
            else {
                y_temp--;//迭代绘制
                py -= tworx2;
                p += ry2 + px - py;
            }
            draw_Ellipse_v(x_temp, y_temp, x, y);//运用平移和对称绘制4个点
        }

        p = ry2 * (x_temp + 1 / 2) * (x_temp + 1 / 2) + rx2 * (y_temp - 1) * (y_temp - 1) - rx2 * ry2;//区域2初始值
        while (y_temp > 0) {
            y_temp--;
            py -= tworx2;
            if (p > 0) {
                p += rx2 - py;
            }
            else {
                x_temp++;
                px += twory2;
                p += rx2 - py + px;
            }
            draw_Ellipse_v( x_temp, y_temp,x, y);
        }
    }
void Ellipse::draw_Ellipse_v(int x,int y, int center_x,int center_y)
{

    QPainter pp(pix);
    QPen pen_temp;
    if(choice==0)
    {
         // 根据鼠标指针前后两个位置就行绘制直线
        pen_temp.setColor(Qt::gray);
        pen_temp.setWidth(1);
        pp.setPen(pen_temp);
     }
    else if(choice==1)
    {
        pen_temp.setColor(Qt::green);
        pen_temp.setWidth(1);
        pp.setPen(pen_temp);
    }

for(int i=-x+center_x+0.5;i<x + center_x-0.5;i++)
{
      pp.drawPoint(i, y + center_y-0.5);
}
for(int i=-x+center_x+0.5;i<x + center_x-0.5;i++)
{
      pp.drawPoint(i, -y + center_y);
}


}
void Ellipse::draw()
    {
        int rx2 = rx * rx;
        int ry2 = ry * ry;
        int tworx2 = 2 * rx2;
        int twory2 = 2 * ry2;
        int p;
        int x_temp = 0;
        int y_temp = ry;
        int px = 0;
        int py = tworx2 * y_temp;

        draw_Ellipse(x_temp, y_temp, x, y);

        p = ry2 - (rx2 * ry) + rx2 / 4;//区域2决策参数的初始值
        while (px < py) {//直到切线斜率为1
            x_temp++;//x增量
            px += twory2;//决策参数中与x有关的部分
            if (p < 0) {//决策参数小于0
                p += ry2 + px;//修改参数
            }
            else {
                y_temp--;//迭代绘制
                py -= tworx2;
                p += ry2 + px - py;
            }
            draw_Ellipse(x_temp, y_temp, x, y);//运用平移和对称绘制4个点
        }

        p = ry2 * (x_temp + 1 / 2) * (x_temp + 1 / 2) + rx2 * (y_temp - 1) * (y_temp - 1) - rx2 * ry2;//区域2初始值
        while (y_temp > 0) {
            y_temp--;
            py -= tworx2;
            if (p > 0) {
                p += rx2 - py;
            }
            else {
                x_temp++;
                px += twory2;
                p += rx2 - py + px;
            }
            draw_Ellipse( x_temp, y_temp,x, y);
        }
    }
void Ellipse::draw(QPixmap*pix_t)
{
    pix=pix_t;
    alive=1;
    pnts=gra;
    draw();
}

    void Ellipse::draw_Ellipse(double x,double y,int center_x,int center_y)
    {

        QPainter pp(pix);    // 根据鼠标指针前后两个位置就行绘制直线
        QPen pen_temp(QColor(cf[0], cf[1], cf[2], cf[3]));
        pen_temp.setWidth(LineWidth);
        pp.setPen(pen_temp);

        pp.drawPoint(x + center_x, y + center_y);
        Add(x + center_x, y + center_y);

        pp.drawPoint(-x + center_x, y + center_y);
        Add(-x + center_x, y + center_y);

        pp.drawPoint(x + center_x, -y + center_y);
        Add(x + center_x, -y + center_y);

        pp.drawPoint(-x + center_x, -y + center_y);
        Add(-x + center_x, -y + center_y);

    }
    void Ellipse::Add(int x,int y)
    {


        if(x>=0&&x<Length&&y>=0&&y<Width&&pnts!=NULL)
        {
         pnts[x][y]=id;
       }
    }
    void Ellipse::translate(int dx,int dy)
     {
            x += dx;
            y +=dy;
     }
    void Ellipse::scale_one(double X, double Y, double r,int&x,int&y)
    {
        x = (double)x*r + X * (1 - r)+0.5;
        y = (double)y*r + Y * (1 - r)+0.5;
    }
    void Ellipse::scale(int X, int Y,double r)
    {

       scale_one(X,Y,r,x,y);
       rx=rx*r;
       ry=ry*r;
    }
    \
    void Ellipse::rotate()
    {
         double temp=rx;
          rx=ry;
          ry=temp;

    }
