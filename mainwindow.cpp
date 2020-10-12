#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLayout>
#include "widgets/bigsurwidget.h"
#include <random>
#include <functional>
#include <time.h>
#include "waitingspinner/waitingspinnerwidget.h"
#include "circleiconbutton/circleiconbutton.h"
int get_random()
{
    std::uniform_int_distribution<int> random_range(0, 255);
    std::default_random_engine re(time(0));
    return random_range(re);
}
#include "iconfont/iconfonthelper.h"
#include "animatedcheckbox/animatedcheckbox.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QHBoxLayout* layout = new QHBoxLayout;
    BigSurWidget* b1 = new BigSurWidget;

    QWidget* bb1 = new QWidget;
    bb1->setStyleSheet("background-color:gray;");
    QHBoxLayout* hLayout = new QHBoxLayout;
    CircleIconButton* bt1 = new CircleIconButton("alicorn", 10);
    CircleIconButton* bt2 = new CircleIconButton("wifi", 10);
    CircleIconButton* bt3 = new CircleIconButton("location-arrow", 10);
    AnimatedCheckBox* cb1 = new AnimatedCheckBox();

    WaitingSpinnerWidget* spinner = new WaitingSpinnerWidget;
    spinner->setRoundness(70.0);
    spinner->setMinimumTrailOpacity(15.0);
    spinner->setTrailFadePercentage(70.0);
    spinner->setNumberOfLines(12);
    spinner->setLineLength(10);
    spinner->setLineWidth(5);
    spinner->setInnerRadius(10);
    spinner->setRevolutionsPerSecond(1);
    spinner->setColor(QColor(Qt::yellow));
    spinner->start();

    hLayout->addWidget(bt1);
    hLayout->addWidget(bt2);
    hLayout->addWidget(bt3);
    hLayout->addWidget(cb1);
    b1->setLayout(hLayout);
    layout->addWidget(b1);
    layout->addWidget(bb1);
    layout->addWidget(spinner);
    BigSurWidget* b2 = new BigSurWidget;
    layout->addWidget(b2);
    centralWidget()->setLayout(layout);
    QSlider* slider = new QSlider;
    slider->setRange(0, 255);
    slider->setValue(255);
    connect(slider, &QSlider::valueChanged, [=](){
        b1->setOpacity((double)slider->value() / 255.0);
        b2->setOpacity((double)slider->value() / 255.0);
    });
    layout->addWidget(slider);

    QSlider* slider2 = new QSlider;
    slider2->setRange(0, 255);
    slider2->setValue(255);

    connect(slider2, &QSlider::valueChanged, [=]() {

        b1->setBackgroundColor(QColor(slider2->value(),slider2->value(),slider2->value()));
        b2->setBackgroundColor(QColor(slider2->value() / 5, slider2->value() / 2,slider2->value()));
    });
    layout->addWidget(slider2);
}

MainWindow::~MainWindow()
{
    delete ui;
}


