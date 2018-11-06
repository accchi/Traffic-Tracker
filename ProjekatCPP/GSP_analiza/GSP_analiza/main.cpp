#include "Network.h"
#include "Generator.h"
#include <iostream>
using namespace std;










void main() {

	Network n;
	//n.loadLines("_lines.txt");
	//cout << n;
	/*for (auto& a : n.lines.front()->linesWithCommonStops()) {
		cout << *a;
	}*/
	/*if (n.getLine("26"))
		cout << "IMA"<<endl;
	else
		cout << "NEMA";*/
	//n.deleteLine("26");
	/*n.getLine("26")->setLineNumb("0");
	if (n.getLine("26"))
		cout << "IMA";
	else
		cout << "NEMA"<<endl;
	if (n.getLine("0"))
		cout << "IMA" << endl;
	else
		cout << "NEMA"; */

	/*n.getLine("26")->addNewStop();
	n.getLine("26")->addNewStop();
	cout<<*(n.getLine("26"));*/
	//n.getLine("26")->deleteStop();
	//cout << *(n.getLine("26")); 
	//cout << n.getLine("EKO1")->getZoneMax();
	//n.filterLinesZone();
	//n.filterLinesStop();
	//n.filterLines();
	//cout << n;
	//n.filterLines();
	//cout << n;
	//cout<<*(n.closestStop(44.810416,20.474482));

	//cout << *(n.getLine("65")->mostCommonStops());
	
//	for (auto& i : Direction::getStop(67)->oneDriveStops())
	//	cout << *i << endl;
	//n.generate();
	//n.getGenerator()->generateFiles();
	/*for (auto& it : n.pairsOfLinesWithCommonStops()) {
		cout << *(it.first.first)<< *(it.first.second) << " broj zajednickih: " << it.second << endl;
	}*/
	int option;
	srand(time(0));
	do {
		cout << "[1] Ucitaj celu mrezu\n[2] Ucitaj odredjene linije\n[3] Ispisi mrezu\n[4] Obrisi stajaliste\n[5] Dodaj stajaliste\n"
			<< "[6] Promeni oznaku linije\n[7] Obrisi Liniju\n[8] Filtriraj linije\n[9] Generisi graf\n[10] Kreiraj izlazni fajl\n[11] Dodatne manipulacije\n[12] Exit\n";
		cin >> option;
		system("cls");
		Stop* s;
		string str,str1;
		int int1, int2,int3;
		double dbl1, dbl2;
		switch (option) {
		case 1: 
			try {
				n.loadLines("_lines.txt");  break; // LOAD ALL LINES
			}
			catch (FileException& f) {
				cout << f;
				system("pause");
				system("cls");
			}
		case 2: 
			try {
				n.loadCoupleLines("_lines.txt"); break; // LOAD COUPLE LINES
			}
			catch (FileException& f) {
				cout << f;
				system("pause");
				system("cls");
			}
		case 3: 
			cout << n; break; // OUTPUT NETWORK
		case 4:
			cout << "Unesite oznaku linije cije stajaliste zelite da uklonite?\n"; cin >> str;
			n.getLine(str)->deleteStop(); break; // DELETING STOP
		case 5:
			cout << "Unesite oznaku linije kojoj zelite da dodate stajaliste?\n"; cin >> str;
			n.getLine(str)->addNewStop(); break; // ADDING NEW STOP
		case 6:
			cout << "Unesite oznaku linije kojoj zelite da promenite oznaku?\n"; cin >> str;
			cout << "Unesite novu oznaku?\n";	cin >> str1;
			n.changeLineNumb(str, str1); // CHANGING LINE NUMB
			break; 
		case 7:
			cout << "Unesite oznaku linije koju zelite da obrisete?\n"; cin >> str;
			if (n.deleteLine(str))
				cout << "Linija " << str << " uspesno obrisana\n";
			else
				cout << "Brisanje linije neuspesno\n";
			break; // LINE DELETION
		case 8:
			n.filterLines(); break; // FILTERING LINES
		case 9:
			n.generate(); break; // GENERATING GRAPH
		case 10:
			n.getGenerator()->generateFiles(); break; // MAKING OUTPUT FILES
		case 11: // MORE FEATURES!!!
			system("cls");
			cout << "[1] Linije sa kojima zadata linija ima zajednicka stajalista\n[2] Da li data linija prolazi kroz 2 zadata stajalista\n"
				<< "[3] Odredi liniju sa kojom zadata linija ima najvise zajednickih stajalista\n[4] Odredjivanje najblizeg stajalista prema zadatoj lokaciji\n"
				<< "[5] Odredjivanje broja zajednickih stajalista za sve parove linija koje imaju zajednicko stajaliste\n"
				<< "[6] Odredjivanje svih linija koje prolaze kroz zadato stajaliste\n[7] Odredjivanje svih stajalista do kojih je moguce stici iz zadatog vozeci se 1 stanicu\n"
				<< "[8] Odredjivanje najmanjeg potrebnog broja presedanja izmedju 2 stajalista\n"<<"[9] Odredjivanje najkraceg puta izmedju 2 stajalista\n[10] Povratak u meni\n";
			cin >> option;
			system("cls");
			switch (option) {
			case 1: { // LINE WITH MOST COMMON STOPS
				cout << "Unesite oznaku linije za koju trazite linije sa zajednickim stajalistem?\n"; cin >> str1;
				for (auto& it : n.getLine(str1)->linesWithCommonStops())
					cout << *it;
				break;
			}
			case 2: { // CHECK DOES LINE PASS 2 GIVEN STOPS
				cout << "Unesite oznaku linije za koju zelite da proverite da li prolazi kroz zadata stajalista?\n"; cin >> str;
				cout << "Unesite sifru prvog stajalista?\n"; cin >> int1;
				cout << "Unesite sifru drugog stajalista?\n"; cin >> int2;
				if (n.getLine(str)->passingTwoStops(int1, int2))
					cout << "Prolazi!\n";
				else
					cout << "Ne prolazi!\n";
				break;
			}
			case 3: { // FINDING LINE WITH MOST COMMON STOPS WITH GIVEN LINE
				cout << "Unesite oznaku linije?\n"; cin >> str;
				Line* l = n.getLine(str)->mostCommonStops();
				if (l)
					cout << *l << endl;
				else
					cout << "Linija nema zajendickih stajalista ni sa jednom drugom linijom\n";
				break;
			}
			case 4: {// FINDING CLOSEST STOP- GEO LOCATION
				cout << "Unesite x koordinatu?\n"; cin >> dbl1;
				cout << "Unesite y koordinatu\n"; cin >> dbl2;
				cout << *(n.closestStop(dbl1, dbl2))<<endl; // cout closest stop
				break;
			}
			case 5: { // DODAJ DA MOZE DA UNESE MIN BROJ ZAJEDNICKIH
				cout << "[1] Sve\n[2] Vise od zadatog broja\n";
				cin >> int1;
				switch (int1) {
				case 1:
					for (auto& it : n.pairsOfLinesWithCommonStops())
						cout << *(it.first.first) << *(it.first.second) << " broj zajednickih: " << it.second << endl;
					break;
				case 2:
					cout << "Unesite broj?\n";
					cin >> int2;
					system("cls");
					for (auto& it : n.pairsOfLinesWithCommonStops(int2))
						cout << *(it.first.first) << *(it.first.second) << " broj zajednickih: " << it.second << endl;
					break;

				}
				break;
			}
			case 6: { // ALL LINES THAT PASS GIVEN STOP
				cout << "Unesite sifru stajalista?\n"; cin >> int1;
				s = Direction::getStop(int1);
				if (s) {
					for (auto& it : s->allPassingLines())
						cout << *it;
				}
				else
					cout << "Ne postoji stajaliste sa zadatom siform\n";
				break;
			}
			case 7: {
				cout << "Unesite sifru stajalista?\n"; cin >> int1;
				s = Direction::getStop(int1);
				if (s) {
					for (auto& it : s->oneDriveStops())
						cout << *it<<endl;
				}
				else
					cout << "Ne postoji stajaliste sa zadatom siform\n";
				break;
			}
			case 8: {
				cout << "Unesite sifru pocetnog stajalista?\n"; cin >> int1;
				cout << "Unesite sifru krajnjeg stajalista?\n"; cin >> int2;
				int3 = n.numberOfTransfers(int1, int2);
				if (int3 < 0)
					cout << "Ne postoji put izmedju 2 stajalista\n";
				else
					cout << "Potrebno je " << int3 << " presedanja da se dodje od " << int1 << " do " << int2 << endl;
				break;

			}
			case 9: {
				cout << "Unesite sifru pocetnog stajalista?\n"; cin >> int1;
				cout << "Unesite sifru krajnjeg stajalista?\n"; cin >> int2;
				n.shortestPath(int1, int2);
				break;
			}
			case 10: // RETURN TO MENU
				break;
			}
			break;
		case 12:
			exit(1);
		}
		system("pause");
		system("cls");
		
	}
	while (option != 0);
	system("pause");

}