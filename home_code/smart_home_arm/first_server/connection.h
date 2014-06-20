#ifndef CONNECTION_H
#define CONNECTION_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "utils.h"
#include <QDebug>
/*
    This file defines a helper function to open a connection to an
    in-memory SQLITE database and to create a test table.

    If you want to use another database, simply modify the code
    below. All the examples in this directory use this function to
    connect to a database.
*/
static bool createConnection()
{
    //添加sqlite数据库支持
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    //设置数据库名称
    db.setDatabaseName(Utils::DATABASE_NAME);
    //尝试打开数据库
    if (!db.open()) {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
            qApp->tr("Unable to establish a database connection.\n"
                     "This example needs SQLite support. Please read "
                     "the Qt SQL driver documentation for information how "
                     "to build it.\n\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
        return false;
    }

    QSqlQuery query;

    query.exec("drop table node_data");


    query.exec("create table node_data (node_id int primary key,node_name varchar(40),"
               "node_type varchar(20),node_value varchar(6),"
               "node_value_min varchar(8),node_value_max varchar(8))");
    query.exec("create unique index myid on node_data (node_id) ");
    qDebug()<<"creat success!";
    query.exec("insert into node_data values(101, 'temperature', 'value','35','10','40')");
    query.exec("insert into node_data values(102, 'humidity', 'value','50','10','40')");
//    query.exec("insert into node_data values(103, 'temperature2', 'value','351','10','40')");
    query.exec("insert into node_data values(104, 'temperature3', 'value','35','210','40')");
//    query.exec("insert into node_data values(105, 'temperature4', 'value','352','10','40')");
//    query.exec("update  node_data (node_id,node_value)""VALUES(102,'213')");
//    query.exec("insert or replace into node_data (node_id,node_value) values (101,'333')");
//    query.exec("insert or replace into node_data (node_id,node_value) values (101,'333')");
//    query.exec("replace into node_data values(101, 'temperature', 'vae','3.5','10','40')");
//    query.exec("insert or replace into node_data values(102, 'temperatu2222re1', 'value','305','10','40')");
//    query.exec("insert into node_data values(103, 'temperature2', 'value','351','10','40')");
//    query.exec("insert into node_data values(104, 'temperature3', 'value','35','210','40')");
//    query.exec("insert or replace into node_data values(105, 'te4', 'value','352','10','40')");
//    query.exec("update node_data set node_value = 999 where node_id = 101");
//    query.exec("insert into node_data values(105, 'temperature5', 'value','325','10','40')");
/*
    query.exec("create table node_data (id int primary key, "
               "name varchar(40),team varchar(20),age varchar(5),ss varchar(7))");
    query.exec("insert into node_data values(101, 'Manu Ginobili', 'spurs','35','213')");
    query.exec("insert into node_data values(102, 'Rudy Gay', 'memphis','26','213')");
    query.exec("insert into node_data values(103, 'Dirk Nowitzki', 'mavericks','34','213')");
    query.exec("insert into node_data values(104, 'Jeremy Lin', 'rocket','24','213')");
    query.exec("insert into node_data values(105, 'Anthony Davis', 'hornets','19','213')");
    */

/*
    query.exec("create table person (id int primary key, "
               "firstname varchar(20), lastname varchar(20))");
    query.exec("insert into person values(101, 'Danny', 'Young')");
    query.exec("insert into person values(102, 'Christine', 'Holand')");
    query.exec("insert into person values(103, 'Lars', 'Gordon')");
    query.exec("insert into person values(104, 'Roberto', 'Robitaille')");
    query.exec("insert into person values(105, 'Maria', 'Papadopoulos')");



    query.exec("create table offices (id int primary key,"
                                             "imagefile int,"
                                             "location varchar(20),"
                                             "country varchar(20),"
                                             "description varchar(100))");
    query.exec("insert into offices "
               "values(0, 0, 'Oslo', 'Norway',"
               "'Oslo is home to more than 500 000 citizens and has a "
               "lot to offer.It has been called \"The city with the big "
               "heart\" and this is a nickname we are happy to live up to.')");
    query.exec("insert into offices "
               "values(1, 1, 'Brisbane', 'Australia',"
               "'Brisbane is the capital of Queensland, the Sunshine State, "
               "where it is beautiful one day, perfect the next.  "
               "Brisbane is Australia''s 3rd largest city, being home "
               "to almost 2 million people.')");
    query.exec("insert into offices "
               "values(2, 2, 'Redwood City', 'US',"
               "'You find Redwood City in the heart of the Bay Area "
               "just north of Silicon Valley. The largest nearby city is "
               "San Jose which is the third largest city in California "
               "and the 10th largest in the US.')");
    query.exec("insert into offices "
               "values(3, 3, 'Berlin', 'Germany',"
               "'Berlin, the capital of Germany is dynamic, cosmopolitan "
               "and creative, allowing for every kind of lifestyle. "
               "East meets West in the metropolis at the heart of a "
               "changing Europe.')");
    query.exec("insert into offices "
               "values(4, 4, 'Munich', 'Germany',"
               "'Several technology companies are represented in Munich, "
               "and the city is often called the \"Bavarian Silicon Valley\". "
               "The exciting city is also filled with culture, "
               "art and music. ')");
    query.exec("insert into offices "
               "values(5, 5, 'Beijing', 'China',"
               "'Beijing as a capital city has more than 3000 years of "
               "history. Today the city counts 12 million citizens, and "
               "is the political, economic and cultural centre of China.')");

    query.exec("create table images (locationid int, file varchar(20))");
    query.exec("insert into images values(0, 'images/oslo.png')");
    query.exec("insert into images values(1, 'images/brisbane.png')");
    query.exec("insert into images values(2, 'images/redwood.png')");
    query.exec("insert into images values(3, 'images/berlin.png')");
    query.exec("insert into images values(4, 'images/munich.png')");
    query.exec("insert into images values(5, 'images/beijing.png')");
*/
    return true;
}
//! [0]

#endif
