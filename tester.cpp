
#include "tester.h"

void Tester::execute() {
    Operation* solver = Operation::buildFromEquation("1+9");
    float result = solver->operate();
    cout << result << endl;
}

