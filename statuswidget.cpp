#include "statuswidget.h"
#include "ui_statuswidget.h"
#include "QPainter"

StatusWidget::StatusWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatusWidget)
{
    ui->setupUi(this);


    ui->label->setStyleSheet("color:white");
    ui->label_3->setStyleSheet("color:white");
    ui->label_4->setStyleSheet("color:white");
    ui->label_6->setStyleSheet("color:white");
    ui->label_7->setStyleSheet("color:white");
    ui->label_8->setStyleSheet("color:white");
    ui->label_9->setStyleSheet("color:white");

    ui->label_10->setStyleSheet("color:white");
    ui->label_11->setStyleSheet("color:white");
    ui->label_12->setStyleSheet("color:white");
    ui->label_13->setStyleSheet("color:white");
    ui->label_14->setStyleSheet("color:white");
    ui->label_15->setStyleSheet("color:white");
    ui->label_16->setStyleSheet("color:white");

    ui->label_17->setStyleSheet("color:white");
    ui->label_18->setStyleSheet("color:white");
    ui->label_19->setStyleSheet("color:white");
    ui->label_20->setStyleSheet("color:white");
    ui->label_21->setStyleSheet("color:white");
    ui->label_22->setStyleSheet("color:white");
    ui->label_23->setStyleSheet("color:white");

    ui->label_24->setStyleSheet("color:white");
    ui->label_25->setStyleSheet("color:white");
    ui->label_26->setStyleSheet("color:white");
    ui->label_27->setStyleSheet("color:white");
    ui->label_28->setStyleSheet("color:white");
    ui->label_29->setStyleSheet("color:white");
    ui->label_30->setStyleSheet("color:white");

    ui->label_31->setStyleSheet("color:white");
    ui->label_32->setStyleSheet("color:white");
    ui->label_33->setStyleSheet("color:white");
    ui->label_34->setStyleSheet("color:white");
    ui->label_35->setStyleSheet("color:white");
    ui->label_36->setStyleSheet("color:white");
    ui->label_37->setStyleSheet("color:white");

    ui->label_38->setStyleSheet("color:white");
    ui->label_39->setStyleSheet("color:white");
    ui->label_40->setStyleSheet("color:white");
    ui->label_41->setStyleSheet("color:white");
    ui->label_42->setStyleSheet("color:white");
    ui->label_43->setStyleSheet("color:white");
    ui->label_44->setStyleSheet("color:white");


}

StatusWidget::~StatusWidget()
{
    delete ui;
}

void StatusWidget::paintEvent(QPaintEvent *event)
{
    QPainter state_painter(this);

/*******************中心深蓝色区域***************/
    const QPoint widget_point[6]=
    {

        QPoint(0,0),

        QPoint(60,0),

        QPoint(89,35),

        QPoint(this->width(),35),

        QPoint(this->width(),this->height()),

        QPoint(0,this->height()),

    };

    state_painter.setBrush(QColor(0,16,48));

    state_painter.drawPolygon(widget_point,6);

/*******************中心深蓝色区域***************/


/*******************左水平渐变线******************/
    state_painter.setRenderHint(QPainter::Antialiasing,true);
    QLinearGradient Linear(0,0,15,0);        //水平渐变
    Linear.setColorAt(0,QColor(10,124,152,255) );
    Linear.setColorAt(0.2,QColor(10,124,152,155) );
    Linear.setColorAt(1,QColor(10,124,152,5));

    state_painter.setBrush(Linear);
    state_painter.setPen(Qt::transparent);

    state_painter.drawRect(0,0,20,this->height());

/*******************左水平渐变线******************/

    state_painter.save();

/*******************上竖直渐变线******************/

    QLinearGradient Linear2(0,0,0,7);        //竖直渐变
    Linear2.setColorAt(0,QColor(10,124,152,255));
    Linear2.setColorAt(0.2,QColor(10,124,152,155));
    Linear2.setColorAt(1,QColor(10,124,152,5));

    state_painter.setBrush(Linear2);
    state_painter.setPen(Qt::transparent);

    //画线区
    const QPoint bother_pointa[4]=
    {
        QPoint(0,0),

        QPoint(60,0),

        QPoint(47,13),

        QPoint(0,13),

    };

    state_painter.drawPolygon(bother_pointa,4);

    state_painter.save();//画完此线之后恢复
    state_painter.translate(88.2842,28.28427);

    const QPoint bother_point[4]=
    {
        QPoint(0,0),

        QPoint(this->width(),0),

        QPoint(this->width(),7),

        QPoint(-7,7),

    };

    state_painter.drawPolygon(bother_point,4);

    //恢复
    state_painter.restore();


/***
    state_painter.drawRect(0,0,80,15);
***/
    state_painter.translate(60,0);
    state_painter.rotate(45);
    state_painter.drawRect(0,0,40,15);


/*******************上竖直渐变线******************/

     state_painter.restore();

/*******************右竖直渐变线******************/

     state_painter.setRenderHint(QPainter::Antialiasing,true);
     QLinearGradient Linear3(  this->width(), 0  ,   ( this->width()-15 )  , 0 );        //水平渐变
     Linear3.setColorAt(0,QColor(10,124,152,255));
     Linear3.setColorAt(0.2,QColor(10,124,152,155));
     Linear3.setColorAt(1,QColor(10,124,152,5));

     state_painter.setBrush(Linear3);
     state_painter.setPen(Qt::transparent);


     //画线区

     state_painter.drawRect( this->width() , 30      ,      -15,  this->height() );

/*******************右竖直渐变线******************/



/*******************下竖直渐变线******************/

    state_painter.setRenderHint(QPainter::Antialiasing,true);
    QLinearGradient Linear4( 0,(this->height()),    0,(this->height()-15) );        //水平渐变
    Linear4.setColorAt(0,QColor(10,124,152,255));
    Linear4.setColorAt(0.2,QColor(10,124,152,155));
    Linear4.setColorAt(1,QColor(10,124,152,5));

    state_painter.setBrush(Linear4);
    state_painter.setPen(Qt::transparent);

    state_painter.drawRect(0,(this->height()-15),this->width(),(this->height()));

/*******************下竖直渐变线******************/





}
