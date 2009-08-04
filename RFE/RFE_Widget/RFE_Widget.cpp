#include <QtGui>

#include "RFE_Widget.h"
#include "RFE_StandardItem.h"
#include "RFE_ImagePreview.h"

namespace RFE
{

Widget::Widget(QWidget *parent)
: QWidget(parent)
{
	setupLayout();
}

void Widget::setupLayout()
{
	QVBoxLayout *mainLayout = new QVBoxLayout(this);

	modelView = new QStandardItemModel(this);
	modelView->setHorizontalHeaderItem(0, new QStandardItem(tr("Resources")));
	treeView = new QTreeView(this);
	treeView->setModel(modelView);
	
	QHBoxLayout *projectLocationLayout = new QHBoxLayout;
	projectLocation = new QLineEdit;
	QPushButton *selectProjectLocation = new QPushButton(QIcon(":/icons/open.png"), "");
	projectLocationLayout->addWidget(projectLocation);
	projectLocationLayout->addWidget(selectProjectLocation);

	QVBoxLayout *rightLayout = new QVBoxLayout;

	path = new QLineEdit();
	path->setEnabled(false);
	selectResource = new QPushButton(QIcon(":/icons/open.png"), "");
	selectResource->setEnabled(false);

	QGridLayout *gridLayout = new QGridLayout;
	gridLayout->addWidget(new QLabel(tr("Path:")), 0, 0);
	gridLayout->addWidget(path, 0, 1);
	gridLayout->addWidget(selectResource, 0, 2);

	rightLayout->addLayout(gridLayout);

	QHBoxLayout *buttonLayout = new QHBoxLayout;

	moveUp = new QPushButton(QIcon(":/icons/up.png"), "");
	moveUp->setEnabled(false);
	moveDown = new QPushButton(QIcon(":/icons/down.png"), "");
	moveDown->setEnabled(false);
	addItem = new QPushButton(QIcon(":/icons/add.png"), "");
	addItem->setEnabled(false);
	addGroup = new QPushButton(QIcon(":/icons/group_add.png"), "");
	//addGroup->setEnabled(false);
	remove = new QPushButton(QIcon(":/icons/rem.png"), "");
	remove->setEnabled(false);

	buttonLayout->addWidget(moveUp);
	buttonLayout->addWidget(moveDown);
	buttonLayout->addWidget(addItem);
	buttonLayout->addWidget(addGroup);
	buttonLayout->addWidget(remove);

	rightLayout->addLayout(buttonLayout);

	QObject::connect(treeView, SIGNAL(clicked(const QModelIndex&)), this, SLOT(treeViewClicked(const QModelIndex&)));
	QObject::connect(treeView, SIGNAL(activated(const QModelIndex&)), this, SLOT(treeViewItemActivated(const QModelIndex&)));
	QObject::connect(treeView, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(treeViewDoubleClicked(const QModelIndex&))); 
	QObject::connect(selectResource, SIGNAL(clicked()), this, SLOT(onSelectResource()));
	QObject::connect(addItem, SIGNAL(clicked()), this, SLOT(addNewItem()));
	QObject::connect(addGroup, SIGNAL(clicked()), this, SLOT(addNewGroup()));
	QObject::connect(remove, SIGNAL(clicked()), this, SLOT(onRemove()));
	QObject::connect(selectProjectLocation, SIGNAL(clicked()), this, SLOT(onSelectProjectLocation()));
	QObject::connect(moveUp, SIGNAL(clicked()), this, SLOT(onMoveUp()));
	QObject::connect(moveDown, SIGNAL(clicked()), this, SLOT(onMoveDown()));

	mainLayout->addLayout(projectLocationLayout);
	mainLayout->addWidget(treeView);
	mainLayout->addLayout(rightLayout);

	setLayout(mainLayout);
}

void Widget::addNewGroup()
{
	if(modelView->rowCount() == 0)
	{
		QStandardItem *item = new StandardItem(QIcon(":/icons/group.png"), tr("default"));
		item->setEditable(false);
		modelView->appendRow(item);
		treeView->setCurrentIndex( item->index() );
		treeViewClicked( item->index() );
	}
	else
	{
		QStandardItem *item = new StandardItem(QIcon(":/icons/group.png"), tr("new Group"));
		modelView->appendRow(item);
		treeView->setCurrentIndex( item->index() );
		treeViewClicked( item->index() );
	}
}

void Widget::addNewGroup(const QString &groupName)
{
	if(modelView->rowCount() == 0)
	{
		QStandardItem *item = new StandardItem(QIcon(":/icons/group.png"), groupName);
		item->setEditable(false);
		modelView->appendRow(item);
		treeView->setCurrentIndex( item->index() );
		treeViewClicked( item->index() );
	}
	else
	{
		QStandardItem *item = new StandardItem(QIcon(":/icons/group.png"), groupName);
		modelView->appendRow(item);
		treeView->setCurrentIndex( item->index() );
		treeViewClicked( item->index() );
	}
}

void Widget::addNewItem()
{
	if(treeView->currentIndex().row() != -1)
	{
		StandardItem *newResource = new StandardItem(tr("new Resource"));

		if(treeView->currentIndex().parent().row() != -1)
		{
			modelView->itemFromIndex( treeView->currentIndex().parent() )->appendRow(newResource);
			treeView->setCurrentIndex( newResource->index() );
			treeViewClicked( newResource->index() );
		}
		else
		{
			modelView->itemFromIndex( treeView->currentIndex() )->appendRow(newResource);
			treeView->setCurrentIndex( newResource->index() );
			treeViewClicked( newResource->index() );
		}
	}
}

void Widget::addNewItem(const QString &resourceName, const QString &resourcePath)
{
	if(treeView->currentIndex().row() != -1)
	{
		StandardItem *newResource = new StandardItem(resourceName);
		newResource->setPath(resourcePath);
		newResource->setIcon(QIcon(resourcePath));

		if(treeView->currentIndex().parent().row() != -1)
		{
			modelView->itemFromIndex( treeView->currentIndex().parent() )->appendRow(newResource);
			treeView->setCurrentIndex( newResource->index() );
			treeViewClicked( newResource->index() );
		}
		else
		{
			modelView->itemFromIndex( treeView->currentIndex() )->appendRow(newResource);
			treeView->setCurrentIndex( newResource->index() );
			treeViewClicked( newResource->index() );
		}
	}
}

void Widget::saveResourceFile()
{
	if( modelView->rowCount() > 0 )
	{
		QString fileName = QFileDialog::getSaveFileName(this, tr("choose Resourcefile"), ".", tr("Resourcefile (*.qrc)"));
		if(!fileName.isEmpty())
		{
			QFile inputFile(fileName);

			if(inputFile.open(QIODevice::WriteOnly | QIODevice::Text))
			{
				QTextStream textStream(&inputFile);
				textStream << "<!DOCTYPE RCC><RCC version=\"1.0\">\n";

				for( int counter = 0; counter < modelView->rowCount(); counter++ )
				{
					QStandardItem *item = modelView->item( counter );

					if( item->text() == "" || item->text() == "default" )
					{
						textStream << "<qresource>\n";
					}
					else
					{
						textStream << "<qresource prefix=\"" << item->text() << "\">\n";
					}

					for( int innerCounter = 0; innerCounter < item->rowCount(); innerCounter++ )
					{
						QStandardItem *innerItem = item->child( innerCounter );
						QString path = ((RFE::StandardItem*)(innerItem))->getPath();

						if( !projectLocation->text().isEmpty() )
						{
							if( path.indexOf(projectLocation->text()) >= 0 )
							{
								path = path.mid( projectLocation->text().size() + 1 );
							}
						}

						if( innerItem->text().isEmpty() )
						{
							textStream << "\t<file>" << path << "</file>\n";
						}
						else
						{
							textStream << "\t<file alias=\"" << innerItem->text() << "\">" << path << "</file>\n";
						}
					}

					textStream << "</qresource>\n";
				}

				textStream << "</RCC>";
				inputFile.close();
			}
			else
			{
				QMessageBox::critical(this, "RFE", tr("The file could not be opened!"));
			}
		}
	}
	else
	{
		QMessageBox::information(this, "RFE", tr("No data to be saved!"));
	}
}

void Widget::loadResourceFile()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("choose Resourcefile"), ".", tr("Resourcefile (*.qrc)"));
	
	if(!fileName.isEmpty())
	{
		QFile inputFile(fileName);

		if(inputFile.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			QTextStream textStream(&inputFile);
			QString line = textStream.readLine();

			if( line.indexOf("<!DOCTYPE RCC><RCC version=\"1.0\">") >=0 )
			{
				modelView->clear();
				modelView->setHorizontalHeaderItem(0, new QStandardItem(tr("Resources")));
				path->setText("");
				path->setEnabled(false);
				addItem->setEnabled(false);
				moveUp->setEnabled(false);
				moveDown->setEnabled(false);

				line = textStream.readLine();
				while( !line.isEmpty() )
				{
					if( line.indexOf( "<qresource>" ) >= 0 )
					{
						// add default group
						addNewGroup(QString("default"));
					}

					if( line.indexOf( "<qresource prefix=\"" ) >= 0 )
					{
						// add named group
						addNewGroup( line.mid(19, line.lastIndexOf( "\">" ) - 19 ) );
					}

					if( line.indexOf( "<file>" ) >= 0 )
					{
						// add item without alias
						QString name = line.mid(line.indexOf( "<file>" ) + 6, line.lastIndexOf( "</file>" ) - (line.indexOf( "<file>" ) + 6));
						addNewItem(QString(""), name );
					}

					if( line.indexOf( "<file alias=\"" ) >= 0 )
					{
						// add item with alias
						QString alias = line.mid(line.indexOf( "<file alias=\"" ) + 13, line.lastIndexOf( "\">" ) - (line.indexOf( "<file alias=\"" ) + 13));
						QString name = line.mid(line.indexOf( "\">" ) + 2, line.lastIndexOf( "</file>" ) - (line.indexOf( "\">" ) + 2));
						addNewItem(alias, name);
					}

					line = textStream.readLine();
				}
				
			}
			else
			{
				QMessageBox::information(this, "RFE", tr("The file does not seem to be well formed!"));
			}
		}
	}
}

