#include "cscamerafolder.h"
#include "cscamerafolder_p.h"
#define declareConstructorMembers(p) \
    CSCamera(p), d(new CSCameraFolderPrivate(this))
#define declareConstructorPath \
    {setPath(path);}


CSCameraFolder::CSCameraFolder(QString      path) : declareConstructorMembers(0) declareConstructorPath
CSCameraFolder::CSCameraFolder(QDir         path) : declareConstructorMembers(0) declareConstructorPath
CSCameraFolder::CSCameraFolder(QFileInfo    path) : declareConstructorMembers(0) declareConstructorPath
CSCameraFolder::CSCameraFolder(QUrl         path) : declareConstructorMembers(0) declareConstructorPath

void CSCameraFolder::setPath(QDir       path){d->setDir(path);}
void CSCameraFolder::setPath(QString    path){setPath(QDir(path));}
void CSCameraFolder::setPath(QFileInfo  path){setPath(path.filePath());}
void CSCameraFolder::setPath(QUrl       path){setPath(path.toLocalFile());}


