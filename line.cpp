#include "line.h"

int Line::step=8 ;
void Line::Add(int x,int y)
{


    if(x>=0&&x<Length&&y>=0&&y<Width&&pnts!=NULL)
    {
     pnts[x][y]=id;
     //qDebug()<<"x="<<x<<" y="<<y;
   }
}
Line:: ~Line()
{}
/*绘制*/
void Line::draw_virtual()
{
    QPainter pp(pix);    // 根据鼠标指针前后两个位置就行绘制直线
    QPen pen_temp(Qt::gray);
    pen_temp.setWidth(1);
    pp.setPen(pen_temp);
    if (x1 == x2)
    {
        if (y1 < y2)
        {
            for (int a = y1;a <= y2;a++)
            {
                if((a/step)%2==0)
                 pp.drawPoint(x1, a);
            }
        }
        else
        {
            for (int a = y2;a <= y1;a++)
            {
                if((a/step)%2==0)
                 pp.drawPoint(x1, a);
            }
        }
    }
    if (y1 == y2)
    {
        if (x1 < x2)
        {
            for (int a = x1;a <= x2;a++)
            {
                if((a/step)%2==0)
                 pp.drawPoint(a,y1);
            }
        }
        else
        {
            for (int a = x2;a <= x1;a++)
            {
                if((a/step)%2==0)
                 pp.drawPoint(a,y1);
            }
        }
    }
}
void Line::draw()
{
    QPainter pp(pix);    // 根据鼠标指针前后两个位置就行绘制直线
    QPen pen_temp(QColor(cf[0], cf[1], cf[2], cf[3]));
    pen_temp.setWidth(LineWidth);
    pp.setPen(pen_temp);
    if (x1 == x2)
    {
        if (y1 < y2)
        {
            for (int a = y1;a <= y2;a++)
            {
                 pp.drawPoint(x1, a);
                 Add(x1,a);
            }
        }
        else
        {
            for (int a = y2;a <= y1;a++)
            {
                 pp.drawPoint(x1, a);
                 Add(x1,a);
            }
        }
    }
    else
    {
        double m = (double)(y2 - y1) / (double)(x2 - x1);
        double b = (double)((double)y1 - m * (double)x1);
        if (algorithm == "DDA")
        {

            if (m > 1 || m < -1)
            {
                if (y1 < y2)
                {
                    double x_temp = x1;
                    for (int i = y1;i <= y2;i++)//以一个像素点为增量
                    {
                         pp.drawPoint(x_temp+0.5, i);
                         Add(x_temp+0.5,i);
                        x_temp += (1 / m);//坐标值迭代累加
                    }
                }
                else
                {
                    double x_temp = x2;
                    for (int i = y2;i <= y1;i++)
                    {
                        pp.drawPoint(x_temp+0.5, i);
                        Add(x_temp+0.5,i);
                        x_temp += (1 / m);
                    }
                }
            }
            else
            {
                if (x1 < x2)
                {
                    double y_temp = y1;
                    for (int i = x1;i <= x2;i++)
                    {
                        pp.drawPoint(i,y_temp+0.5);
                        Add(i,y_temp+0.5);
                        y_temp += m;
                    }
                }
                else
                {
                    double y_temp = y2;
                    for (int i = x2;i <= x1;i++)
                    {
                         pp.drawPoint(i,y_temp+0.5);
                         Add(i,y_temp+0.5);
                        y_temp += m;                    }
                }
            }
        }
        else if(algorithm=="Bresenham")
        {
            if (m<1 && m>-1)
            {
                if (x1 < x2)
                {
                    int x_temp = x1;
                    int y_temp = y1;
                    int deltax = abs(x2 - x1);
                    int deltay = abs(y2 - y1);
                    int p_temp = 2 * deltay - deltax;
                    pp.drawPoint(x_temp, y_temp);
                    Add(x_temp,y_temp);
                    for (int i = x1 + 1;i <= x2;i++)
                    {
                        if (p_temp < 0)
                        {
                            p_temp += 2 * deltay;
                            pp.drawPoint(i, y_temp+0.5);
                             Add(i,y_temp+0.5);
                        }
                        else
                        {
                            p_temp += 2 * deltay - 2 * deltax;
                            if (m > 0)
                                y_temp++;
                            else
                                y_temp--;
                             pp.drawPoint(i, y_temp+0.5);
                               Add(i,y_temp+0.5);
                        }
                    }

                }
                else
                {
                    int x_temp = x2;
                    int y_temp = y2;
                    int deltax = abs(x2 - x1);
                    int deltay = abs(y2 - y1);
                    int p_temp = 2 * deltay - deltax;
                    pp.drawPoint(x_temp, y_temp);
                    for (int i = x2 + 1;i <= x1;i++)
                    {
                        if (p_temp < 0)
                        {
                            p_temp += 2 * deltay;
                             pp.drawPoint(i, y_temp+0.5);
                              Add(i,y_temp+0.5);
                        }
                        else
                        {
                            p_temp += 2 * deltay - 2 * deltax;
                            if (m > 0)
                                y_temp++;
                            else
                                y_temp--;
                            pp.drawPoint(i, y_temp+0.5);
                              Add(i,y_temp+0.5);
                        }
                    }
                }

            }
            else
            {
                if (y1 < y2)
                {
                    int x_temp = x1;
                    int y_temp = y1;
                    int deltax = abs(x2 - x1);
                    int deltay = abs(y2 - y1);
                    int p_temp = 2 * deltax - deltay;
                     pp.drawPoint(x_temp, y_temp);
                    for (int i = y1 + 1;i <= y2;i++)
                    {
                        if (p_temp < 0)
                        {
                            p_temp += 2 * deltax;
                             pp.drawPoint(x_temp+0.5, i);
                               Add(x_temp+0.5,i);
                        }
                        else
                        {
                            p_temp += 2 * deltax - 2 * deltay;
                            if (m > 0)
                                x_temp++;
                            else
                                x_temp--;

                             pp.drawPoint(x_temp+0.5, i);
                              Add(x_temp+0.5,i);
                        }
                    }

                }
                else
                {
                    int x_temp = x2;
                    int y_temp = y2;
                    int deltax = abs(x2 - x1);
                    int deltay = abs(y2 - y1);
                    int p_temp = 2 * deltax - deltay;
                     pp.drawPoint(x_temp, y_temp);
                    for (int i = y2 + 1;i <= y1;i++)
                    {
                        if (p_temp < 0)
                        {
                            p_temp += 2 * deltax;
                             pp.drawPoint(x_temp+0.5, i);
                              Add(x_temp+0.5,i);
                        }
                        else
                        {
                            p_temp += 2 * deltax - 2 * deltay;
                            if (m > 0)
                                x_temp++;
                            else
                                x_temp--;
                             pp.drawPoint(x_temp+0.5, i);
                               Add(x_temp+0.5,i);
                        }
                    }
                }

            }

        }
    }

}

