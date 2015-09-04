#ifndef QTHANDLEBARS_GLOBAL_H
#define QTHANDLEBARS_GLOBAL_H

#include <QtCore/qglobal.h>

/**
  This is automatically defined when building a static library, but when
  including QtHandlebars sources directly into a project,
  QTHANDLEBARS_STATIC should be defined explicitly to avoid possible troubles
  with unnecessary importing/exporting.
  */
#ifdef QTHANDLEBARS_STATIC
	#define QTHANDLEBARSSHARED_EXPORT
#else
	#if defined(QTHANDLEBARS_LIBRARY)
	#  define QTHANDLEBARSSHARED_EXPORT Q_DECL_EXPORT
	#else
	#  define QTHANDLEBARSSHARED_EXPORT Q_DECL_IMPORT
	#endif
#endif

#endif // QTHANDLEBARS_GLOBAL_H
