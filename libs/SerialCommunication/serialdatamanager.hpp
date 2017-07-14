#ifndef SERIALDATAMANAGER_H
#define SERIALDATAMANAGER_H

#include <QObject>
#include <QWidget>
#include <QStringList>
#include <QQueue>
#include <QRegExp>
#include <QVector>
#include <QMap>
#include <QDebug>

#include "serialportrecorder.hpp"
#include "serialsettings.hpp"

class SerialDataManager : public QObject
{
    Q_OBJECT
public:
	explicit SerialDataManager( QObject *parent = 0, QWidget *widget = 0 );

    // Pure Variables in Serial without Titles
    // e.g.
    // Case 1: 555\r555\r555\r [...] -> Each carriage return has 1 Vars

    // Case 2: 555 555\r555 555\r555 555\r [...] -> Each carriage return has more than 1 Vars

    // Case 3: 555 555 555\r555 555\r555\r [...] -> On each carriage return there is a different amount of Vars
    static QVector<QVector<int>> getIntData( const QByteArray &data );
    QVector<QVector<int>> getIntData( );
    static QVector<QVector<double>> getDoubleData( const QByteArray &data );
    QVector<QVector<double>> getDoubleData( );
    static QVector<QVector<QString>> getStringData( const QByteArray &data );
    QVector<QVector<QString>> getStringData( );

    // In case our input has Titles for each Variable
    // e.g.
    // Gender 555 Sex 238\rGender 238 Sex 777
    QMap<QString, int> getMappedIntegers( const QByteArray &data );
    QMap<QString, int> getMappedIntegers( );
    QMap<QString, double> getMappedDoubles( const QByteArray &data );
    QMap<QString, double> getMappedDoubles( );

    QByteArray getData( ) const;

    void getUnfinishedValue( );

    SerialPortRecorder *serialRecorder;
signals:
    void dataChanged( );

private slots:
    void setData();
    void readBytes( );

private:
    QByteArray data;
    QByteArray carry; // Carries the last unfinished string (unfinshed = NotEndsWith( \n or \r ) )
	QWidget *widget;


};
#endif // SERIALDATAMANAGER_H
