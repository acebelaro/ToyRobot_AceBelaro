#include <iostream>
#include <sstream>
#include "report_command.hpp"

const string ReportCommand::PATTERN = "^\\s*REPORT\\s*$";

void ReportCommand::Execute(Robot& robot, Table& table)
{
    stringstream report;
    string robotReport = robot.Report();
    if( robotReport.compare("") != 0 )
    {
        report << "Output : " << robot.Report();
        cout << report.str() << endl;
    }			
}
