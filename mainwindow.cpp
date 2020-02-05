#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QColorDialog>

#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QTime>
#include <QDir>
#include <QFile>

int MainWindow::ID_NUM=0;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Create_Toolbar();
    //drawWidget->setWidth(widthSpinBox->value());    //初始化画笔宽度
    //drawWidget->setColor(Qt::black);
    LineWidth=1;
    Color[0]=0;
    Color[1]=0;
    Color[2]=0;
    Color[3]=255;
    Length=550;
    Width=450;
    pix = QPixmap(Length, Width);
    polygon=NULL;
    pix.fill(Qt::white);

    p_pen = QPixmap(Length, Width);
    p_pen.fill(Qt::white);


    ui->pen->setChecked(true);
    lastPoint.setX(-1);
    endPoint.setX(-1);
    state=STATE_PEN;
    setMouseTracking(true);
    ui->centralWidget->setMouseTracking(true);
    pnt=new int*[Length];
    for(int i=0;i<Length;i++)
    {
        pnt[i]=new int[Width];
        for(int j=0;j<Width;j++)
        {
            pnt[i][j]=-1;
        }
    }
   ui->save->setIcon(QIcon(":/ICON/ICON/save.png"));
    ui->reset->setIcon(QIcon(":/ICON/ICON/reset.png"));
     ui->pen->setIcon(QIcon(":/ICON/ICON/pen.png"));
     ui->pushButton_9->setIcon(QIcon(":/ICON/ICON/choose.png"));
     ui->pushButton_2->setIcon(QIcon(":/ICON/ICON/line.png"));
     ui->pushButton_5->setIcon(QIcon(":/ICON/ICON/polygon.png"));
     ui->del->setIcon(QIcon(":/ICON/ICON/delete.png"));
     ui->ellipse->setIcon(QIcon(":/ICON/ICON/ellipse.png"));
     ui->curve->setIcon(QIcon(":/ICON/ICON/curve.png"));
     // 设置对话框icon
      setWindowIcon(QIcon(":/ICON/ICON/scale.png"));

         // 设置窗体标题
      setWindowTitle(tr("铁憨憨画图板"));


}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paint_all()
{
    for(int i=0;i<Length;i++)
    {
        for(int j=0;j<Width;j++)
        {
            pnt[i][j]=-1;
        }
    }

     //pix = QPixmap(Length, Width);
      //pix.fill(Qt::white);
    pix=p_pen;


      for(int i=0;i<M_line.size();i++)
      {
          if(M_line[i]!=NULL&&M_line[i]->alive==1)
          M_line[i]->draw();
      }

      for(int i=0;i<M_polygon.size();i++)
      {
          if(M_polygon[i]!=NULL&&M_polygon[i]->alive==1)
          {

             M_polygon[i]->draw();
          }
      }

      for(int i=0;i<M_curve.size();i++)
      {
          if(M_curve[i]!=NULL&&M_curve[i]->alive==1)
          {
             M_curve[i]->draw();
          }
      }
      for(int i=0;i<M_ellipse.size();i++)
      {
          if(M_ellipse[i]!=NULL&&M_ellipse[i]->alive==1)
          {
             M_ellipse[i]->draw();
          }
      }


   // update();
}
void MainWindow::Create_Toolbar()
{
                  //创建颜色选择控件
  QPixmap pixmap(20,20);
  pixmap.fill(Qt::black);

  ui->colorBtn->setIcon(QIcon(pixmap));
  //connect(colorBtn,SIGNAL(clicked()),this,SLOT(ShowColor()));


  QWidget*y=new QWidget();

  y->setFixedSize(30,1);
  QWidget*x=new QWidget();

  x->setFixedSize(200,1);

  QWidget*z=new QWidget();

  z->setFixedSize(120,1);


  ui->mainToolBar->addWidget(ui->widthLabel);
  ui->mainToolBar->addWidget(ui->widthSpinBox);
  ui->mainToolBar->addWidget(y);
  ui->mainToolBar->addWidget(ui->COlor);
  ui->mainToolBar->addWidget(ui->colorBtn);
  ui->mainToolBar->addWidget(z);
  ui->mainToolBar->addWidget(ui->al_t);
  ui->mainToolBar->addWidget(ui->al);
  ui->mainToolBar->addWidget(x);
  ui->mainToolBar->addWidget(ui->del);


}
void MainWindow::change(QPoint&a)
{
    a.rx()-=width_offset;
    a.ry()-=height_offset;
}
void MainWindow::change(int&x,int&y)
{
    x-=width_offset;
    y-=height_offset;
}
void MainWindow::setColor(int r,int g,int b,int a)
{
    Color[0]=r;
    Color[1]=g;
    Color[2]=b;
    Color[3]=a;
}
void MainWindow::draw_virtual(QVector<QPoint> a)
{

    int n=a.size();
    if(n==0)
        return;


    xmin=a[0].x();
    ymin=a[0].y();
    xmax=a[0].x();
    ymax=a[0].y();
    for(int i=0;i<n;i++)
    {
        //pp.drawPoint(a[i].rx(),a[i].ry());
        if(a[i].x()>xmax)
            xmax=a[i].x();
        if(a[i].x()<xmin)
            xmin=a[i].x();
        if(a[i].y()>ymax)
            ymax=a[i].y();
        if(a[i].y()<ymin)
            ymin=a[i].y();
    }

    xmin-=5;
    xmax+=5;
    ymin-=5;
    ymax+=5;
int xm=(xmin+xmax)/2;
    Line l1(xmin,ymin,xmax,ymin,&pix);
    Line l2(xmin,ymax,xmax,ymax,&pix);
    Line l3(xmin,ymin,xmin,ymax,&pix);
    Line l4(xmax,ymin,xmax,ymax,&pix);

     Ellipse(xmin,ymin,4,4,&pix,0);
     Ellipse(xmax,ymin,4,4,&pix,0);
     Ellipse(xmax,ymax,4,4,&pix,0);
     Ellipse(xmin,ymax,4,4,&pix,0);
     Ellipse(xmin,ymax,4,4,&pix,0);
     Ellipse(xm,ymin,4,4,&pix,0);
     Ellipse(xm,ymin-38,4,4,&pix,1);

    QPainter pp(&pix);    // 根据鼠标指针前后两个位置就行绘制直线
    QPen pen_temp(Qt::red);
    pen_temp.setWidth(4);
    pp.setPen(pen_temp);
    for(int i=0;i<n;i++)
    {
        pp.drawPoint(a[i].rx(),a[i].ry());
    }

     pen_temp.setColor(Qt::white);
     pp.setPen(pen_temp);

    pp.drawPoint(xmin,ymin);
    pp.drawPoint(xmax,ymin);
    pp.drawPoint(xmin,ymax);
    pp.drawPoint(xmax,ymax);



    pen_temp.setWidth(1);
    pen_temp.setColor(Qt::gray);
    pp.setPen(pen_temp);


   for(int i=0;i<35;i++)
   {
       pp.drawPoint(xm,ymin-i);
  }


    a.clear();

}
void MainWindow::draw_virtual_v(QVector<QPoint> a)
{

    int n=a.size();
    if(n==0)
        return;


    xmin=a[0].x();
    ymin=a[0].y();
    xmax=a[0].x();
    ymax=a[0].y();
    for(int i=0;i<n;i++)
    {
        //pp.drawPoint(a[i].rx(),a[i].ry());
        if(a[i].x()>xmax)
            xmax=a[i].x();
        if(a[i].x()<xmin)
            xmin=a[i].x();
        if(a[i].y()>ymax)
            ymax=a[i].y();
        if(a[i].y()<ymin)
            ymin=a[i].y();
    }


int xm=(xmin+xmax)/2;
    Line l1(xmin,ymin,xmax,ymin,&pix);
    Line l2(xmin,ymax,xmax,ymax,&pix);
    Line l3(xmin,ymin,xmin,ymax,&pix);
    Line l4(xmax,ymin,xmax,ymax,&pix);

     Ellipse(xmin,ymin,4,4,&pix,0);
     Ellipse(xmax,ymin,4,4,&pix,0);
     Ellipse(xmax,ymax,4,4,&pix,0);
     Ellipse(xmin,ymax,4,4,&pix,0);
     Ellipse(xmin,ymax,4,4,&pix,0);


    QPainter pp(&pix);    // 根据鼠标指针前后两个位置就行绘制直线
    QPen pen_temp(Qt::red);
    pen_temp.setWidth(4);
    pp.setPen(pen_temp);
    for(int i=0;i<n;i++)
    {
        pp.drawPoint(a[i].rx(),a[i].ry());
    }

     pen_temp.setColor(Qt::white);
     pp.setPen(pen_temp);

    pp.drawPoint(xmin,ymin);
    pp.drawPoint(xmax,ymin);
    pp.drawPoint(xmin,ymax);
    pp.drawPoint(xmax,ymax);

    a.clear();

}
bool MainWindow::Check(int x,int y,int x1,int y1)
{
if(abs(x-x1)<=4&&abs(y-y1)<=4)
{
    return true;
}
else
    return false;
}
int MainWindow::Check_all(int x,int y)
{
    int xm=(xmin+xmax)/2;

    if(Check(x,y,xm,ymin))
    {
        return 0;
    }
    else if(Check(x,y,xmin,ymin))
    {
        return 1;
    }
    else if(Check(x,y,xmin,ymax))
    {
        return 2;
    }
    else if(Check(x,y,xmax,ymin))
    {
        return 3;
    }
    else if(Check(x,y,xmax,ymax))
    {
        return 4;
    }
    else if(Check(x,y,(xmax+xmin)/2,ymin-38))
    {
        return 5;
    }
    return -1;
}
void MainWindow::paintEvent(QPaintEvent *)
{

    QPainter painter(this);

    switch (state) {
    case STATE_ELLI:
        if(ori!=0)
        {
            QPainter pp(&p_temp);    // 根据鼠标指针前后两个位置就行绘制直线
            QPen pen_temp(Qt::red);
            pen_temp.setWidth(4);
            pp.setPen(pen_temp);
            pp.drawPoint(e_x,e_y);
            pp.drawPoint(e_x+rx,e_y);
            pp.drawPoint(e_x-rx,e_y);
            pp.drawPoint(e_x,e_y+ry);
            pp.drawPoint(e_x,e_y-ry);

            painter.drawPixmap(width_offset, height_offset, p_temp);//加上偏移量，更新画布
        }
        else
        {
               painter.drawPixmap(width_offset, height_offset, pix);//加上偏移量，更新画布
        }
        break;
    case STATE_PEN:
       //首先获取鼠标事件，存入
      if(lastPoint.rx()!=-1&&endPoint.rx()!=-1)//如果不是第一个点
      {
          Line l(lastPoint.rx(),lastPoint.ry(),endPoint.rx(),endPoint.ry(),"DDA",Color,LineWidth,p_pen);//跟上一个点连起来
          Line l1(lastPoint.rx(),lastPoint.ry(),endPoint.rx(),endPoint.ry(),"DDA",Color,LineWidth,pix);//跟上一个点连起来
          //Gra.insert(ID_NUM,line_info);
      }
      lastPoint = endPoint;//更新上一个点
         painter.drawPixmap(width_offset, height_offset, pix);//加上偏移量，更新画布
        break;
      case STATE_CURVE:

        if(ori==2)
        {

            QPainter pp(&p_temp);    // 根据鼠标指针前后两个位置就行绘制直线
            QPen pen_temp(Qt::red);
            pen_temp.setWidth(4);
            pp.setPen(pen_temp);

            for(int i=0;i<curve->points.size();i++)
            {
                 pp.drawPoint(QPoint(curve->points[i].x(),curve->points[i].y()));
            }

              painter.drawPixmap(width_offset, height_offset, p_temp);
        }
        else if(ori==1)
        {


            QPainter pp(&p_temp);    // 根据鼠标指针前后两个位置就行绘制直线
            QPen pen_temp(Qt::red);
            pen_temp.setWidth(4);
            pp.setPen(pen_temp);

            for(int i=0;i<curve->points.size();i++)
            {
                 pp.drawPoint(QPoint(curve->points[i].x(),curve->points[i].y()));
            }
            painter.drawPixmap(width_offset, height_offset, p_temp);
        }
        else if(ori==3)
         {
            curve->draw(&pix);
            painter.drawPixmap(width_offset, height_offset, pix);//加上偏移量，更新画布
            ori=0;
            p_temp=pix;
            Curve*cu=new Curve(ID_NUM,al, Color,LineWidth,&p_temp,pnt,Length,Width);
            curve=cu;
            M_curve.insert(ID_NUM,cu);
            Gra.insert(ID_NUM,curve_info);
            ID_NUM++;
        }
        else
        {
             painter.drawPixmap(width_offset, height_offset, p_temp);
        }

        break;
    case STATE_POLY:
      if(ori==3)
      {
          polygon->draw(&pix);
          painter.drawPixmap(width_offset, height_offset, pix);//加上偏移量，更新画布
          p_temp=pix;
          Polygon*pony=new Polygon(ID_NUM,al, Color,LineWidth,&p_temp,pnt,Length,Width);
          polygon=pony;
          M_polygon.insert(ID_NUM,pony);
           Gra.insert(ID_NUM,polygon_info);
          ID_NUM++;
          ori=1;
      }
      else if(ori==2)
      {
          int n=polygon->points.size();
          Line l(polygon->points[n-1].x(), polygon->points[n-1].y(), endPoint.x(),endPoint.y(), "DDA", Color,LineWidth,p_temp);
          polygon->cf[0]=Color[0];
          polygon->cf[1]=Color[1];
          polygon->cf[2]=Color[2];
          polygon->cf[3]=Color[3];

          polygon->draw();
          QPainter pp(&p_temp);    // 根据鼠标指针前后两个位置就行绘制直线
          QPen pen_temp(Qt::red);
          pen_temp.setWidth(4);
          pp.setPen(pen_temp);
          for(int i=0;i<n;i++)
          {
               pp.drawPoint(QPoint(polygon->points[i].x(),polygon->points[i].y()));
          }
          painter.drawPixmap(width_offset, height_offset, p_temp);

      }
      else
      {
           painter.drawPixmap(width_offset, height_offset, p_temp);
      }
      p_temp=pix;

      break;
      case STATE_LINE:

        if(line_step==1&&one==0)
        {
            p_temp=pix;
            QPainter pp(&p_temp);    // 根据鼠标指针前后两个位置就行绘制直线
            QPen pen_temp(Qt::red);
            pen_temp.setWidth(4);
            pp.setPen(pen_temp);
            pp.drawPoint(QPoint(x1,y1));

            one=1;
             painter.drawPixmap(width_offset, height_offset, p_temp);//加上偏移量，更新画布
        }
        else if(line_step==1&&one==1)
        {
            p_temp=pix;
            Line l(x1, y1, endPoint.x(),endPoint.y(), al, Color,LineWidth,p_temp);

            QPainter pp(&p_temp);    // 根据鼠标指针前后两个位置就行绘制直线
            QPen pen_temp(Qt::red);
            pen_temp.setWidth(4);
            pp.setPen(pen_temp);
            pp.drawPoint(QPoint(x1,y1));


            painter.drawPixmap(width_offset, height_offset, p_temp);
        }
        else if(line_step==2)
        {
            Line*l1=new Line(ID_NUM,x1,y1,x2,y2,al,Color,LineWidth,&pix,pnt,Length,Width);
             M_line.insert(ID_NUM,l1);
             Gra.insert(ID_NUM,line_info);
             ID_NUM++;
             line_step=0;

             one=0;
             painter.drawPixmap(width_offset, height_offset, pix);//加上偏移量，更新画布

        }
        else
        {
             painter.drawPixmap(width_offset, height_offset, pix);//加上偏移量，更新画布
        }
        break;
    case STATE_PICK:
        points.clear();

        if(pick_state==0)//平移+放大
        {

            if(lastPoint.rx()!=-1&&endPoint.rx()!=-1&&pick_control==0)
            {
                setCursor(Qt::SizeAllCursor);
                if(pick_choice==line_info)
                {
                    l->translate(endPoint.x()-lastPoint.x(),endPoint.y()-lastPoint.y());
                    paint_all();

                    points.push_back(QPoint(l->x1,l->y1));
                    points.push_back(QPoint(l->x2,l->y2));
                }
                else if(pick_choice==polygon_info)
                {
                    p->translate(endPoint.x()-lastPoint.x(),endPoint.y()-lastPoint.y());
                    paint_all();

                    for(int i=0;i<p->points.size();i++)
                    {
                         points.push_back(QPoint(p->points[i].x(),p->points[i].y()));
                    }

                }
                else if(pick_choice==curve_info)
                {
                    curve->translate(endPoint.x()-lastPoint.x(),endPoint.y()-lastPoint.y());
                    paint_all();
                    for(int i=0;i<curve->points.size();i++)
                    {
                        points.push_back(QPoint(curve->points[i].x(),curve->points[i].y()));
                    }

                }
                else if(pick_choice==ellipse_info)
                {
                    elli->translate(endPoint.x()-lastPoint.x(),endPoint.y()-lastPoint.y());
                    paint_all();

                    e_x=elli->x;
                    e_y=elli->y;
                    rx=elli->rx;
                    ry=elli->ry;

                    points.push_back(QPoint(e_x+rx,e_y));
                    points.push_back(QPoint(e_x-rx,e_y));
                    points.push_back(QPoint(e_x,e_y+ry));
                    points.push_back(QPoint(e_x,e_y-ry));
                }
            }
            else if(lastPoint.rx()!=-1&&endPoint.rx()!=-1&&pick_control>=1&&pick_control<=4)
            {

                int hell=pick_control;
                int X,Y;
                int X_c,Y_c;
                if(hell==1)
                {
                    X=xmax;
                    Y=ymax;
                    X_c=xmin;
                    Y_c=ymin;
                    setCursor(Qt::SizeFDiagCursor);
                }
                else if(hell==2)
                {
                    X=xmax;
                    Y=ymin;
                    X_c=xmin;
                    Y_c=ymax;
                    setCursor(Qt::SizeBDiagCursor);
                }
                else if(hell==3)
                {
                    X=xmin;
                    Y=ymax;
                    X_c=xmax;
                    Y_c=ymin;
                    setCursor(Qt::SizeBDiagCursor);
                }
                else if(hell==4)
                {
                    X=xmin;
                    Y=ymin;
                    X_c=xmax;
                    Y_c=ymax;
                    setCursor(Qt::SizeFDiagCursor);
                }
                double r=1;
                if(endPoint.rx()!=-1)
                {
                    if((X_c-X)!=0)
                    r=(double)(endPoint.rx()-X)/(double)(X_c-X);
                    if((Y_c-Y)!=0)
                    {
                        double r1=(double)(endPoint.ry()-Y)/(double)(Y_c-Y);
                            if(r1>r)
                                r=r1;
                    }
                }
                if(pick_choice==line_info)
                {
                    if((abs(xmax-xmin)>20&&abs(ymax-ymin)>20)||abs(r)>1)
                    l->scale(X,Y,r);
                    paint_all();

                    points.push_back(QPoint(l->x1,l->y1));
                    points.push_back(QPoint(l->x2,l->y2));
                }
                else if(pick_choice==polygon_info)
                {
                    if((abs(xmax-xmin)>20&&abs(ymax-ymin)>20)||abs(r)>1)
                        p->scale(X,Y,r);
                    paint_all();

                    for(int i=0;i<p->points.size();i++)
                    {
                         points.push_back(QPoint(p->points[i].x(),p->points[i].y()));
                    }

                }
                else if(pick_choice==curve_info)
                {
                    if((abs(xmax-xmin)>20&&abs(ymax-ymin)>20)||abs(r)>1)
                        curve->scale(X,Y,r);
                    paint_all();
                    for(int i=0;i<curve->points.size();i++)
                    {
                        points.push_back(QPoint(curve->points[i].x(),curve->points[i].y()));
                    }

                }
                else if(pick_choice==ellipse_info)
                {
                    if((abs(xmax-xmin)>20&&abs(ymax-ymin)>20)||abs(r)>1)
                         elli->scale(X,Y,r);
                    paint_all();

                    e_x=elli->x;
                    e_y=elli->y;
                    rx=elli->rx;
                    ry=elli->ry;

                    points.push_back(QPoint(e_x+rx,e_y));
                    points.push_back(QPoint(e_x-rx,e_y));
                    points.push_back(QPoint(e_x,e_y+ry));
                    points.push_back(QPoint(e_x,e_y-ry));
                }

            }
            else if(lastPoint.rx()!=-1&&endPoint.rx()!=-1&&pick_control==5)
            {
                setCursor(Qt::PointingHandCursor);
                if(pick_choice==line_info)
                {
                    l->rotate((xmin+xmax)/2,(ymin+ymax)/2,endPoint.x()-lastPoint.x());
                    paint_all();

                    points.push_back(QPoint(l->x1,l->y1));
                    points.push_back(QPoint(l->x2,l->y2));
                }
                else if(pick_choice==polygon_info)
                {
                    p->rotate((xmin+xmax)/2,(ymin+ymax)/2,endPoint.x()-lastPoint.x());
                    paint_all();

                    for(int i=0;i<p->points.size();i++)
                    {
                         points.push_back(QPoint(p->points[i].x(),p->points[i].y()));
                    }

                }
                else if(pick_choice==curve_info)
                {
                    curve->rotate((xmin+xmax)/2,(ymin+ymax)/2,endPoint.x()-lastPoint.x());
                    paint_all();
                    for(int i=0;i<curve->points.size();i++)
                    {
                        points.push_back(QPoint(curve->points[i].x(),curve->points[i].y()));
                    }

                }
                else if(pick_choice==ellipse_info)
                {
                    elli->rotate();
                    pick_control=-1;
                    paint_all();
                    e_x=elli->x;
                    e_y=elli->y;
                    rx=elli->rx;
                    ry=elli->ry;

                    points.push_back(QPoint(e_x+rx,e_y));
                    points.push_back(QPoint(e_x-rx,e_y));
                    points.push_back(QPoint(e_x,e_y+ry));
                    points.push_back(QPoint(e_x,e_y-ry));
                }
            }
            else
            {
                setCursor(Qt::ArrowCursor);
                if(pick_choice==line_info)
                {

                    points.push_back(QPoint(l->x1,l->y1));
                    points.push_back(QPoint(l->x2,l->y2));
                }
                else if(pick_choice==polygon_info)
                {       
                    for(int i=0;i<p->points.size();i++)
                    {
                         points.push_back(QPoint(p->points[i].x(),p->points[i].y()));
                    }
                }
                else if(pick_choice==curve_info)
                {

                    for(int i=0;i<curve->points.size();i++)
                    {
                         points.push_back(QPoint(curve->points[i].x(),curve->points[i].y()));
                    }

                }
                else if(pick_choice==ellipse_info)
                {

                    e_x=elli->x;
                    e_y=elli->y;
                    rx=elli->rx;
                    ry=elli->ry;                   
                    points.push_back(QPoint(e_x+rx,e_y));
                    points.push_back(QPoint(e_x-rx,e_y));
                    points.push_back(QPoint(e_x,e_y+ry));
                    points.push_back(QPoint(e_x,e_y-ry));

                }
            }
            lastPoint = endPoint;
            draw_virtual(points);

        }
        else if(pick_state==1)
        {

            if(lastPoint.rx()!=-1&&endPoint.rx()!=-1&&pick_control>=1&&pick_control<=4)
            {
                int hell=pick_control;
                int X,Y;
                int X_c,Y_c;
                if(hell==1)
                {
                    X=xmax;
                    Y=ymax;
                    X_c=xmin;
                    Y_c=ymin;
                }
                else if(hell==2)
                {
                    X=xmax;
                    Y=ymin;
                    X_c=xmin;
                    Y_c=ymax;
                }
                else if(hell==3)
                {
                    X=xmin;
                    Y=ymax;
                    X_c=xmax;
                    Y_c=ymin;
                }
                else if(hell==4)
                {
                    X=xmin;
                    Y=ymin;
                    X_c=xmax;
                    Y_c=ymax;
                }

                if(pick_choice==line_info)
                {
                    setCursor(Qt::CrossCursor);
                    int x1,x2,y1,y2;
                    if(X>endPoint.rx())
                    {
                        x1=endPoint.rx();
                        x2=X;
                    }
                    else
                    {
                        x1=X;
                        x2=endPoint.rx();
                    }
                    if(Y>endPoint.ry())
                    {
                        y1=endPoint.ry();
                        y2=Y;
                    }
                    else
                    {
                        y1=Y;
                        y2=endPoint.ry();
                    }

                    l->clip(x1,y1,x2,y2,"Liang-Barsky");
                    paint_all();

                    points.push_back(QPoint(l->x1,l->y1));
                    points.push_back(QPoint(l->x2,l->y2));
                }
            }
            else
            {
                setCursor(Qt::ArrowCursor);
                paint_all();
                points.push_back(QPoint(l->x1,l->y1));
                points.push_back(QPoint(l->x2,l->y2));
            }
            draw_virtual_v(points);

        }
        painter.drawPixmap(width_offset, height_offset, pix);//加上偏移量，更新画布
        break;
    default:
          painter.drawPixmap(width_offset, height_offset, pix);//加上偏移量，更新画布
        break;
    }

}
void MainWindow::on_colorBtn_clicked()
{
    QColor myColor(Color[0], Color[1], Color[2], Color[3]);
    QColorDialog color(myColor,this);//调出颜色选择器对话框
    QColor co;
    color.exec();
     //获取当前选中的颜色
    co = color.currentColor();
    setColor(co.red(),co.green(),co.blue(),co.alpha());
    QPixmap pixmap(20,20);
    pixmap.fill(co);
    ui->colorBtn->setIcon(QIcon(pixmap));
}
void MainWindow::setLineWidth(int lw)
{
    LineWidth=lw;
}
int MainWindow::finid(int**pnt,int x,int y)
{
    int id=-1;
    if((x)>=0&&(x)<Length&&(y)>=0&&(y)<Width)
    id=pnt[x][y];
    if(id!=-1)
        return id;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if((x+i)>=0&&(x+i)<Length&&(y+j)>=0&&(y+j)<Width&&pnt[x+i][y+j]!=-1)
                return pnt[x+i][y+j];
            if((x-i)>=0&&(x-i)<Length&&(y-j)>=0&&(y-j)<Width&&pnt[x-i][y-j]!=-1)
                return pnt[x-i][y-j];
        }
    }

    return -1;
}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    switch (state) {
    case STATE_ELLI:
        if(event->button()==Qt::LeftButton)
        {
            ori=1;
            p_temp=pix;
            lastPoint = event->pos();
            change(lastPoint);
            rx=0;
            ry=0;
            e_x=lastPoint.x()-rx;
            e_y=lastPoint.y()-ry;
            Ellipse(-1,e_x,e_y,rx,ry,Color,LineWidth,&p_temp,pnt,Length,Width);
            update();
        }
        break;
    case STATE_PEN:
        if(event->button()==Qt::LeftButton) //鼠标左键按下
        {
            lastPoint = event->pos();
            change(lastPoint);
        }
        break;
      case STATE_PICK:

        if(event->button() ==Qt::LeftButton) //鼠标左键按下
         {
            lastPoint = event->pos();
            change(lastPoint);
            if(pick_control==-1)
            {
                pick_control=Check_all(lastPoint.rx(),lastPoint.ry());
                if(pick_control==5&&pick_choice==ellipse_info)
                {
                    endPoint.setX(0);
                }
            }
            update();
        }
        break;
    case STATE_LINE:
       if(event->button() ==Qt::LeftButton) //鼠标左键按下
        {
           lastPoint = event->pos();
           change(lastPoint);
           if(line_step==0)
           {
               x1=lastPoint.rx();
               y1=lastPoint.ry();
                line_step++;
           }
           else if(line_step==1)
           {
               x2=lastPoint.rx();
               y2=lastPoint.ry();
               line_step++;
           }
             update();

       }

       break;
     case STATE_POLY:
        if(event->button() ==Qt::LeftButton) //鼠标左键按下
         {

            if(ori==2)
            {
                lastPoint = event->pos();
                change(lastPoint);

                int temp=polygon->add_point(lastPoint.x(),lastPoint.y());
                if(temp==1)
                {
                   ori=3;
                }
                else
                {
                    ori=2;
                }
                update();

            }
            else if(ori==1)
            {

                 lastPoint = event->pos();
                change(lastPoint);

                int temp=polygon->add_point(lastPoint.x(),lastPoint.y());
                update();
                if(temp==0)
                {
                   ori=2;//画了一个点
                }


            }
        }
        break;

    case STATE_CURVE:
       if(event->button() ==Qt::LeftButton) //鼠标左键按下
        {
           if(ori==0)
           {
               lastPoint = event->pos();
               change(lastPoint);
               int temp=curve->add_point(lastPoint.x(),lastPoint.y());
               if(temp==1)
              {
                   p_temp=pix;
                   curve->draw();
                   ori=2;//实心
                   update();
                   ori=1;
               }
           }
           else if(ori!=3)
           {
               lastPoint = event->pos();
               change(lastPoint);

               int temp=curve->add_point(lastPoint.x(),lastPoint.y());
               if(temp==1)
              {

                   p_temp=pix;
                   curve->draw();
                   ori=2;//实心
                   update();
                   ori=1;//待画
               }
           }
           else
           {
                update();
           }

       }
       else if(event->button() ==Qt::RightButton)
       {
            ori=3;
            update();
       }
       break;
    default:
        break;
    }
     setFocus();


}
void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    switch (state)
    {
    case STATE_CURVE:
        ori=3;
        update();
        break;
    case STATE_PICK:

             lastPoint=event->pos();
              endPoint=event->pos();
              change(lastPoint);
              change(endPoint);

            if(lastPoint.x()>=0&&lastPoint.x()<Length&&lastPoint.y()>=0&&lastPoint.y()<Width)
            {
                int id= finid(pnt,lastPoint.x(),lastPoint.y());
                 if(id!=-1)
                {

                    int info=Gra.find(id).value();
                    pick_choice=info;
                    ui->al->clear();
                    switch(info)
                    {
                        case line_info:
                        l=M_line.find(id).value();
                        pick_state=0;//平移
                        if(l->algorithm=="DDA")
                         {
                            ui->al->addItem("DDA");
                            ui->al->addItem("Bresenham");
                        }
                        else
                        {
                            ui->al->addItem("Bresenham");
                            ui->al->addItem("DDA");
                        }
                        break;
                        case polygon_info:
                        p=M_polygon.find(id).value();
                        pick_state=0;
                        if(p->algorithm=="DDA")
                         {
                            ui->al->addItem("DDA");
                            ui->al->addItem("Bresenham");
                        }
                        else
                        {
                            ui->al->addItem("Bresenham");
                            ui->al->addItem("DDA");
                        }
                        break;
                        case curve_info:
                        curve=M_curve.find(id).value();
                        pick_state=0;
                        if(curve->algorithm=="Bezier")
                         {
                            ui->al->addItem("Bezier");
                            ui->al->addItem("B-spline");
                        }
                        else
                        {
                            ui->al->addItem("B-spline");
                            ui->al->addItem("Bezier");
                        }
                        break;
                        case ellipse_info:
                        elli=M_ellipse.find(id).value();
                        pick_state=0;
                        break;
                        }
                    lastPoint.setX(-1);
                    paint_all();
                    update();
                }
                else
                {
                    if(pick_state!=-1)
                    {
                        pick_state=-1;
                        pick_choice-1;
                        pick_control=-1;
                        paint_all();
                    }
                    ui->al->clear();
                }
            }


        break;
    default:break;
     }
}
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{


    switch (state) {
    case STATE_ELLI:
          if(event->buttons()&Qt::LeftButton) //鼠标左键按下的同时移动鼠标
        {
            ori=2;
            p_temp=pix;
            endPoint = event->pos();
            change(endPoint);
            rx=abs(endPoint.x()-lastPoint.x())/2;
            ry=abs(endPoint.y()-lastPoint.y())/2;
            e_x=(endPoint.x()+lastPoint.x())/2;
            e_y=(endPoint.y()+lastPoint.y())/2;
            Ellipse(-1,e_x,e_y,rx,ry,Color,LineWidth,&p_temp,pnt,Length,Width);
            update();
        }
        break;
    case STATE_PEN:

        if(event->buttons()&Qt::LeftButton) //鼠标左键按下的同时移动鼠标
       {

                 endPoint = event->pos();
                 change(endPoint);
                 update(); //进行绘制

        }
        break;
     case STATE_LINE:
        endPoint = event->pos();
        change(endPoint);
        update(); //进行绘制
        break;

    case STATE_POLY:
       endPoint = event->pos();
       change(endPoint);
       update(); //进行绘制
       break;
     case STATE_PICK:
        if(event->buttons()&Qt::LeftButton) //鼠标左键按下的同时移动鼠标
       {
            endPoint = event->pos();
                 change(endPoint);
                 update(); //进行绘制


        }break;
    default:
        break;
    }

}
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    switch (state) {
    case STATE_ELLI:
        if(event->button()&Qt::LeftButton)
        {
            endPoint = event->pos();
            change(endPoint);
            rx=abs(endPoint.x()-lastPoint.x())/2;
            ry=abs(endPoint.y()-lastPoint.y())/2;
            e_x=(endPoint.x()+lastPoint.x())/2;
            e_y=(endPoint.y()+lastPoint.y())/2;
            Ellipse*el=new Ellipse(ID_NUM,e_x,e_y,rx,ry,Color,LineWidth,&pix,pnt,Length,Width);
            el->draw(&pix);
            M_ellipse.insert(ID_NUM,el);
            Gra.insert(ID_NUM,ellipse_info);
            ID_NUM++;
            update();
            ori=0;

        }
        break;
    case STATE_PEN:
        if(event->button() == Qt::LeftButton) //鼠标左键释放
         {
                  endPoint = event->pos();
                  change(endPoint);
                  update();
                  lastPoint.setX(-1);
                  endPoint.setX(-1);
        }
        break;
    case STATE_PICK:
        if(event->button() == Qt::LeftButton) //鼠标左键释放
         {
                  endPoint = event->pos();
                  change(endPoint);

                  update();
                  lastPoint.setX(-1);
                  endPoint.setX(-1);
                  pick_control=-1;

        }
        break;
    default:
        break;
    }

}
int MainWindow::height_offset=80;
int MainWindow::width_offset=180;


