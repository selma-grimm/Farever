#ifndef BROWSETABLE_H
#define BROWSETABLE_H

class BrowseModel;

class BrowseTable : public QTreeView
{
    Q_OBJECT
public:
	explicit BrowseTable(QWidget *parent);

	void            goToPath(const QString& sPath);
	void            goToDisk(const QString& sPath);
	void            setModel(QAbstractItemModel* pModel);
	QModelIndexList selectedIndexes();
    void            setHeader(QHeaderView * header);

protected:
    virtual void	drawBranches(QPainter * painter, const QRect & rect, const QModelIndex & index) const;

private:
    BrowseModel* m_pFS;
	QStack<QModelIndex> m_expandStack;
	QModelIndex m_editingIndex;
    
signals:
    
public slots:
	void selectFirst(const QString &sPath);
	void restorEditedSelection();

private slots:
    void onExpanded(const QModelIndex &index);
    void onCollapsed(const QModelIndex &index);

protected:
	//bool	event(QEvent* event);
	void	keyPressEvent(QKeyEvent* event);
	void	resizeEvent(QResizeEvent * event);


    
};

#endif // BROWSETABLE_H
