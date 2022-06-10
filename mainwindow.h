#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDataWidgetMapper>
#include <QLineEdit>
#include <QModelIndex>
#include <QDebug>
#include "dblayer.h"
#include "author.h"
#include "funfact.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    DBLayer appDB;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_SaveQuote_clicked();

    void on_CancelQuote_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_CancelFunFact_clicked();

private:
    enum PAGES {HOME,QUOTE};
    Ui::MainWindow *ui;
    Author *alUI;
    FunFact *flUI;
    char insertOrUpdate = ' ';
    void ShowQuoteList();
    void ShowQuote(QString selIdx);
    void UpdateOneQuote();
    void InsertOneQuote();
    bool ValidateInput();
};
#endif // MAINWINDOW_H
