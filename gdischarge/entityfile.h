#ifndef ENTITYFILE_H
#define ENTITYFILE_H

#include <QStringList>

class EntityFile
{
public:
    EntityFile();

    // Setters
    void setFileName();         //H20190909-000000N3N1C0.avi
    void setFileType();         //Arquivo AVI ou Pasta de arquivos
    void setFileExtension();    //.avi
    void setFileSize();         //54.047KB
    void setDataModified();     //19/09/2019 13:14

private:
    QStringList m_FileName;
    QStringList m_FileType;
    QStringList m_FileExtension;
    QStringList m_FileSize;
    QStringList m_DateModified;
};

#endif // ENTITYFILE_H
