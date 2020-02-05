#ifndef SET_CANVAS_H
#define SET_CANVAS_H

#include <QDialog>

namespace Ui {
class set_canvas;
}

class set_canvas : public QDialog
{
    Q_OBJECT

public:
    explicit set_canvas(QWidget *parent = 0);
    ~set_canvas();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::set_canvas *ui;
signals:
    void signal(int x,int y);
};

#endif // SET_CANVAS_H
