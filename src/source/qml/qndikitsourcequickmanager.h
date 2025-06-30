#ifndef QNDIKITSOURCEQUICKMANAGER_H
#define QNDIKITSOURCEQUICKMANAGER_H

#include <QObject>

class QNDIKITSOURCE_EXPORT QNdiKitSourceQuickManager : public QObject
{
    Q_OBJECT

public:
    explicit QNdiKitSourceQuickManager(QObject *parent = nullptr);
    ~QNdiKitSourceQuickManager();
};

#endif // QNDIKITSOURCEQUICKMANAGER_H 