/*初始化*/

Line:: Line(int ID_NUM,int X1, int Y1, int X2, int Y2, QString a, int*cf_temp,int LineWidth_temp,QPixmap*pix_temp,int**Gra,int l,int w)
{

    id=ID_NUM;
    x1 = X1;
    y1 = Y1;
    x2 = X2;
    y2 = Y2;
    algorithm = a;
    cf[0]=cf_temp[0];
    cf[1]=cf_temp[1];
    cf[2]=cf_temp[2];
    cf[3]=cf_temp[3];
     pix=pix_temp;
     pnts=Gra;
    alive=1;
     LineWidth=LineWidth_temp;

     Length=l;
     Width=w;
      draw();
}

Line::Line(int X1, int Y1, int X2, int Y2, QString a, int*cf_temp,int LineWidth_temp,QPixmap&pix_temp)
{

    x1 = X1;
    y1 = Y1;
    x2 = X2;
    y2 = Y2;
    algorithm = a;
    cf[0]=cf_temp[0];
    cf[1]=cf_temp[1];
    cf[2]=cf_temp[2];
    cf[3]=cf_temp[3];
     pix=&pix_temp;
   pnts=NULL;
     LineWidth=LineWidth_temp;
    draw();
}
Line::Line(int X1, int Y1, int X2, int Y2, QPixmap*pix_temp)
{

    x1 = X1;
    y1 = Y1;
    x2 = X2;
    y2 = Y2;
     pix=pix_temp;
   pnts=NULL;
    draw_virtual();
}

