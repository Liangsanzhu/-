#include "curve.h"
void Curve::Add(int x,int y)
{


    if(x>=0&&x<Length&&y>=0&&y<Width&&pnts!=NULL)
    {
     pnts[x][y]=id;
   }
}
Curve::Curve(int ID_NUM,QString a, int*cf_temp,int LineWidth_temp,QPixmap*pix_temp,int**Gra,int l,int w)
{
    id=ID_NUM;
    algorithm=a;
    cf[0]=cf_temp[0];
    cf[1]=cf_temp[1];
    cf[2]=cf_temp[2];
    cf[3]=cf_temp[3];
     pix=pix_temp;
    pnts=Gra;
     LineWidth=LineWidth_temp;
alive=0;
     Length=l;
     Width=w;
}
void Curve::translate(int dx, int dy)
{
    for (int i = 0;i < points.size();i++)
    {
        points[i].setX(points[i].x()+dx);
         points[i].setY(points[i].y()+dy);
    }
}
void Curve::draw()
{

    if (algorithm == "Bezier")
    {
        double delta = 0.001;
        for (double i = 0;i < 1.0;i+=delta)
        {
            QPoint temp=bezier(i);
            if(alive==1)
            Add(temp.x(),temp.y());
        }
    }
    else if (algorithm == "B-spline")
    {
        double delta = 0.001;
        for (double i = 3;i <= points.size();i += delta)//3次B样条
        {
            QPoint temp=B_spline(i);
            if(alive==1)
            Add(temp.x(),temp.y());
        }
    }
}
void Curve::draw(QPixmap*pix_t)
{

    pix=pix_t;
    alive=1;
    if (algorithm == "Bezier")
    {
        double delta = 0.001;
        for (double i = 0;i < 1.0;i+=delta)
        {
            QPoint temp=bezier(i);
            if(alive==1)
            Add(temp.x(),temp.y());
        }
    }
    else if (algorithm == "B-spline")
    {
        double delta = 0.001;
        for (double i = 3;i <= points.size();i += delta)//3次B样条
        {
            QPoint temp= B_spline(i);
            if(alive==1)
            Add(temp.x(),temp.y());
        }
    }
}
int Curve::add_point(int x,int y)
{

    if(!(x>=0&&x<Length&&y>=0&&y<Width))
    {
        return -1;
    }
  else
   {
       points.push_back(QPoint(x,y));

     }

     return 1;

}
QPoint Curve::bezier(double t)
    {
    int n=points.size();
        double*P1 = new double[n];
        for (int i = 0;i < points.size(); i++)
            P1[i] = points[i].x();

        for (int j = 0; j < n - 1; j++)
        {
            for (int i = 0; i < n - j - 1; i++)
            {
                P1[i] = (1.0 - t) * P1[i] + t * P1[i + 1];
            }
        }
        double*P2 = new double[n];
        for (int i = 0;i < n; i++)
            P2[i] = points[i].y();

        for (int j = 0; j < n - 1; j++)
        {
            for (int i = 0; i < n - j - 1; i++)
            {
                P2[i] = (1.0 - t) * P2[i] + t * P2[i + 1];
            }
        }
        QPainter pp(pix);    // 根据鼠标指针前后两个位置就行绘制直线
        QPen pen_temp(QColor(cf[0], cf[1], cf[2], cf[3]));
        pen_temp.setWidth(LineWidth);
        pp.setPen(pen_temp);

        int x=P1[0]+0.5;
        int y=P2[0]+0.5;
        pp.drawPoint(P1[0]+0.5,P2[0]+0.5);
        Add(P1[0]+0.5,P2[0]+0.5);
        delete []P1;
        delete []P2;
        return QPoint(x,y);
}
double  Curve::Bkd(double k, double d, double u)
{
    if (d == 1)
    {
        if (u >= k && u <= k + 1)
            return 1;
        else
            return 0;
    }
    else
        return (u - k) / (d - 1)*Bkd(k, d - 1, u) + (k + d - u) / (d - 1)*Bkd(k + 1, d - 1, u);
}
QPoint Curve::B_spline(double u)
{
    double x = 0;
    double y = 0;
    for (int k = 0;k < points.size();k++)
    {
        double temp = Bkd(k, 4, u);
        x += points[k].x()*temp;
        y += points[k].y()*temp;
    }
    QPainter pp(pix);    // 根据鼠标指针前后两个位置就行绘制直线
    QPen pen_temp(QColor(cf[0], cf[1], cf[2], cf[3]));
    pen_temp.setWidth(LineWidth);
    pp.setPen(pen_temp);

    pp.drawPoint(x+0.5,y+0.5);
    Add(x+0.5,y+0.5);
    return QPoint(x+0.5,y+0.5);
}
void Curve::scale_one(double X, double Y, float r,int&x,int&y)
{
    x = (double)x*r + X * (1 - r)+0.5;
    y = (double)y*r + Y * (1 - r)+0.5;
}
void Curve::scale(int X, int Y, float r)
{
    for (int i = 0;i < points.size();i++)
    {
    scale_one(X, Y, r, points[i].rx(), points[i].ry());
   }
}
void Curve::rotate_one(double X, double Y, double R, int&x, int&y)
{
    double cos_r = cos(R*pi_c);
    double sin_r = sin(R*pi_c);
    int x1 = x;
    int y1 = y;
    x = X + ((double)x1 - X)*cos_r - ((double)y1 - Y)*sin_r+0.5;
    y = Y + ((double)x1 - X)*sin_r + ((double)y1 - Y)*cos_r+0.5;
}
void Curve::rotate(int X, int Y, double R)
{
    for (int i = 0;i < points.size();i++)
    {
    rotate_one(X, Y, R, points[i].rx(), points[i].ry());
   }
}


