#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "Panels/BrowsePanel.h"

class FileManager: public QObject
{
	Q_OBJECT
public:
	explicit FileManager(BrowsePanel* pLeft, BrowsePanel* pRight);

    void createFolder(const QString &current_path);

public slots:
	void copy();
    void remove();
    void remove(BrowsePanel* senderPanel);
	void move();	

private:
	BrowsePanel* m_pLeft;
	BrowsePanel* m_pRight;

    void copy(BrowsePanel* senderPanel);
    void copyDir(const QString& sSource, const QString& sDest);
    void removeDir(const QString& sPath);


};

#endif // FILEMANAGER_H