void MainWindow::on_widthSpinBox_editingFinished()
{
      setLineWidth(ui->widthSpinBox->text().toInt());
}

void MainWindow::on_pushButton_5_clicked()
{
    state=STATE_POLY;
    ori=1;
    p_temp=pix;
    ui->al->clear();
    ui->al->addItem("DDA");
    ui->al->addItem("Bresenham");
    al="DDA";
    Polygon*pony=new Polygon(ID_NUM,al, Color,LineWidth,&p_temp,pnt,Length,Width);
    polygon=pony;
    M_polygon.insert(ID_NUM,pony);
     Gra.insert(ID_NUM,polygon_info);
    ID_NUM++;

}


void MainWindow::on_pushButton_2_clicked()
{
    state=STATE_LINE;
    ui->al->clear();
    ui->al->addItem("DDA");
    ui->al->addItem("Bresenham");
    al="DDA";
    line_step=0;
    one=0;

}


void MainWindow::on_pen_clicked()
{
    ui->al->clear();
    lastPoint.setX(-1);
    endPoint.setX(-1);
     state=STATE_PEN;
}

void MainWindow::on_pushButton_9_clicked()
{
    ui->al->clear();
    state=STATE_PICK;
    ori=0;
    pick_state=-1;
    pick_control=-1;
}




