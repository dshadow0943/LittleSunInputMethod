#include "customskin.h"

CustomSkin * CustomSkin::instance = nullptr;
CustomSkin::CustomSkin(QObject *parent) : QObject(parent)
{
    initWithNoSkipFile();
}

CustomSkin *CustomSkin::getInstance()
{
    if(instance == nullptr)
    {
        instance = new CustomSkin;
    }
    return instance;
}

CustomSkin::~CustomSkin()
{

}

void CustomSkin::initWithNoSkipFile()
{
    QFont font;
    font.setPixelSize(18);
    defaultButtonStyle1 = new KeyButtonStyle;
    defaultButtonStyle1->textFont        = font;
    defaultButtonStyle1->backgroundColor = QColor("#FeFeFe");
    defaultButtonStyle1->textPen         = QPen(QColor("#101010"));
    defaultButtonStyle1->borderPen       = QPen(QColor("#BBBBBB"));
    defaultButtonStyle1->borderFont      = font;
    defaultButtonStyle1->backImage       = QPixmap();

    defaultButtonStyle1_pressed = new KeyButtonStyle(defaultButtonStyle1);
    defaultButtonStyle1_pressed->pressed = 1;
    defaultButtonStyle1_pressed->backgroundColor = QColor(0xa8, 0xa8, 0xa8, 0xff);

    defaultButtonStyle2 = new KeyButtonStyle;
    defaultButtonStyle2->textFont        = font;
    defaultButtonStyle2->backgroundColor = QColor("#DDDDDD");
    defaultButtonStyle2->textPen         = QPen(QColor("#101010"));
    defaultButtonStyle2->borderPen       = QPen(QColor("#BBBBBB"));
    defaultButtonStyle2->borderFont      = font;
    defaultButtonStyle2->backImage       = QPixmap();

    defaultButtonStyle2_pressed = new KeyButtonStyle(defaultButtonStyle2);
    defaultButtonStyle2_pressed->pressed = 1;
    defaultButtonStyle2_pressed->backgroundColor = QColor(0xa8, 0xa8, 0xa8, 0xff);

    font.setPixelSize(20);
    candidateTextFont = font;
    candidateTextPen = QPen(QColor("black"));
    candidateTextPressBKColor = QColor(0xa8,0xa8,0xa8,0xff);

    borderPen = QPen(QColor(0x55, 0x55, 0x55, 0x50));
    trianglePressedBKColor = QColor(0xa8,0xa8,0xa8,0xff);
    QPen pen(QColor("black"));
    pen.setWidth(3);
    trianglePen = pen;

    bottomColor1 = QColor("#fdfefe");
    bottomColor2 = QColor("#EEEEEE");

    topColor = QColor("#fdfefe");

}

KeyButtonStyle *CustomSkin::getStyleByKey(int key, bool pressed)
{
    if(pressed)
    {
        return defaultButtonStyle1_pressed;
    }else{
        return defaultButtonStyle1;
    }
}
