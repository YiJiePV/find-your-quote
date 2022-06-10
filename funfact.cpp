#include "funfact.h"
#include "ui_funfact.h"

FunFact::FunFact(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FunFact)
{
    ui->setupUi(this);
}

FunFact::~FunFact()
{
    delete ui;
}

QString FunFact::GetTitle() {
    return selTitle;
};

int FunFact::GetFunFactId() {
    return selFunFactId;
};

void FunFact::on_pushButton_clicked()
{
    int sRow = ui->fFunFactList->selectionModel()->currentIndex().row();

    selFunFactId = ui->fFunFactList->model()->data(ui->fFunFactList->model()->index(sRow,0)).toInt();
    selTitle = ui->fFunFactList->model()->data(ui->fFunFactList->model()->index(sRow,1)).toString();

    this->done(QDialog::Accepted);
}


void FunFact::on_pushButton_2_clicked()
{
    selTitle = "";
    selFunFactId = -1;

    this->done(QDialog::Rejected);
}

