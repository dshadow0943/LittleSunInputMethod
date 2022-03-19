/*
*
* Author:     leilong <dshadow@foxmail.com>
*
*/
#ifndef ICONBUTTON_H
#define ICONBUTTON_H

#include <QObject>
#include <QLabel>

class IconButton : public QLabel
{
    Q_OBJECT
public:
    explicit IconButton(QString path, QWidget *parent = nullptr);

    void setIconPath(QString path);

    enum IconType {
        Other,
        Svg,
    };

signals:

public slots:

protected:
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    QPixmap loadPixmap();

private:
    QString mIconPath;
    QPixmap *mPixmap;
    IconType mType;
};

#endif // ICONBUTTON_H