void MainWindow::on_save_clicked()
{
    ui->al->clear();

    QString filename = QFileDialog::getSaveFileName(NULL,QStringLiteral("保存画布"),"新建画布.bmp",QStringLiteral("Images (*.bmp)"));//获取需要保存成的文件名
      if(!filename.isEmpty())
       {
                  QString savePath=QString("%1").arg(filename);//保存为位图
                  pix.save(savePath);//调用save方法
                  QMessageBox::information(this,"信息","保存成功");

       }
}

void MainWindow::on_reset_clicked()
{
    ui->al->clear();
     set_canvas*draw_canvas=new set_canvas();
     connect(draw_canvas,SIGNAL(signal(int,int)),this,SLOT(idraw_canvas(int,int)));
     draw_canvas->show();
}
void MainWindow::idraw_canvas(int x,int y)
{
    pix = QPixmap(x, y);//根据x、y画出Qpixmap
    pix.fill(Qt::white);
    p_pen = QPixmap(x, y);//根据x、y画出Qpixmap
    p_pen.fill(Qt::white);
    Gra.clear();
    M_line.clear();
    M_polygon.clear();
    M_ellipse.clear();
    M_curve.clear();
}

void MainWindow::on_ellipse_clicked()
{
    ui->al->clear();
    state=STATE_ELLI;
    ori=0;
    p_temp=pix;
}

