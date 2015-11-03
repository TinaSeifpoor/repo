#include "visionitem.h"

VisionItem::VisionItem(QFileInfo fileInfo)
{
    setFileInfo(fileInfo);
    setName(FileInfo().baseName());
    setIcon(QIcon(FileInfo().filePath()));
}
