#ifndef DBLAYER_H
#define DBLAYER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

class DBLayer
{
public:
    DBLayer();
    bool DBConnect();
    bool DBStatus();
    QSqlQueryModel* GetResults(QString queryStr);
    QSqlQueryModel* GetQuoteList();
    QSqlQueryModel* GetQuote(QString quoteId);
    QSqlQueryModel* GetAllAuthors();
    QSqlQueryModel* GetAllFunFacts();
    bool UpdateQuote(QString quoteId, QString name, QString quote, int yearWritten, QString historicalContext, QString author, QString funfact);
    bool InsertQuote(QString name, QString quote, int yearWritten, QString historicalContext, QString author, QString funfact);

private:
    QSqlDatabase db;
    bool dbOK = false;
};

#endif // DBLAYER_H
