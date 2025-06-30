#ifndef FINDNDISOURCEWORKER_H
#define FINDNDISOURCEWORKER_H

#include <Processing.NDI.Lib.h>
#include <QObject>
#include <QVariant>
#include "qndimanagercore_global.h"
#include "qndimanagercore.h"

namespace QNK
{
    namespace Manager
    {
        class QNDIMANAGERCORE_EXPORT FindNdiSourceWorker : public QObject
        {
            Q_OBJECT
        public:
            explicit FindNdiSourceWorker(QObject *parent = nullptr);

        public slots:
            void handle(const QNK::Manager::QNdiManagerCore::NdiManagerType &type,
                        const QVariant &param);

        signals:
            void answer(const QNK::Manager::QNdiManagerCore::NdiManagerType &type,
                        const QVariant &param,
                        const bool &isSuccess,
                        const QString &message);

        private:
            void initializeNDI();
            void handleFindNdiSource(const QNK::Manager::QNdiManagerCore::NdiManagerType &type, const QVariant &param = QVariant());

        private:
            NDIlib_find_instance_t m_pNDI_find{nullptr};
        };
    }
}

#endif // FINDNDISOURCEWORKER_H
