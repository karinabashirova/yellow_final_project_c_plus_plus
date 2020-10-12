#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "test_runner.h"
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

string ParseEvent(istream& is) {
	// Реализуйте эту функцию
	string event;
	is >> ws;
	getline(is, event,'\n');
	return event;

}
void TestAll() {
	TestRunner tr;
	tr.RunTest(TestParseCondition, "TestParseCondition");
	tr.RunTest(TestEmptyNode, "Test 2 from Coursera");
	tr.RunTest(TestDbAdd, "Test 3(1) from Coursera");
	tr.RunTest(TestDbFind, "Test 3(2) from Coursera");
	tr.RunTest(TestDbLast, "Test 3(3) from Coursera");
	tr.RunTest(TestDbRemoveIf, "Test 3(4) from Coursera");
	tr.RunTest(TestInsertionOrder, "Test output order");
	tr.RunTest(TestsMyCustom, "My Test");
	tr.RunTest(TestDatabase, "Test database GitHub");
}
int main() {
	TestAll();

	Database db;

	Date d1(1997, 2, 10), d2(1997, 2, 12);
	for (string line; getline(cin, line); ) {
		istringstream is(line);

		string command;
		is >> command;
		if (command == "Add") {
			const auto date = ParseDate(is);
			const auto event = ParseEvent(is);
			db.Add(date, event);
		}
		else if (command == "Print") {
			db.Print(cout);
		}
		else if (command == "Del") {
			auto condition = ParseCondition(is);
			auto predicate = [condition](const Date& date, const string& event) {
				return condition->Evaluate(date, event);
			};
			int count = db.RemoveIf(predicate);
			cout << "Removed " << count << " entries" << endl;
		}
		else if (command == "Find") {
			auto condition = ParseCondition(is);
			auto predicate = [condition](const Date& date, const string& event) {
				return condition->Evaluate(date, event);
			};

			const auto entries = db.FindIf(predicate);
			for (const auto& entry : entries) {
				cout << entry << endl;
			}
			cout << "Found " << entries.size() << " entries" << endl;
		}
		else if (command == "Last") 
		{
			try {
				const auto date = ParseDate(is);
				cout << db.Last(date) << endl;
			}
			catch (invalid_argument&) {
				cout << "No entries" << endl;
			}
		}
		else if (command.empty()) {
			continue;
		}
		else {
			throw logic_error("Unknown command: " + command);
		}
	}

	return 0;
}
