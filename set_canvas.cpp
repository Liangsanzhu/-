#include "set_canvas.h"
#include "ui_set_canvas.h"

set_canvas::set_canvas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::set_canvas)
{
    setWindowIcon(QIcon(":/ICON/ICON/color.png"));

       // 设置窗体标题
    setWindowTitle(tr("新建画布"));
    ui->setupUi(this);

}

set_canvas::~set_canvas()
{
    delete ui;
}

void set_canvas::on_buttonBox_accepted()
{
    QString X=ui->TE_X->toPlainText();
       QString Y=ui->TE_Y->toPlainText();
       int*var=new int[2];
       var[0]=X.toInt();
       var[1]=Y.toInt();
       emit signal(var[0],var[1]);
}
