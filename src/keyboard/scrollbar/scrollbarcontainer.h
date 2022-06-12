#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <scrollbarbase.h>

class ScrollBarContainer : public QWidget
{
    Q_OBJECT
public:
    enum DIRECTION{Horizontal, Vertical};
    ScrollBarContainer(QWidget *parent = nullptr);
    void setWidget(QWidget *mCenterWidget, DIRECTION dire = Vertical, int mouseSensitivity = 1);
    int getMouseSensitivity() const;
    void setMouseSensitivity(int value);

signals:

public slots:

protected:
    void resizeEvent(QResizeEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);

private:
    int mMouseSensitivity; //鼠标灵敏度
    QWidget *mCenterWidget;
    DIRECTION mDirection;
};

#endif // CUSTOMWIDGET_H
