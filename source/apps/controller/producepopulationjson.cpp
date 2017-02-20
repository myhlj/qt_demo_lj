#include <QJsonobject.h>
#include <QJsonDocument>
#include "producepopulationjson.h"

#define KEYSTATUS       "status"
#define KEYMESSAGE      "message"
#define KEYPERSONINFO   "personInfo"
#define KEYPERSONNAME   "personName"
#define KEYCARDNO       "cardNo"
#define KEYGENDERCODE   "genderCode"
#define KEYNATIONCODE   "nationCode"
#define KEYADDR         "addr"
#define KEYPHOTO        "photo"

ProducePopulationJson::ProducePopulationJson()
{

}

QByteArray ProducePopulationJson::get_population_json(string cardno)
{
    QJsonObject json_obj;
    json_obj["method"] = "queryPersonInfo";
    json_obj["cardNo"] = QString::fromStdString(cardno);
    json_obj["invokeKey"] = "F05949BEEA3BCE3F211ACA5569D3F6D3";


    QJsonDocument json_doc(json_obj);
    return json_doc.toJson(QJsonDocument::Compact);
}

int ProducePopulationJson::analy_request_json(const QByteArray &json,
                                              IDCardInfo& card_info,
                                              string descrip)
{
    QJsonDocument json_doc(QJsonDocument::fromJson(json));
    QJsonObject obj = json_doc.object();
    if(obj.isEmpty()){
        return STATUSJSONERROR;
    }
    QString status,descript,personname,cardno,gendercode,
            nationcode,addr,photo;
    if(obj.contains(KEYSTATUS)){
        if(obj[KEYSTATUS].isString()){
            status = obj[KEYSTATUS].toString();
        }
    }
    if(obj.contains(KEYMESSAGE)){
        if(obj[KEYMESSAGE].isString()){
            descript = obj[KEYMESSAGE].toString();
        }
    }
    if(status.toInt() != STATUSSUCCED){
        return status.toInt();
    }
    QJsonObject personobj;
    if(obj.contains(KEYPERSONINFO)){
        if(obj[KEYPERSONINFO].isObject()){
            personobj = obj[KEYPERSONINFO].toObject();
        }else{
            return STATUSJSONERROR;
        }
    }else{
        return STATUSJSONERROR;
    }
    if(personobj.contains(KEYPERSONNAME)){
        if(personobj[KEYPERSONNAME].isString()){
            personname = personobj[KEYPERSONNAME].toString();
        }
    }
    if(personobj.contains(KEYCARDNO)){
        if(personobj[KEYCARDNO].isString()){
            cardno = personobj[KEYCARDNO].toString();
        }
    }
    if(personobj.contains(KEYGENDERCODE)){
        if(personobj[KEYGENDERCODE].isString()){
            gendercode = personobj[KEYGENDERCODE].toString();
        }
    }
    if(personobj.contains(KEYNATIONCODE)){
        if(personobj[KEYNATIONCODE].isString()){
            nationcode = personobj[KEYNATIONCODE].toString();
        }
    }
    if(personobj.contains(KEYADDR)){
        if(personobj[KEYADDR].isString()){
            addr = personobj[KEYADDR].toString();
        }
    }
    if(personobj.contains(KEYPHOTO)){
        if(personobj[KEYPHOTO].isString()){
            photo = personobj[KEYPHOTO].toString();
        }
    }

    strcpy(card_info.textInfo.name,personname.toStdString().c_str());
    strcpy(card_info.textInfo.address,addr.toStdString().c_str());
    strcpy(card_info.textInfo.gender,getgender(gendercode.toStdString()).c_str());
    strcpy(card_info.textInfo.folk,getnation(nationcode.toStdString()).c_str());
    strcpy(card_info.textInfo.code,cardno.toStdString().c_str());

    QByteArray ba;
    ba.append(photo);
    ba = QByteArray::fromBase64(ba);
    card_info.photoLength = ba.length();
    card_info.photo = new unsigned char[card_info.photoLength];
    memcpy(card_info.photo,ba.data(),card_info.photoLength);
    descrip = descript.toStdString();
    return STATUSSUCCED;
}

string ProducePopulationJson::getgender(string gendercode)
{
    int n = atoi(gendercode.c_str());
    if(n == 1){
        return "男";
    }else{
        return "女";
    }
}

string ProducePopulationJson::getnation(string nationcode)
{
    int code = atoi(nationcode.c_str());
    string nation_desc;
    switch (code){
        case 1:  nation_desc = "汉"; break;
        case 2:  nation_desc = "蒙古"; break;
        case 3:  nation_desc = "回"; break;
        case 4:  nation_desc = "藏"; break;
        case 5:  nation_desc = "维吾尔"; break;
        case 6:  nation_desc = "苗"; break;
        case 7:  nation_desc = "彝"; break;
        case 8:  nation_desc = "壮"; break;
        case 9:  nation_desc = "布依"; break;
        case 10:  nation_desc = "朝鲜"; break;
        case 11:  nation_desc = "满"; break;
        case 12:  nation_desc = "侗"; break;
        case 13:  nation_desc = "瑶"; break;
        case 14:  nation_desc = "白"; break;
        case 15:  nation_desc = "土家"; break;
        case 16:  nation_desc = "哈尼"; break;
        case 17:  nation_desc = "哈萨克"; break;
        case 18:  nation_desc = "傣"; break;
        case 19:  nation_desc = "黎"; break;
        case 20:  nation_desc = "傈僳"; break;
        case 21:  nation_desc = "佤"; break;
        case 22:  nation_desc = "畲"; break;
        case 23:  nation_desc = "高山"; break;
        case 24:  nation_desc = "拉祜"; break;
        case 25:  nation_desc = "水"; break;
        case 26:  nation_desc = "东乡"; break;
        case 27:  nation_desc = "纳西"; break;
        case 28:  nation_desc = "景颇"; break;
        case 29:  nation_desc = "柯尔克孜"; break;
        case 30:  nation_desc = "土"; break;
        case 31:  nation_desc = "达斡尔"; break;
        case 32:  nation_desc = "仫佬"; break;
        case 33:  nation_desc = "羌"; break;
        case 34:  nation_desc = "布朗"; break;
        case 35:  nation_desc = "撒拉"; break;
        case 36:  nation_desc = "毛南"; break;
        case 37:  nation_desc = "仡佬"; break;
        case 38:  nation_desc = "锡伯"; break;
        case 39:  nation_desc = "阿昌"; break;
        case 40:  nation_desc = "普米"; break;
        case 41:  nation_desc = "塔吉克"; break;
        case 42:  nation_desc = "怒"; break;
        case 43:  nation_desc = "乌孜别克"; break;
        case 44:  nation_desc = "俄罗斯"; break;
        case 45:  nation_desc = "鄂温克"; break;
        case 46:  nation_desc = "德昂"; break;
        case 47:  nation_desc = "保安"; break;
        case 48:  nation_desc = "裕固"; break;
        case 49:  nation_desc = "京"; break;
        case 50:  nation_desc = "塔塔尔"; break;
        case 51:  nation_desc = "独龙"; break;
        case 52:  nation_desc = "鄂伦春"; break;
        case 53:  nation_desc = "赫哲"; break;
        case 54:  nation_desc = "门巴"; break;
        case 55:  nation_desc = "珞巴"; break;
        case 56:  nation_desc = "基诺"; break;
        case 97:  nation_desc = "其他"; break;
        case 98:  nation_desc = "外国"; break;
        default:  nation_desc = "";
    }
    return nation_desc;
}
