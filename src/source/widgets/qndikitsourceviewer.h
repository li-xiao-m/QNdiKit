#ifndef QNDIKITSOURCEVIEWER_H
#define QNDIKITSOURCEVIEWER_H

#include <QWidget>

class QNDIKITSOURCE_EXPORT QNdiKitSourceViewer : public QWidget
{
    Q_OBJECT

public:
    explicit QNdiKitSourceViewer(QWidget *parent = nullptr);
    ~QNdiKitSourceViewer();
};

#endif // QNDIKITSOURCEVIEWER_H 