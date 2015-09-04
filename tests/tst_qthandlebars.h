#include <QtTest>

class TestsQtHandlebars : public QObject
{
	Q_OBJECT

public:
	TestsQtHandlebars();

private Q_SLOTS:
	void initTestCase();
	void cleanupTestCase();

	void testEmptyRender();
	void testRenderHelloWorld();
	void testRenderHelloWorldWithVariables();
	void testHelloWorldJsonData();
};
