#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QWidget>

class CustomWidget : public QWidget
{
    Q_OBJECT
public:
    enum DIRECTION{HORIZONTAL1, VERTICAL1};
    CustomWidget(QWidget *parent = nullptr);
    void init(QWidget *centerWidget, DIRECTION dire);
    int getMouseSensitivity() const;
    void setMouseSensitivity(int value);

signals:

public slots:

protected:
    void resizeEvent(QResizeEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);

private:
    int mouseSensitivity; //鼠标灵敏度
    QWidget *centerWidget;
    DIRECTION direction;

};

#endif // CUSTOMWIDGET_H
