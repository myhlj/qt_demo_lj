#ifndef PRODUCEPOPULATIONJSON_H
#define PRODUCEPOPULATIONJSON_H
#include <QByteArray>
#include <string>
#include "common_data.h"

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
using namespace std;


class ProducePopulationJson
{
public:
    ProducePopulationJson();
    static QByteArray get_population_json(string cardno);
    int analy_request_json(const QByteArray& json,IDCardInfo& card_info,string descrip);
private:
    string getgender(string gendercode);
    string getnation(string nationcode);
};

#endif // PRODUCEPOPULATIONJSON_H
