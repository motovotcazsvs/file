#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTextStream>
#include <QDebug>
#include <QDir>
#include <QDateTime>
#include <QFileDialog>

void writeFile(QString, int);
void writeFile(QFile &, QString);
void writeFile(QFile &, QString &, int);


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString file_settings_path = "settingsfile.txt";
    QFile settings_file(file_settings_path);

    file_data_path = QDir::currentPath();
    save_settings_comport = "com7";
    save_settings_speed = "9600";

    if(settings_file.exists(file_settings_path)){
        qDebug() << "Файл существует";
        QTextStream cin(&settings_file);
        QStringList file_settings_strings;

        if(settings_file.open(QIODevice::ReadOnly)){
            for(int i = 0; i < 3; i++) file_settings_strings << cin.readLine();
            settings_file.close();
        }

        file_data_path = file_settings_strings[0];
        save_settings_comport = file_settings_strings[1];
        save_settings_speed = file_settings_strings[2];
    }
    else {
        qDebug() << "Файл не существует!";
        settings_file.open(QIODevice::WriteOnly); //| QIODevice::Text);
        QTextStream cout(&settings_file);
        cout << file_data_path << "\n";
        cout << save_settings_comport << "\n";
        cout << save_settings_speed << "\n";
        settings_file.close();
    }

    qDebug() << file_data_path << endl << save_settings_comport << endl << save_settings_speed << endl;
    QDateTime dat;
    dat = QDateTime::currentDateTime();
    QString d;
    d = dat.toString("dd.MM.yyyy");
    qDebug() << d;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    QDateTime dat = QDateTime::currentDateTime();
    QString d = dat.toString("dd.MM.yyyy");
    QString name_new_file(file_data_path + "/" + d + ".txt");
    QFile new_file(name_new_file);
    qDebug() << name_new_file;
    if(new_file.exists(name_new_file)){
       writeFile(new_file, "дописано");
    }
    else {
        new_file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream cout(&new_file);
        QString s = "написано";
        cout << s << endl;
        new_file.close();
    }
}

void MainWindow::on_pushButton_clicked()
{
    QString open_folder = QFileDialog::getExistingDirectory(this, tr("папка сохранянея файлов"), QDir::currentPath(),
                                                   QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    file_data_path = open_folder;
    writeFile(file_data_path, 0);
    qDebug() << open_folder;
}

void writeFile(QString str, int num_str)//только для файла настройки бо все в одну строку
{
    QFile file("settingsfile.txt");
    QStringList strList;
    /*Считываем исходный файл в контейнер*/
    if(file.open(QIODevice::ReadOnly)){
        while(!file.atEnd()){
            strList << file.readLine();
        }
        file.close();
    }
    /*Добавляем строку и сохраняем содержимое контейнера в тот же файл*/
    if(file.open(QIODevice::WriteOnly)){// | QIODevice::Text)){
        strList[num_str] = str + "\n";
        QTextStream stream(&file);
        foreach(QString s, strList){
            qDebug() << s;
        }
        foreach(QString s, strList){
            stream << s;

        }

        file.close();
    }
}

void writeFile(QFile &file, QString str)
{
    QTextStream stream(&file);
    if (file.open(QIODevice::Append | QIODevice::Text)) {
       stream << str << endl;
    }
    file.close();
}

void writeFile(QFile &file, QString &str, int num_str)
{
    QStringList strList;
    /*Считываем исходный файл в контейнер*/
    if(file.open(QIODevice::ReadOnly)){
        while(!file.atEnd()){
            strList << file.readLine();
        }
        file.close();
    }
    /*Добавляем строку и сохраняем содержимое контейнера в тот же файл*/
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
        strList[num_str] = str + "\n";
        QTextStream stream(&file);

        foreach(QString s, strList){
            stream << s << endl;

        }

        file.close();
    }
}