void MainWindow::on_curve_clicked()
{
    ui->al->clear();
    state=STATE_CURVE;
    ori=0;
    p_temp=pix;
    ui->al->clear();
    ui->al->addItem("Bezier");
    ui->al->addItem("B-spline");

    al="Bezier";
    Curve*cu=new Curve(ID_NUM,al, Color,LineWidth,&p_temp,pnt,Length,Width);
    curve=cu;
    M_curve.insert(ID_NUM,cu);
    Gra.insert(ID_NUM,curve_info);
    ID_NUM++;

}

void MainWindow::on_del_clicked()
{
    switch(pick_choice)
    {
        case line_info:
        l->alive=0;
        break;
        case polygon_info:
        p->alive=0;
        break;
        case curve_info:
       curve->alive=0;
        break;
        case ellipse_info:
        elli->alive=0;
        break;
        }
    ui->al->clear();
    pick_state=-1;
    pick_choice=-1;
    lastPoint.setX(-1);
    endPoint.setX(-1);
    pick_control=-1;
    ori=0;
    paint_all();
    update();
}

void MainWindow::on_cut_clicked()
{


}


void MainWindow::on_al_activated(const QString &arg1)
{
    al=arg1;
    if(state==STATE_PICK)
    {
        switch(pick_choice)
        {
            case line_info:
            l->algorithm=al;
            break;
            case polygon_info:
            p->algorithm=al;
            break;
            case curve_info:
           curve->algorithm=al;
            break;

            }
    }
    points.clear();
    paint_all();
    update();
}

void MainWindow::on_cut_clicked(bool checked)
{

}