void Widget::onSelectResource()
{
	QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("choose Resource"), ".", supportedImageFormats().toStdString().c_str());

	if( fileNames.size() >= 1 )
	{
		QString fileName = fileNames.at(0);

		path->setText(fileName);
		modelView->itemFromIndex(treeView->currentIndex())->setText( fileName.mid(fileName.lastIndexOf('/') + 1) );
		modelView->itemFromIndex(treeView->currentIndex())->setIcon( QIcon(fileName) );
		( (RFE::StandardItem*) (modelView->itemFromIndex(treeView->currentIndex()) ))->setPath(fileName);
	}

	if( fileNames.size() > 1 )
	{
		for(int counter = 1; counter < fileNames.size(); counter++)
		{
			addNewItem();
			
			QString fileName = fileNames.at(counter);

			path->setText(fileName);
			modelView->itemFromIndex(treeView->currentIndex())->setText( fileName.mid(fileName.lastIndexOf('/') + 1) );
			modelView->itemFromIndex(treeView->currentIndex())->setIcon( QIcon(fileName) );
			( (RFE::StandardItem*) (modelView->itemFromIndex(treeView->currentIndex()) ))->setPath(fileName);
		}
	}
}

void Widget::treeViewClicked( const QModelIndex & index )
{
	if( index.row() != -1 )
	{
		moveUp->setEnabled(true);
		moveDown->setEnabled(true);
		addItem->setEnabled(true);
		remove->setEnabled(true);

		if( index.parent().row() != -1 )
		{
			path->setEnabled(true);
			path->setText( ( (RFE::StandardItem*) (modelView->itemFromIndex(treeView->currentIndex()) ))->getPath() );
			selectResource->setEnabled(true);

			if( modelView->itemFromIndex(index)->row() == 0 )
			{
				moveUp->setEnabled(false);
			}
			
			if( modelView->itemFromIndex(index)->row() == modelView->itemFromIndex(index)->parent()->rowCount() - 1 )
			{
				moveDown->setEnabled(false);
			}
		}
		else
		{
			path->setEnabled(false);
			path->setText( "" );
			selectResource->setEnabled(false);

			if( modelView->itemFromIndex(index)->row() == 0 )
			{
				moveUp->setEnabled(false);
			}
			
			if( modelView->itemFromIndex(index)->row() == modelView->rowCount() - 1 )
			{
				moveDown->setEnabled(false);
			}
		}
	}
}

