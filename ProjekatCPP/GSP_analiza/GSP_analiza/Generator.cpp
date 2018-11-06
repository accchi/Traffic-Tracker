#include "Generator.h"
#include "GMLFormat.h"
#include "CSVFormat.h"

void Generator::generateFiles(){
	if (format) delete format; // if format already exist then delete it
	cout << "Koju vrstu formata zelite da ispisete?\n[1] GML Format\n[2] CSV Format\n"; int option;
	cin >> option; // chose type of format
	switch (option) {
	case 1: format = new GMLFormat(); break;
	case 2: format = new CSVFormat(); break;
	}
	format->output(graph); // make output file
	cout << "Izlazni fajl napravljen\n";
}

Generator::~Generator(){
	if (format) delete format;
}
