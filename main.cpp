#include <QCoreApplication>
#include <QVector>
#include <QString>
#include <QtDebug>
#include <QFile>

QVector<QString> convertFromStirngToStringVector(QString str){
    QVector<QString> tmp;

    for(int i = 0; i < str.length(); i++){
        tmp.append( str.left(str.indexOf(" ",i, Qt::CaseInsensitive)));
        str.remove(tmp.last());
        tmp.last().replace(" ","");
        i = 0;
    }
  return tmp;
}

void vectors_print(QVector<QVector<QString>> print) {
    for(int i = 0; i < print.length(); i++){
        qDebug() << QString::number(i) << "\t --> " << print.at(i).length() << " words.";
        for(int j = 0; j < print.at(i).length(); j++)
            qDebug() << "\t"<< QString::number(j) << "\t\t" << print.at(i).at(j)
                     << "\t--> " << print.at(i).at(j).length()<< " simbols";

    }
}

void getInfo(QVector<QVector<QString>> data,QString file_name) {
    QFile info(file_name + "_" +  "info.txt");
    if(info.open(QIODevice::ReadWrite)){
        QTextStream out(&info);

        for(int i = 0; i < data.length(); i++){
            for(int j = 0; j < data.at(i).length(); j++){
                out << QString::number(j) << "\t" << data.at(i).at(j)
                         << "--> " << data.at(i).at(j).length()<< " simbols";
                out << "\r\n";
            }
            out << QString::number(i) << "\t --> " << data.at(i).length() << " words.";
            out << "\r\n";
            out << "\r\n";
        }
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QVector<QVector<QString>> hard;

    QFile count_starts("starts.txt");
    if(count_starts.open(QIODevice::ReadWrite)){
        QTextStream out(&count_starts);
        QString n = out.readAll();
        int c = n.toInt();
        c++ ;
        out << QString::number(c);
    }
    count_starts.close();

  //  hard.append(convertFromStirngToStringVector("I hate vectors and Victors"));
  //  hard.append(convertFromStirngToStringVector("But I love C++"));
    //vectors_print(hard);

    int total_count = 0;
    for(int i = 0; i < hard.length(); i++){
        total_count += hard.at(i).count("hate");
    }

    qDebug() << hard;
    qDebug() << total_count;

    //return a.exec();

//    запись файла
//    QFile mFile("t.txt");

//    if(mFile.open(QIODevice::ReadWrite)){
//        QTextStream out(&mFile);
//        out<< "MF";

//    }
//    mFile.close();

//    читать файл
    QString file_name = "t.txt";
    QFile mFile(file_name);
    if(!mFile.open(QIODevice::ReadOnly)){
        qDebug() << "error file name!";
    }

    QTextStream in(&mFile);
    while (!in.atEnd()) {
        //64 - кол-тво символов за раз
        //qDebug() << in.read(64);
//        qDebug() << in.readLine();
          hard.append(convertFromStirngToStringVector(in.readLine()));
    }

    vectors_print(hard);
    getInfo(hard, file_name);


    return 1;
}
