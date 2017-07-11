#pragma once
#include <QObject>
#include <QString>


class QLogging : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text  READ text  NOTIFY textChanged)

public:
    explicit QLogging(QObject *parent = nullptr);

    QString text() const;
    Q_SIGNAL void textChanged();

    Q_INVOKABLE void clear();

private:

    void update();

    static void myMessageHandler(QtMsgType type, const QMessageLogContext &, const QString & msg);

    static QString _text;
    static bool _changed;
};


