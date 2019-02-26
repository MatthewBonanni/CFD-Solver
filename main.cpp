#include "dsys.h"

int main(){
    dsys sys1 (0.1, 0, 0);
    sys1.fill_tvec(10);
    sys1.march_ab();
    sys1.printtraj();
    sys1.export_data("data.csv");
}