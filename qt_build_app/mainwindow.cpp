#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QSlider>
#include <QProgressBar>
#include <QListWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ---------------------------------------
    //  Layout structuur
    // ---------------------------------------
    auto *mainLayout = new QVBoxLayout();
    auto *row1 = new QHBoxLayout();
    auto *row2 = new QHBoxLayout();
    auto *row3 = new QHBoxLayout();

    // ---------------------------------------
    //  Widgets aanmaken
    // ---------------------------------------
    auto *title = new QLabel("⭐ Multi-OS Test Interface");
    title->setStyleSheet("font-size: 20px; font-weight: bold;");

    auto *osInfo = new QLabel();
#if defined(Q_OS_WIN)
    osInfo->setText("Running on: Windows");
#elif defined(Q_OS_MACOS)
    osInfo->setText("Running on: macOS");
#elif defined(Q_OS_LINUX)
    osInfo->setText("Running on: Linux");
#else
    osInfo->setText("Running on: Unknown OS");
#endif

    auto *btnMessage = new QPushButton("Test MessageBox");
    auto *btnAddItem = new QPushButton("Add Item");
    auto *textLog = new QTextEdit();
    textLog->setReadOnly(true);

    auto *slider = new QSlider(Qt::Horizontal);
    slider->setRange(0, 100);
    slider->setValue(50);

    auto *progress = new QProgressBar();
    progress->setRange(0, 100);
    progress->setValue(50);

    auto *list = new QListWidget();

    // ---------------------------------------
    //  Row layout vullen
    // ---------------------------------------
    row1->addWidget(btnMessage);
    row1->addWidget(btnAddItem);

    row2->addWidget(slider);
    row2->addWidget(progress);

    row3->addWidget(list);

    // ---------------------------------------
    //  Alles in main layout
    // ---------------------------------------
    mainLayout->addWidget(title);
    mainLayout->addWidget(osInfo);
    mainLayout->addSpacing(10);
    mainLayout->addLayout(row1);
    mainLayout->addSpacing(5);
    mainLayout->addLayout(row2);
    mainLayout->addSpacing(10);
    mainLayout->addWidget(new QLabel("Event Log:"));
    mainLayout->addWidget(textLog);
    mainLayout->addSpacing(10);
    mainLayout->addLayout(row3);

    // ---------------------------------------
    //  Layout toepassen op centralwidget
    // ---------------------------------------
    ui->centralwidget->setLayout(mainLayout);

    // ---------------------------------------
    //  Interactie
    // ---------------------------------------
    connect(btnMessage, &QPushButton::clicked, this, [=]() {
        QMessageBox::information(this, "MessageBox Test", "Dit werkt op dit OS!");
    });

    connect(btnAddItem, &QPushButton::clicked, this, [=]() {
        list->addItem("Nieuwe item");
        textLog->append("Item toegevoegd.");
    });

    connect(slider, &QSlider::valueChanged, this, [=](int v) {
        progress->setValue(v);
        textLog->append("Slider ↦ " + QString::number(v));
    });

    textLog->append("Qt versie: " + QString(qVersion()));
    textLog->append("UI succesvol geladen ✔");
}

MainWindow::~MainWindow()
{
    delete ui;
}