void Widget::treeViewDoubleClicked(const QModelIndex &index)
{
	if( index.row() != -1 )
	{
		if( index.parent().row() != -1 )
		{
			QString path = ((RFE::StandardItem*) (modelView->itemFromIndex(treeView->currentIndex()) ))->getPath();
			if(!path.isEmpty())
			{
				RFE::ImagePreview *imagePreview = new RFE::ImagePreview(path);
				imagePreview->show();
			}
		}
	}
}

void Widget::treeViewItemActivated( const QModelIndex & index )
{
	treeViewClicked(index);
}

QString Widget::supportedImageFormats()
{
	QString available_image_formats;
	QList<QByteArray> byte_array_list = QImageReader::supportedImageFormats();

	available_image_formats.append(tr("Imagefile ("));

	for(QList<QByteArray>::Iterator it = byte_array_list.begin(); it != byte_array_list.end(); ++it)
	{
            available_image_formats.append(QString(" *.") + it->data());
	}

	available_image_formats.append(" )");

	return(available_image_formats);
}

void Widget::onRemove()
{
	if(treeView->currentIndex().row() != -1)
	{
		if(treeView->currentIndex().parent().row() != -1)
		{
			modelView->removeRow(treeView->currentIndex().row(), treeView->currentIndex().parent());
			treeViewClicked( treeView->currentIndex() );
		}
		else
		{
			modelView->removeRow(treeView->currentIndex().row());
			treeViewClicked( treeView->currentIndex() );
		}
	}

	if( modelView->rowCount() == 0)
	{
		remove->setEnabled(false);
		addItem->setEnabled(false);
	}
}

