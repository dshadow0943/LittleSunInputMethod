#include "custompushbutton.h"
#include "customskin.h"
#include <QMouseEvent>
#include <QDebug>
#include <QString>


bool CustomPushButton::shift = false;
//初始的时候是英文小写
bool CustomPushButton::chinese = false;
bool CustomPushButton::abc123 = false;


int CustomPushButton::board = 1;
QList<CustomPushButton *> CustomPushButton::allBtns = QList<CustomPushButton*>();
QList<CustomPushButton *> CustomPushButton::allNumBtns = QList<CustomPushButton*>();
QList<CustomPushButton *> CustomPushButton::allHandBtns = QList<CustomPushButton*>();

CustomPushButton::CustomPushButton(const QString &text, int generalKey, QWidget *parent)
    : QLabel(text, parent),
      generalKey(generalKey),
      checkable(false),
      checked(false),
      pressed(false)
{
    allBtns.append(this);
}
CustomPushButton::CustomPushButton(const QString &text, int generalKey, int type, QWidget *parent)
    : QLabel(text, parent),
      generalKey(generalKey),
      checkable(false),
      checked(false),
      pressed(false)
{
    if(type == 0){
        allNumBtns.append(this);
    }else if(type == 2){
        allHandBtns.append(this);
    }
}

void CustomPushButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    KeyButtonStyle *style;
    if(pressed)
    {
        style = CUSTOMSKIN->getStyleByKey(generalKey, true);
    }else{
        style = CUSTOMSKIN->getStyleByKey(generalKey, false);
    }

    QString draw_text = text();
    QFont font = style->textFont;
    painter.setPen(style->borderPen);

    painter.setBrush(style->backgroundColor);
    painter.drawRoundedRect(rect().x() + 1,
                            rect().y() + 1,
                            rect().width() - 2,
                            rect().height() - 2,
                            4, 4);
    painter.setPen(style->textPen);

    //中英键盘选择按键，正在使用的键盘对应的字加粗，扩大
    if (generalKey == Qt::Key_Menu)
    {
        QRect left = rect();
        left.setWidth(left.width() / 2);
        QRect right = left;
        right.setX(left.x() + left.width());
        right.setWidth(left.width());

        QString left_text, right_text;
        if (chinese)
        {
            font.setPixelSize(font.pixelSize() - 4);
            left_text = CustomPushButton::EnText() + "/";
            right_text = CustomPushButton::ChText();
            font.setBold(false);
            font.setPixelSize(font.pixelSize() - 2);
            painter.setFont(font);
            painter.drawText(left, left_text, QTextOption(Qt::AlignRight|Qt::AlignVCenter));
            font.setBold(true);
            font.setPixelSize(font.pixelSize() + 2);
            painter.setFont(font);
            painter.drawText(right, right_text, QTextOption(Qt::AlignLeft|Qt::AlignVCenter));
        }
        else
        {
            font.setPixelSize(font.pixelSize() - 4);
            left_text = CustomPushButton::EnText();
            right_text = "/" + CustomPushButton::ChText();
            font.setBold(true);
            painter.setFont(font);
            painter.drawText(left, left_text, QTextOption(Qt::AlignRight|Qt::AlignVCenter));
            font.setBold(false);
            font.setPixelSize(font.pixelSize() - 2);
            painter.setFont(font);
            painter.drawText(right, right_text, QTextOption(Qt::AlignLeft|Qt::AlignVCenter));
        }
    }

    if(generalKey == Qt::Key_WWW){
        if(abc123){
            font.setPixelSize(font.pixelSize()+2);
            font.setBold(true);
            painter.setFont(font);
            painter.drawText(this->rect(), "A&8", QTextOption(Qt::AlignHCenter|Qt::AlignVCenter));
        }else{
            painter.setFont(font);
            painter.drawText(this->rect(), "A&8", QTextOption(Qt::AlignHCenter|Qt::AlignVCenter));
        }
    }

    //painter.drawText(rect(), text(), QTextOption(Qt::AlignCenter));

    font.setPixelSize(style->textFont.pixelSize());
    if (draw_text.size() > 1)
    {
        font.setPixelSize(font.pixelSize() - 4);
    }
    painter.setFont(font);
    if (!draw_text.isEmpty() && generalKey != Qt::Key_Menu && generalKey!= Qt::Key_WWW)
    {
        painter.drawText(rect(), text(), QTextOption(Qt::AlignCenter));
    }

}

QString CustomPushButton::EnText()
{
    return QString::fromUtf8("En");
}
QString CustomPushButton::ChText()
{
    return QString::fromUtf8("中");
}

void CustomPushButton::mousePressEvent(QMouseEvent *e)
{
    e->accept();
    pressed = true;
    update();
}

void CustomPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    e->accept();

    pressed = false;
    update();

    int key = generalKey;
    int unicode = key;
        if(!chinese)
        {
            switch(generalKey)
            {
            case Qt::Key_Shift:
                shift = !shift;
                break;
            case Qt::Key_Menu:
                update();
                chinese = !chinese;
                break;
            default:
                break;
            }
        }
        else {
            switch (generalKey) {
            case Qt::Key_Shift:
                break;
            case Qt::Key_Meta:
                break;
            case Qt::Key_Menu:
                update();
                chinese = !chinese;
                break;
            case Qt::Key_Backspace:
                unicode = 0x08;
                break;
            case Qt::Key_Enter:
                unicode = 0x0A;
                break;
            default:
                break;
            }
        }
        if(Qt::Key_A <= generalKey && generalKey <= Qt::Key_Z)
        {
            if(chinese || shift)
            {
                unicode = generalKey;
            }
            else {
                unicode = generalKey+32;
            }
        }

    switch(generalKey)
    {
    case Qt::Key_Meta:
    case Qt::Key_WWW:
    case Qt::Key_Word:
    case Qt::Key_Back:
    case Qt::Key_Backspace:
        emit clicked1();
        break;
    default:
        emit clicked1();
        break;
    }

    emit clicked(unicode ,key);
}
