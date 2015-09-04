#include "tst_qthandlebars.h"
#include "qthandlebars.h"

#include <QJsonDocument>

TestsQtHandlebars::TestsQtHandlebars()
{
}

void TestsQtHandlebars::initTestCase()
{

}

void TestsQtHandlebars::cleanupTestCase()
{
}

void TestsQtHandlebars::testEmptyRender()
{
	QtHandlebars h;
	QVERIFY(h.render().isEmpty());
}

void TestsQtHandlebars::testRenderHelloWorld()
{
	QString tmpl("Hello, world!");
	QtHandlebars h;
	h.setTemplate(tmpl);
	QVERIFY(h.render().compare(tmpl) == 0);
}

void TestsQtHandlebars::testRenderHelloWorldWithVariables()
{
	QString tmpl("{{a}}, {{b}}!");
	QtHandlebars h;
	h.setTemplate(tmpl);
	h.insert("a", "Hello");
	h.insert("b", "world");
	QVERIFY(h.render().compare("Hello, world!") == 0);
}

void TestsQtHandlebars::testHelloWorldJsonData()
{
	QJsonObject o;
	o.insert("a", "Hello");
	o.insert("b", "world");

	QJsonDocument d;
	d.setObject(o);

	QtHandlebars h;
	h.setData(o);

	QString from_qt(d.toJson(QJsonDocument::Compact));
	QString from_hb(QJsonDocument::fromJson(h.getJsonAsString().toUtf8()).toJson(QJsonDocument::Compact));

	QVERIFY(from_qt.compare(from_hb) == 0);
}

QTEST_APPLESS_MAIN(TestsQtHandlebars)