void Widget::onSelectProjectLocation()
{
	QString folderName = QFileDialog::getExistingDirectory(this, tr("choose Projectfolder"), ".", QFileDialog::ShowDirsOnly);

	if(!folderName.isEmpty())
	{
		projectLocation->setText(folderName);
	}
}


void Widget::onMoveUp()
{
	if( treeView->currentIndex().row() >= 0 )
	{
		if( treeView->currentIndex().parent().row() >= 0 )
		{
			QStandardItem *parent = modelView->itemFromIndex( treeView->currentIndex().parent() );

			QStandardItem *item = parent->takeChild( treeView->currentIndex().row() );
			int oldRow = treeView->currentIndex().row();
			parent->removeRow( oldRow );
			parent->insertRow( oldRow - 1, item );
			treeView->setCurrentIndex( item->index() );
			treeViewClicked( item->index() );
		}
	}
}

void Widget::onMoveDown()
{
	if( treeView->currentIndex().row() >= 0 )
	{
		if( treeView->currentIndex().parent().row() >= 0 )
		{
			QStandardItem *parent = modelView->itemFromIndex( treeView->currentIndex().parent() );

			QStandardItem *item = parent->takeChild( treeView->currentIndex().row() );
			int oldRow = treeView->currentIndex().row();
			parent->removeRow( oldRow );
			parent->insertRow( oldRow + 1, item );
			treeView->setCurrentIndex( item->index() );
			treeViewClicked( item->index() );
		}
	}
}

} // namespace RFE
