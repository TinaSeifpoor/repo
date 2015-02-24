#ifndef RDFMODULE_GLOBAL_H
#define RDFMODULE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(RDFMODULE_LIBRARY)
#  define RDFMODULESHARED_EXPORT Q_DECL_EXPORT
#else
#  define RDFMODULESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // RDFMODULE_GLOBAL_H
