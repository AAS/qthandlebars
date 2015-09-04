#ifndef QTHANDLEBARS_H
#define QTHANDLEBARS_H

#include "qthandlebars_global.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QString>

#include <QVector>

#ifdef QTHANDLEBARS_WITH_SQL
	#include <QSqlQuery>
	#include <QSqlRecord>
	#include <QSqlField>
#endif

class QTHANDLEBARSSHARED_EXPORT QtHandlebars
{
public:
	QtHandlebars();
	QtHandlebars(const QString &templateString, const QJsonObject &templateData = QJsonObject());
	static QtHandlebars fromFile(const QString &templateFileName, const QJsonObject &templateData = QJsonObject());
	~QtHandlebars();

	QString render() const;
	void setTemplate(const QString &templateString);
	void setTemplateFromFile(const QString &templateFile);
	void setData(const QJsonObject &templateData);
	void addJavaScriptCode(const QString &code);
	void addJavaScriptCode(const QStringList &codelist);
	void addJavaScriptCodeFromFile(const QString &file);
	void addJavaScriptCodeFromFiles(const QStringList &files);
	QJsonObject::iterator insert(const QString &key, QJsonValue value);
	QJsonObject::iterator insert(const QString &key, QVariantHash &hash);
	QJsonObject::iterator insert(const QString &key, QVariantMap &map);
	QJsonObject::iterator insert(const QString &key, QMap<QString, QString> &map);
#ifdef QTHANDLEBARS_WITH_SQL
	QJsonObject::iterator insert(const QString &key, QSqlQuery query, bool onlyFirst = false);
#endif
	QString getJsonAsString() const;

	void setTimeFormat(const QString &format);
	void setDateFormat(const QString &format);
	void setDateTimeFormat(const QString &format);

protected:
	QString _template;
	QJsonObject _data;
	QStringList _additionalJs;

	QString _dateFormat;
	QString _timeFormat;
	QString _datetimeFormat;
};

#endif // QTHANDLEBARS_H
