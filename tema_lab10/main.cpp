#include <iostream>
#include "ui.h"
#include "gui.h"
#include <QtWidgets/QApplication>
#include <cstring>
#include <cstdio>
#include "Windows.h"

#define CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include "tests.h"
#include "repository.h"
#include "servicecos.h"
#include "produs.h"


int main(int argc, char *argv[])
{
	
	
	
	test_all();

	repository<produs> repo;
	cos_cumparaturi c{ repo };
	service_cos srv_cos{ c };
	service serv{ repo, srv_cos};


	// dorim sa lucram din consola
	if (argc == 2 && (strcmp(argv[1], "--console") || strcmp(argv[1], "-c")))
	{
		FreeConsole();
		AllocConsole();
		AttachConsole(GetCurrentProcessId());
		freopen("CON", "w", stdout);
		freopen("CON", "w", stderr);
		freopen("CON", "r", stdin);

		ui thisUi{ serv, srv_cos };
		thisUi.ruleaza();
	}

	// dorim GUI
	else if (argc == 1)
	{
		// eu am ecran mic cu rezolutie mare la laptop, iar daca nu folosesc functia asta, butoanele sunt foarte mici
		QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
		QApplication a(argc, argv);
		tema_lab10 w{ serv, srv_cos };

		w.setWindowTitle("Magazin");
		w.show();

		return a.exec();
	}

	return 0;
}
