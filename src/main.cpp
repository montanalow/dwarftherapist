/*
Dwarf Therapist
Copyright (c) 2009 Trey Stout (chmod)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

/*! \mainpage Dwarf Therapist
*
* \section intro_sec Introduction
*
* Dwarf Therapist is written in C++ using Qt 4.5.2. It is meant to be used as
* an addon for the game Dwarf Fortress.
*
*/

#include <QtGui>
#include <QxtLogger>
#include "truncatingfilelogger.h"
#include "mainwindow.h"
#include "dfinstance.h"
#include "utils.h"
#include "version.h"

int main(int argc, char *argv[]) {
	// start up the application
	QApplication a(argc, argv);

	QStringList args = a.arguments();
	bool debug_logging = args.indexOf("-debug") != -1;
	bool trace_logging = args.indexOf("-trace") != -1;

	//TODO REMOVE ME
	// debug logging on by default for the early builds...
	debug_logging = true;

	//setup logging
	TruncatingFileLoggerEngine *engine = new TruncatingFileLoggerEngine("log/run.log");
	qxtLog->addLoggerEngine("main", engine);
	QxtLogger::getInstance()->installAsMessageHandler();
	qxtLog->setMinimumLevel(QxtLogger::InfoLevel);
		
	Version v; // current version
	LOG->info("Dwarf Therapist", v.to_string(), "starting normally.");
	if (debug_logging && !trace_logging) {
		qxtLog->setMinimumLevel(QxtLogger::DebugLevel);
		LOG->info("MINIMUM LOG LEVEL SET TO: DEBUG");
	} else if (trace_logging) {
		qxtLog->setMinimumLevel(QxtLogger::TraceLevel);
		LOG->info("MINIMUM LOG LEVEL SET TO: TRACE");
	} else {
		LOG->info("MINIMUM LOG LEVEL SET TO: INFO");
	}

	// translator
	LOGD << "loading translations";
	QTranslator translator;
	translator.load("dwarftherapist_en");
	a.installTranslator(&translator);

	// make and run the main window
    MainWindow w;
    w.show();
    return a.exec();
}