/*平移*/
void Line::translate(int dx, int dy)
{
    x1 += dx;
    y1 +=dy;
    x2 += dx;
    y2 +=dy;
}

/*剪裁*/
void Line::getcs_code(int x, int y, int xmin, int xmax, int ymin, int ymax, int&rc)
{
    if (x < xmin)
    {
        rc |= 1;
    }

    if (x > xmax)
    {
        rc |= 2;
    }
    if (y < ymin)
    {
        rc |= 4;
    }
    if (y > ymax)
    {
        rc |= 8;
    }
}
void Line::cs_code(int X1,int Y1,int X2,int Y2)
{
    int rc1 = 0;
    int	rc2 = 0;
    int xmin = X1 < X2 ? X1 : X2;
    int xmax = X1 > X2 ? X1 : Y2;
    int ymin = Y1 < Y2 ? Y1 : Y2;
    int ymax = Y1 > Y2 ? Y1 : Y2;
    getcs_code(x1, y1, xmin, xmax, ymin, ymax, rc1);
    getcs_code(x2, y2, xmin, xmax, ymin, ymax, rc2);
    if ((rc1 | rc2) == 0)
        return;
    else if ((rc1&rc2) != 0)
    {
        x2 = x1;
        y2 = y1;
    }
    else
    {
        if (x1 == x2)
        {
            if (rc1 != 0)
            {
                if (rc1 == 8)
                    y1 = ymax;
                else
                    y1 = ymin;
            }
            if (rc2 != 0)
            {
                if (rc2 == 8)
                    y2 = ymax;
                else
                    y2 = ymin;
            }
        }
        else if (y1 == y2)
        {
            if (rc1 != 0)
            {
                if (rc1 == 1)
                {
                    x1 = xmin;
                }
                else
                {
                    x1 = xmax;
                }
            }
            if (rc2 != 0)
            {
                if (rc2 == 1)
                {
                    x2 = xmin;
                }
                else
                {
                    x2 = xmax;
                }
            }
        }
        else
        {
            double k = (double)(y1 - y2) / (double)(x1 - x2);
            /*left*/
            double yleft = k * (double)(xmin - x1) + (double)y1;
            if (yleft >= ymin && yleft <= ymax)
            {
                if ((rc1 & 1) == 1)
                {
                    y1 = yleft;
                    x1 = xmin;
                }
                if ((rc2 & 1) == 1)
                {
                    y2 = yleft;
                    x2 = xmin;
                }
            }
            double yright = k * (double)(xmax - x1) + (double)y1;
            if (yright >= ymin && yright <= ymax)
            {
                if ((rc1 & 2) == 2)
                {
                    y1 = yright;
                    x1 = xmax;
                }
                if ((rc2 & 2) == 2)
                {
                    y2 = yright;
                    x2 = xmax;
                }
            }
            double xbottom = (ymin-y1)/k+x1;
            if (xbottom >= xmin && xbottom <= ymax)
            {
                if ((rc1 & 4) == 4)
                {
                    y1 = ymin;
                    x1 = xbottom;
                }
                if ((rc2 & 4) == 4)
                {
                    y2 = ymin;
                    x2 = xbottom;
                }
            }
            double xtop = (ymax - y1) / k + x1;
            if (xtop >= xmin && xtop <= ymax)
            {
                if ((rc1 & 8) == 8)
                {
                    y1 = ymax;
                    x1 = xtop;
                }
                if ((rc2 & 8) == 8)
                {
                    y2 = ymax;
                    x2 = xtop;
                }
            }
        }
    }
}
void Line::get_u(int X1, int Y1, int X2, int Y2)
{
    int xmin = X1 < X2 ? X1 : X2;
    int xmax = X1 > X2 ? X1 : Y2;
    int ymin = Y1 < Y2 ? Y1 : Y2;
    int ymax = Y1 > Y2 ? Y1 : Y2;
    int p[4];
    p[0] = x1 - x2;
    p[1] = x2 - x1;
    p[2] = y1 - y2;
    p[3] = y2 - y1;
    int q1 = x1 - xmin;
    int q2 = xmax - x1;
    int q3 = y1 - ymin;
    int q4 = ymax - y1;
    double u1 = 0;
    double u2 = 1;
    double I[4];
    I[0] = (double)q1 / (double)p[0];
    I[1] = (double)q2 / (double)p[1];
    I[2] = (double)q3 / (double)p[2];
    I[3] = (double)q4 / (double)p[3];
    for (int i = 0;i < 4;i++)
    {
        if (p[i] > 0)
        {

            u2 = u2< I[i]?u2:I[i];
        }
        else
        {
            u1 = u1>I[i]?u1:I[i];
        }
    }

    if (u1 > u2)
        return;
    else
    {
        if (u2 <= 1 && u2 >= 0)
        {
            x2 = x1 + u2 * p[1];
            y2 = y1 + u2 * p[3];
        }
        if (u1 >= 0 && u1 <= 1)
        {
            x1 = x1 + u1 * p[1];
            y1 = y1 + u1 * p[3];
        }

    }
}
void Line::get_lb(int X1, int Y1, int X2, int Y2)
{
    int xmin = X1 < X2 ? X1 : X2;
    int xmax = X1 > X2 ? X1 : Y2;
    int ymin = Y1 < Y2 ? Y1 : Y2;
    int ymax = Y1 > Y2 ? Y1 : Y2;
    if (x1 == x2 || y1 == y2)
    {
        if (x1 == x2)
        {
            if (y1 > ymax)
            {
                y1 = ymax;
            }
            else if (y1 < ymin)
            {
                y1 = ymin;
            }
            if (y2 > ymax)
            {
                y2 = ymax;
            }
            else if (y2 < ymin)
            {
                y2 = ymin;
            }
        }
        if (y1 == y2)
        {
            if (x1 > xmax)
            {
                x1 = xmax;
            }
            else if (x1 < xmin)
            {
                x1 = xmin;
            }
            if (x2 > xmax)
            {
                x2 = xmax;
            }
            else if (x2 < xmin)
            {
                x2 = xmin;
            }
        }
    }
    else
    {
        get_u(X1, Y1, X2, Y2);
    }
}
void Line::clip(int X1, int Y1,int X2,int Y2,QString algorithm)
{
    int xmin = X1 < X2 ? X1 : X2;
    int xmax = X1 > X2 ? X1 : Y2;
    int ymin = Y1 < Y2 ? Y1 : Y2;
    int ymax = Y1 > Y2 ? Y1 : Y2;
    if (algorithm == "Cohen-Sutherland")
    {
        int rc1 = 0;
        int rc2 = 0;
        cs_code(X1, Y1, X2, Y2);
    }
    else if (algorithm == "Liang-Barsky")
    {
        get_lb(X1, Y1, X2, Y2);
    }
}

/*旋转*/
void Line::rotate_one(double X, double Y, double R, int&x, int&y)
{
    double cos_r = cos(R*pi_c);
    double sin_r = sin(R*pi_c);
    int x1 = x;
    int y1 = y;
    x = X + ((double)x1 - X)*cos_r - ((double)y1 - Y)*sin_r+0.5;
    y = Y + ((double)x1 - X)*sin_r + ((double)y1 - Y)*cos_r+0.5;
}
void Line::rotate(int X, int Y, int R)
{
    rotate_one(X, Y, R, x1, y1);
    rotate_one(X, Y, R, x2, y2);
}

/*缩放*/
void Line::scale_one(double X, double Y, float r,int&x,int&y)
{
    x = (double)x*r + X * (1 - r)+0.5;
    y = (double)y*r + Y * (1 - r)+0.5;
}
void Line::scale(int X, int Y, float r)
{
    scale_one(X, Y, r, x1, y1);
    scale_one(X, Y, r, x2, y2);
}
