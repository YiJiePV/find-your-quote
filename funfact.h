#ifndef FUNFACT_H
#define FUNFACT_H

#include <QDialog>

namespace Ui {
class FunFact;
}

class FunFact : public QDialog
{
    Q_OBJECT

public:
    explicit FunFact(QWidget *parent = nullptr);
    ~FunFact();
    int GetFunFactId();
    QString GetTitle();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::FunFact *ui;
    int selFunFactId = -1;
    QString selTitle;
};

#endif // FUNFACT_H
