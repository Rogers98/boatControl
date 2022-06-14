#ifndef SPEEDWIDGET2_H
#define SPEEDWIDGET2_H

#include <QWidget>
#include <QPropertyAnimation>

namespace Ui {
class SpeedWidget2;
}

class SpeedWidget2 : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(double value READ getValue WRITE setValue)
    Q_PROPERTY(int hShearValue READ getHShearValue WRITE setHShearValue)
    Q_PROPERTY(int vShearValue READ getVShearValue WRITE setVShearValue)
    Q_PROPERTY(double radiusInner READ getRadiusInner WRITE setRadiusInner)
    Q_PROPERTY(double radiusOuter READ getRadiusOuter WRITE setRadiusOuter)
    Q_PROPERTY(double radiusHalo READ getRadiusHalo WRITE setRadiusHalo)
    Q_PROPERTY(QColor colorOuterFrame READ getColorOuterFrame WRITE setColorOuterFrame)
    Q_PROPERTY(QColor colorInnerStart READ getColorInnerStart WRITE setColorInnerStart)
    Q_PROPERTY(QColor colorInnerEnd READ getColorInnerEnd WRITE setColorInnerEnd)
    Q_PROPERTY(QColor colorOuterStart READ getColorOuterStart WRITE setColorOuterStart)
    Q_PROPERTY(QColor colorOuterEnd READ getColorOuterEnd WRITE setColorOuterEnd)
    Q_PROPERTY(QColor colorHaloStart READ getColorHaloStart WRITE setColorHaloStart)
    Q_PROPERTY(QColor colorHaloEnd READ getColorHaloEnd WRITE setColorHaloEnd)

public:
    explicit SpeedWidget2(QWidget *parent = nullptr);
    ~SpeedWidget2();

private:
    Ui::SpeedWidget2 *ui;

protected:
    void paintEvent(QPaintEvent *);

private:
    void drawOuterGradient(QPainter *painter);
    void drawInnerGradient(QPainter *painter);
    void drawOuterHalo(QPainter *painter);
    void drawScale(QPainter *painter);
    void drawScaleNum(QPainter *painter);
    void drawPointer(QPainter *painter);
    void drawPointerSector(QPainter *painter);
    void drawValue(QPainter *painter);
    void drawUnit(QPainter *painter);

private:
    double value;                   //目标值
    int hShearValue, vShearValue;//H、V扭曲值
    double radiusInner;             //渐变内圈内半径
    double radiusOuter;             //渐变外圈内半径
    double radiusHalo;              //光晕内半径
    QColor colorOuterFrame;         //表盘外边框颜色
    QColor colorInnerStart;         //渐变内圈起始颜色
    QColor colorInnerEnd;           //渐变内圈结束颜色
    QColor colorOuterStart;         //渐变外圈起始颜色
    QColor colorOuterEnd;           //渐变外圈结束颜色
    QColor colorHaloStart;          //光晕起始颜色
    QColor colorHaloEnd;            //光晕结束颜色

    QPropertyAnimation *hShearAnimation, *vShearAnimation;

public:
    double getValue()               const;
    int    getHShearValue()         const;
    int    getVShearValue()         const;
    double getRadiusInner()         const;
    double getRadiusOuter()         const;
    double getRadiusHalo()          const;
    QColor getColorOuterFrame()     const;
    QColor getColorInnerStart()     const;
    QColor getColorInnerEnd()       const;
    QColor getColorOuterStart()     const;
    QColor getColorOuterEnd()       const;
    QColor getColorHaloStart()      const;
    QColor getColorHaloEnd()        const;

    void setValue(int value);
    void setValue(double value);
    void setHShearValue(int value);
    void setVShearValue(int value);

    //表盘外边框颜色
    void setColorOuterFrame(QColor color);

    //内层渐变区半径
    void setRadiusInner(int radius);
    void setRadiusInner(double radius);

    //外层渐变区半径
    void setRadiusOuter(int radius);
    void setRadiusOuter(double radius);

    //外层光晕区半径
    void setRadiusHalo(int radius);
    void setRadiusHalo(double radius);

    //内层渐变颜色
    void setColorInnerStart(QColor color);
    void setColorInnerEnd(QColor color);

    //外层渐变颜色
    void setColorOuterStart(QColor color);
    void setColorOuterEnd(QColor color);

    //光晕颜色
    void setColorHaloStart(QColor color);
    void setColorHaloEnd(QColor color);

    void startShearAnimal(int duration, int hShearValue, int vShearValue);

public slots:
    void updateValue(double value);
};

#endif // SPEEDWIDGET2_H
