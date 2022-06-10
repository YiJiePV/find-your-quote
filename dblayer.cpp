#include "dblayer.h"

DBLayer::DBLayer()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    QString db_path = "C:/Users/karen/Quote/quote.db";
    db.setDatabaseName(db_path);
}

bool DBLayer::DBConnect() {
    if (!db.isValid()) {
        dbOK = false;
    } else {
        try {
            if (db.open()) {
                dbOK = true;
            } else {
                dbOK = false;
            };
        }  catch (...) {
            dbOK = false;
        }
    }
    return dbOK;
};

bool DBLayer::DBStatus() {
    return dbOK;
};

QSqlQueryModel* DBLayer::GetQuoteList() {
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery *qry = new QSqlQuery(db);

    QString queryStr = "";
    queryStr += "SELECT q.QuoteID,q.Name,q.Quote,q.YearWritten,q.HistoricalContext,a.Name,f.Title";
    queryStr += " FROM Quotebox q";
    queryStr += " LEFT JOIN Author a ON q.AuthorID = a.AuthorID";
    queryStr += " LEFT JOIN Funfact f ON q.FunFactID = f.FunFactID";
    qry->prepare(queryStr);

    if (!qry->exec()) {
        QMessageBox::critical(nullptr,"error::",qry->lastError().text());
    }
    model->setQuery(*qry);

    delete qry;

    return model;
};

QSqlQueryModel* DBLayer::GetAllAuthors() {
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery *qry = new QSqlQuery(db);

    QString queryStr = "";
    //SELECT a.AuthorID,a.Name,a.BirthDate,a.DeathDate FROM Author a
    queryStr += "SELECT a.AuthorID,a.Name,a.BirthDate,a.DeathDate";
    queryStr += " FROM Author a";

    qry->prepare(queryStr);
    qry->exec();
    model->setQuery(*qry);

    delete qry;

    return model;
};

QSqlQueryModel* DBLayer::GetAllFunFacts() {
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery *qry = new QSqlQuery(db);

    QString queryStr = "";
    queryStr += "SELECT f.FunFactID,f.Title";
    queryStr += " FROM FunFact f";

    qry->prepare(queryStr);
    qry->exec();
    model->setQuery(*qry);

    delete qry;

    return model;
};

QSqlQueryModel* DBLayer::GetQuote(QString quoteId) {
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery *qry = new QSqlQuery(db);

    QString queryStr = "";
    queryStr += "SELECT q.QuoteID,q.Name,q.Quote,q.YearWritten,q.HistoricalContext,a.Name,f.Title";
    queryStr += " FROM Quotebox q";
    queryStr += " LEFT JOIN Author a ON q.AuthorID = a.AuthorID";
    queryStr += " LEFT JOIN FunFact f ON q.FunFactID = f.FunFactID";
    queryStr += " WHERE q.QuoteID=";
    queryStr += quoteId;

    qry->prepare(queryStr);
    qry->exec();
    model->setQuery(*qry);

    delete qry;

    return model;
};

bool DBLayer::UpdateQuote(QString quoteId, QString name, QString quote, int yearWritten, QString historicalContext, QString author, QString funfact) {
    QSqlQuery *qry = new QSqlQuery(db);
    bool result=true;

    QString queryStr = "";
    queryStr += "UPDATE quotebox SET";
    queryStr += " Name=\'" + name + "\',";
    queryStr += " Quote=\'" + quote + "\',";
    queryStr += " YearWritten=" + QString::number(yearWritten) +",";
    queryStr += " HistoricalContext=\'" + historicalContext + "\',";
    queryStr += " AuthorID=(SELECT a.AuthorId FROM Author a WHERE a.Name=\'" + author + "\')" +",";
    queryStr += " FunFactID=(SELECT f.FunFactID FROM FunFact f WHERE f.Title=\'" + funfact + "\')";
    queryStr += " WHERE QuoteId=" + quoteId;

    qDebug() << queryStr;

    qry->prepare(queryStr);
    result = qry->exec();

    delete qry;

    return result;
};

bool DBLayer::InsertQuote(QString name, QString quote, int yearWritten, QString historicalContext, QString author, QString funfact) {
    QSqlQuery *qry = new QSqlQuery(db);
    bool result=true;

    QString queryStr = "";
    queryStr += "INSERT INTO Quotebox (Name, Quote, YearWritten, HistoricalContext, AuthorID, FunFactID)";
    //VALUES ('Your First Program','Hello World! My name is <name>.','2000','The very first program every programmer has ever made.','1')
    queryStr += " VALUES (\'" + name + "\',";
    queryStr += " \'" + quote + "\',";
    queryStr += " " + QString::number(yearWritten) +",";
    queryStr += " \'" + historicalContext + "\',";
    queryStr += " (SELECT a.AuthorID FROM Author a WHERE a.Name=\'" + author + "\')" + ",";
    queryStr += " (SELECT f.FunFactID FROM FunFact f WHERE f.Title=\'" + funfact + "\'))";

    qDebug() << queryStr;

    qry->prepare(queryStr);
    result = qry->exec();

    delete qry;

    return result;
};
