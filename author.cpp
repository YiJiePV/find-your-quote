#include "author.h"
#include "ui_author.h"

Author::Author(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Author)
{
    ui->setupUi(this);
}

Author::~Author()
{
    delete ui;
}

QString Author::GetAuthorName() {
    return selAuthorName;
};

int Author::GetAuthorId() {
    return selAuthorId;
};

QString Author::GetBirthDate(){
    return selBirthDate;
};

QString Author::GetDeathDate(){
    return selDeathDate;
};

void Author::on_pushButton_clicked()
{
    int sRow = ui->fAuthorList->selectionModel()->currentIndex().row();

    selAuthorId = ui->fAuthorList->model()->data(ui->fAuthorList->model()->index(sRow,0)).toInt();
    selAuthorName = ui->fAuthorList->model()->data(ui->fAuthorList->model()->index(sRow,1)).toString();
    selBirthDate = ui->fAuthorList->model()->data(ui->fAuthorList->model()->index(sRow,2)).toString();
    selDeathDate = ui->fAuthorList->model()->data(ui->fAuthorList->model()->index(sRow,3)).toString();

    this->done(QDialog::Accepted);
}


void Author::on_pushButton_2_clicked()
{
    selAuthorName = "";
    selAuthorId = -1;
    selBirthDate = "";
    selDeathDate = "";

    this->done(QDialog::Rejected);
}

