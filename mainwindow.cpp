#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

#include "dblayer.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Setup the database
    if (appDB.DBConnect()) {
        qDebug() << "Connection worked!";
    } else {
        qDebug() << "Error: connection failed!";
    };

    ui->setupUi(this);

    ShowQuoteList();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete alUI;
    delete flUI;
}

void MainWindow::on_pushButton_clicked()
{
    ShowQuote(nullptr);
}

void MainWindow::on_SaveQuote_clicked()
{
    if (insertOrUpdate == 'U') {
        UpdateOneQuote();
    } else if (insertOrUpdate == 'I') {
        InsertOneQuote();
    };
    ShowQuoteList();
}

void MainWindow::on_CancelQuote_clicked()
{
    ShowQuoteList();
}

void MainWindow::on_CancelFunFact_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    QString selectedQuoteId;
    selectedQuoteId = index.siblingAtColumn(0).data().value<QString>();
    ShowQuote(selectedQuoteId);
}

void MainWindow::on_pushButton_5_clicked()
{
    alUI = new Author(this);
    QTableView *fAuthorList = alUI->findChild<QTableView* >("fAuthorList");
    QLineEdit *fAuthorName = ui->page_2->findChild<QLineEdit* >("fQuoteAuthor");

    fAuthorList->setSelectionBehavior(QAbstractItemView::SelectRows);
    fAuthorList->setAlternatingRowColors(true);
    fAuthorList->setSelectionMode(QAbstractItemView::SingleSelection);

    QSqlQueryModel *mp = appDB.GetAllAuthors();
    fAuthorList->setModel(mp);
    fAuthorList->setColumnHidden(0,true);

    alUI->setModal(true);
    if (alUI->exec() == QDialog::Accepted)
    {
        QString aName = alUI->GetAuthorName();
        fAuthorName->setText(aName);
    };
}

void MainWindow::on_pushButton_6_clicked()
{
    flUI = new FunFact(this);
    QTableView *fFunFactList = flUI->findChild<QTableView* >("fFunFactList");
    QLineEdit *fFunFact = ui->page_2->findChild<QLineEdit* >("fQuoteFunFact");

    fFunFactList->setSelectionBehavior(QAbstractItemView::SelectRows);
    fFunFactList->setAlternatingRowColors(true);
    fFunFactList->setSelectionMode(QAbstractItemView::SingleSelection);

    QSqlQueryModel *mp = appDB.GetAllFunFacts();
    fFunFactList->setModel(mp);
    fFunFactList->setColumnHidden(0,true);

    flUI->setModal(true);
    if (flUI->exec() == QDialog::Accepted)
    {
        QString fName = flUI->GetTitle();
        fFunFact->setText(fName);
    };
}

void MainWindow::ShowQuoteList() {
    ui->stackedWidget->setCurrentIndex(0);

    // Populate the grid
    QSqlQueryModel *m1 = appDB.GetQuoteList();
    ui->tableView->setModel(m1);
    ui->tableView->setColumnHidden(0,true);   // Hide the Task ID
}


void MainWindow::ShowQuote(QString selIdx = nullptr) {
    QLineEdit *fQuoteId = ui->page_2->findChild<QLineEdit* >("fQuoteId");
    QLineEdit *fQuoteName = ui->page_2->findChild<QLineEdit* >("fQuoteName");
    QTextEdit *fQuoteQuote = ui->page_2->findChild<QTextEdit* >("fQuoteQuote");
    QLineEdit *fQuoteYear = ui->page_2->findChild<QLineEdit* >("fQuoteYear");
    QTextEdit *fQuoteHistory = ui->page_2->findChild<QTextEdit* >("fQuoteHistory");
    QLineEdit *fQuoteAuthor = ui->page_2->findChild<QLineEdit* >("fQuoteAuthor");
    QLineEdit *fQuoteFunFact = ui->page_2->findChild<QLineEdit* >("fQuoteFunFact");

    PAGES pg=QUOTE;
    ui->stackedWidget->setCurrentIndex(pg);
    ui->fQuoteId->setVisible(false);

    QDataWidgetMapper *mapper = new QDataWidgetMapper(ui->page_2);

    if (selIdx == nullptr) {
        insertOrUpdate = 'I';
        QModelIndex index = ui->tableView->selectionModel()->currentIndex();
        QAbstractItemModel *m2 = ui->tableView->model();
        ui->tableView->setModel(m2);
        m2->insertColumns(0, 6, index);
        m2->insertRows(0, 1, index);
        mapper->setModel(m2);
    } else {
        insertOrUpdate = 'U';
        QSqlQueryModel *m2 = appDB.GetQuote(selIdx);
        ui->tableView->setModel(m2);
        mapper->setModel(m2);
    };

    mapper->addMapping(fQuoteId,0);
    mapper->addMapping(fQuoteName, 1);
    mapper->addMapping(fQuoteQuote, 2);
    mapper->addMapping(fQuoteYear, 3);
    mapper->addMapping(fQuoteHistory, 4);
    mapper->addMapping(fQuoteAuthor, 5);
    mapper->addMapping(fQuoteFunFact, 6);
    mapper->toFirst();

}

void MainWindow::UpdateOneQuote() {
    QString qId = ui->fQuoteId->text();
    QString qName = ui->fQuoteName->text();
    QString qQuote = ui->fQuoteQuote->toPlainText();
    int qYear = ui->fQuoteYear->text().toInt();
    QString qHistory = ui->fQuoteHistory->toPlainText();
    QString aAuthor = ui->fQuoteAuthor->text();
    QString fFunFact = ui->fQuoteFunFact->text();

    if (!ValidateInput()) {
        bool a = appDB.UpdateQuote(qId, qName, qQuote, qYear, qHistory, aAuthor, fFunFact);
        if(!a){
            QString errMsg = "Update failed\n";
            QMessageBox::information(this,"Validation Error", errMsg);
        }
    }
}

void MainWindow::InsertOneQuote() {
    QString qName = ui->fQuoteName->text();
    QString qQuote = ui->fQuoteQuote->toPlainText();
    int qYear = ui->fQuoteYear->text().toInt();
    QString qHistory = ui->fQuoteHistory->toPlainText();
    QString aAuthor = ui->fQuoteAuthor->text();
    QString fFunFact = ui->fQuoteFunFact->text();

    if (!ValidateInput()) {
        appDB.InsertQuote(qName, qQuote, qYear, qHistory, aAuthor, fFunFact);
    }
}

bool MainWindow::ValidateInput() {
    bool foundErr = false;
    QString errMsg = "";

    if (ui->fQuoteName->text().length() == 0) {
        errMsg += "Quote Name can not be blank\n";
        foundErr = true;
    };

    if (ui->fQuoteAuthor->text().length() == 0) {
        errMsg += "Author can not be blank\n";
        foundErr = true;
    };

    if (foundErr) {
        QMessageBox::information(this,"Validation Error", errMsg);
    }

    return foundErr;
}


























