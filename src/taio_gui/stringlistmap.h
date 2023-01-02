#ifndef STRINGLISTMAP_H
#define STRINGLISTMAP_H

#include <QString>
#include <QStringList>
#include <QMap>
#include <QMetaType>

class StringMap : public QMap<QString, QStringList> {

};
Q_DECLARE_METATYPE(StringMap)

#endif // STRINGLISTMAP_H
