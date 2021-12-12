#ifndef CUSTOMSKIN_H
#define CUSTOMSKIN_H

#include <QObject>
#include <QList>
#include <QColor>
#include <QPixmap>
#include <QFont>
#include <QPen>
#include <QDomElement>

struct KeyButtonStyle{
    KeyButtonStyle()
        :key(0), pressed(0)
    {}
    KeyButtonStyle(const KeyButtonStyle *o)
    {
        this->key = o->key;
        this->pressed = o->pressed;
        this->textFont = o->textFont;
        this->backgroundColor = o->backgroundColor;
        this->textPen = o->textPen;
        this->borderPen = o->borderPen;
        this->borderFont = o->borderFont;
        this->backImage = o->backImage;
    }
    int key;                //按钮键值
    int pressed;            //是否按下
    QFont textFont;         //文字字体
    QColor backgroundColor; //背景颜色
    QPen textPen;           //文字笔画
    QPen borderPen;         //边框画笔
    QFont borderFont;       //边框字体
    QPixmap backImage;      //背景图片
};

class CustomSkin : public QObject
{
    Q_OBJECT
public:

    static CustomSkin *getInstance();
    ~CustomSkin();
    void initWithNoSkipFile();
    KeyButtonStyle *getStyleByKey(int key, bool pressed);

public:
    KeyButtonStyle      *defaultButtonStyle1;           //默认按钮1风格
    KeyButtonStyle      *defaultButtonStyle1_pressed;   //默认按钮1按下时风格
    KeyButtonStyle      *defaultButtonStyle2;           //默认按钮2风格
    KeyButtonStyle      *defaultButtonStyle2_pressed;   //默认按钮2按下时风格

    QFont               candidateTextFont;          //候选词的字体
    QPen                candidateTextPen;           //候选词的画笔
    QColor              candidateTextPressBKColor;  //候选词按下时的颜色

    QPen                borderPen;                  //边框画笔
    QPixmap             topBKPixmap;                //候选词背景图片
    QColor              topColor;                   //候选词背景色

    QColor              trianglePressedBKColor;     //下拉框按下时的颜色
    QPen                trianglePen;                //下拉框图标画笔

    QColor              bottomColor1;           // 底部显示按钮时的颜色
    QColor              bottomColor2;           // 底部显示滚动窗口时候的颜色

private:
    explicit CustomSkin(QObject *parent = nullptr);
    static CustomSkin *instance;

};
#define CUSTOMSKIN CustomSkin::getInstance()

#endif // CUSTOMSKIN_H
