#ifndef CUSTONCHARVIEW_H
#define CUSTONCHARVIEW_H

#include <QWidget>

class ScrollBarBase : public QWidget
{
    Q_OBJECT
public:
    explicit ScrollBarBase(QWidget *parent = nullptr);

    int getUnitMinWidth() const;
    void setUnitMinWidth(int value);

    int getUnitMinHeight() const;
    void setUnitMinHeight(int value);

    void setData(QStringList& data);
    void clearData();

signals:
    void stringPressed(const QString &text, const QPoint &pos);
    void clicked(const QString &text, int index);


public slots:
    void onDataChange(QStringList data);

protected:
    bool event(QEvent *event);

private:
    int findcontansMouseRect(const QPoint &mousePos, QRect &rect);

protected:
    QList<QRect> dataRects;
    QStringList dataStrings;

    int unitMinWidth;
    int unitMinHeight;
    QRect pressRect;


    friend class EnKeyboard;
    friend class SoftKeyboard;
    friend class PuncKeyboard;

};

#endif // CUSTONCHARVIEW_H