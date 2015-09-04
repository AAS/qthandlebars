#include "qthandlebars.h"

#include <QDate>
#include <QFile>
#include <QJSEngine>
#include <QJsonDocument>
#include <QJsonArray>
#include <QTextStream>

static QString getFileContent(const QString &fileName, bool *ok = 0)
{
	QFile f(fileName);

	if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		if(ok != 0)
			*ok = false;

		return QString();
	}

	QTextStream ts(&f);
	ts.setCodec("UTF-8");
	QString s = ts.readAll();
	f.close();

	if(ok != 0)
		*ok = true;

	return s;
}

QtHandlebars::QtHandlebars()
{
}

QtHandlebars::QtHandlebars(const QString &templateString, const QJsonObject &templateData):
	_template(templateString),
	_data(templateData)
{
}

QtHandlebars QtHandlebars::fromFile(const QString &templateFileName, const QJsonObject &templateData)
{
	QtHandlebars t;
	t.setTemplateFromFile(templateFileName);

	if(!templateData.isEmpty())
		t.setData(templateData);

	return t;
}

QtHandlebars::~QtHandlebars()
{
}

QString QtHandlebars::render() const
{
	QJSEngine e;
	e.globalObject().setProperty("source", QJSValue(this->_template));

	bool ok = false;
	QString hbjs = getFileContent(":/qthandlebars/js", &ok);

	if(!ok)
		return "Unable to open handlebars.js";

	if(e.evaluate(hbjs).isError())
		return "Unable to evaluate handlebars.js";

	for(auto i: this->_additionalJs)
	{
		if(e.evaluate(i).isError())
			return "Unable to evaluate additional js";
	}

	QString jsCall = QString("Handlebars.compile(source)(%1);").arg(
		QString(QJsonDocument(this->_data).toJson(QJsonDocument::Compact)));

	return e.evaluate(jsCall).toString();
}

void QtHandlebars::setTemplate(const QString &templateString)
{
	this->_template = templateString;
}

void QtHandlebars::setTemplateFromFile(const QString &templateFile)
{
	this->_template = getFileContent(templateFile);
}

void QtHandlebars::setData(const QJsonObject &templateData)
{
	this->_data = templateData;
}

void QtHandlebars::addJavaScriptCode(const QString &code)
{
	this->_additionalJs.append(code);
}

void QtHandlebars::addJavaScriptCode(const QStringList &codelist)
{
	for(auto &i: codelist)
		this->addJavaScriptCode(i);
}

void QtHandlebars::addJavaScriptCodeFromFile(const QString &file)
{
	this->addJavaScriptCode(getFileContent(file));
}

void QtHandlebars::addJavaScriptCodeFromFiles(const QStringList &files)
{
	for(auto &i: files)
		this->addJavaScriptCodeFromFile(i);
}

QJsonObject::iterator QtHandlebars::insert(const QString &key, QJsonValue value)
{
	return this->_data.insert(key, value);
}

QJsonObject::iterator QtHandlebars::insert(const QString &key, QVariantHash &hash)
{
	return this->insert(key, QJsonObject::fromVariantHash(hash));
}

QJsonObject::iterator QtHandlebars::insert(const QString &key, QVariantMap &map)
{
	return this->insert(key, QJsonObject::fromVariantMap(map));
}

QJsonObject::iterator QtHandlebars::insert(const QString &key, QMap<QString, QString> &map)
{
	QVariantMap vmap;

	for(const QString &k: map.keys())
		vmap.insert(k, map.value(k));

	return this->insert(key, vmap);
}

#ifdef QTHANDLEBARS_WITH_SQL
QJsonObject::iterator QtHandlebars::insert(const QString &key, QSqlQuery query, bool onlyFirst)
{
	if(!query.isActive())
	{
		if(!query.exec())
		{
			return QJsonObject::iterator();
		}
	}

	QJsonArray a;

	while(query.next())
	{
		QJsonObject o;
		QSqlRecord r = query.record();

		for(int i = 0; i < r.count(); i++)
		{
			if(r.field(i).type() == QVariant::Date && !this->_dateFormat.isEmpty())
				o.insert(r.fieldName(i), r.value(i).toDate().toString(this->_dateFormat));
			if(r.field(i).type() == QVariant::Time && !this->_timeFormat.isEmpty())
				o.insert(r.fieldName(i), r.value(i).toTime().toString(this->_timeFormat));
			else if(r.field(i).type() == QVariant::DateTime && !this->_datetimeFormat.isEmpty())
				o.insert(r.fieldName(i), r.value(i).toDate().toString(this->_datetimeFormat));
			else if(r.field(i).type() == QVariant::Int)
				o.insert(r.fieldName(i), r.value(i).toInt());
			else
				o.insert(r.fieldName(i), r.value(i).toString());
		}

		if(onlyFirst)
		{
			this->insert(key, o);
			return QJsonObject::iterator();
		}

		a.append(o);
	}

	return this->insert(key, a);
}
#endif

QString QtHandlebars::getJsonAsString() const
{
	return QString(QJsonDocument(this->_data).toJson());
}

void QtHandlebars::setTimeFormat(const QString &format)
{
	this->_timeFormat = format;
}

void QtHandlebars::setDateFormat(const QString &format)
{
	this->_dateFormat = format;
}

void QtHandlebars::setDateTimeFormat(const QString &format)
{
	this->_datetimeFormat = format;
}
