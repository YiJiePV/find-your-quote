#ifndef AUTHOR_H
#define AUTHOR_H

#include <QDialog>

namespace Ui {
class Author;
}

class Author : public QDialog
{
    Q_OBJECT

public:
    explicit Author(QWidget *parent = nullptr);
    ~Author();
    int GetAuthorId();
    QString GetAuthorName();
    QString GetBirthDate();
    QString GetDeathDate();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Author *ui;
    int selAuthorId = -1;
    QString selAuthorName;
    QString selBirthDate;
    QString selDeathDate;
};

#endif // AUTHOR_H
