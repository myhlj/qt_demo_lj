#ifndef COMMON_DATA_H
#define COMMON_DATA_H


#define   STATUSSUCCED			 0
#define   STATUSJSONERROR        -1 //json解析错误
#define   STATUSSOCKETERROR      -2 //网络错误
#define   STATUSCARDNOERROR      -3 //身份证号码错误


#define  GATEONE   1 //通道一
#define  GATETWO   2 //2
#define  GATEBOTH  3 //双通道

enum returnResult{
    bingo = 1,
    notMatch,
    notCompare
};


struct IDCardTextInfo
{
    IDCardTextInfo()
    {
        memset(name,0,sizeof(name));
        memset(gender,0,sizeof(gender));
        memset(folk,0,sizeof(folk));
        memset(birthday,0,sizeof(birthday));
        memset(code,0,sizeof(code));
        memset(address,0,sizeof(address));
        memset(agency,0,sizeof(agency));
        memset(expireStart,0,sizeof(expireStart));
        memset(expireEnd,0,sizeof(expireEnd));
    }
    ~IDCardTextInfo()
    {

    }
    IDCardTextInfo(const IDCardTextInfo & idinfo )
    {
        memcpy(name,idinfo.name, strlen(idinfo.name)+1 );
        memcpy(gender,idinfo.gender, strlen(idinfo.gender)+1 );
        memcpy(folk,idinfo.folk, strlen(idinfo.folk)+1 );
        memcpy(birthday,idinfo.birthday, strlen(idinfo.birthday)+1 );
        memcpy(code,idinfo.code, strlen(idinfo.code)+1 );
        memcpy(address,idinfo.address, strlen(idinfo.address)+1 );
        memcpy(agency,idinfo.agency, strlen(idinfo.agency)+1 );
        memcpy(expireStart,idinfo.expireStart, strlen(idinfo.expireStart)+1 );
        memcpy(expireEnd,idinfo.expireEnd, strlen(idinfo.expireEnd)+1 );

    }

    IDCardTextInfo& operator=(const IDCardTextInfo& idinfo)
    {
        if(this == &idinfo)
        {
            return *this;
        }

        memcpy(name,idinfo.name, strlen(idinfo.name)+1 );
        memcpy(gender,idinfo.gender, strlen(idinfo.gender)+1 );
        memcpy(folk,idinfo.folk, strlen(idinfo.folk)+1 );
        memcpy(birthday,idinfo.birthday, strlen(idinfo.birthday)+1 );
        memcpy(code,idinfo.code, strlen(idinfo.code)+1 );
        memcpy(address,idinfo.address, strlen(idinfo.address)+1 );
        memcpy(agency,idinfo.agency, strlen(idinfo.agency)+1 );
        memcpy(expireStart,idinfo.expireStart, strlen(idinfo.expireStart)+1 );
        memcpy(expireEnd,idinfo.expireEnd, strlen(idinfo.expireEnd)+1 );
        return *this;
    }
    char name[60 + 1];
    char gender[4 + 1];
    char folk[18 + 1];
    char birthday[16 + 1];
    char code[36 + 1];
    char address[140 + 1];
    char agency[140 + 1];
    char expireStart[16 + 1];
    char expireEnd[16 + 1];
};




struct FingerFeat
{

    FingerFeat()
    {
        exist= false;
    }
    ~FingerFeat()
    {

    }

    FingerFeat(const FingerFeat & fpfeat)
    {
        exist=fpfeat.exist;
        memcpy(finger1, fpfeat.finger1, 512);
        memcpy(finger2, fpfeat.finger2, 512);
    }
#if 0
    FingerFeat & FingerFeat::operator = (const &FingerFeat &fpfeat)
    {
        exist =fpfeat.exist;
        memcpy(finger1,fpfeat.finger1,512);
        memcpy(finger2,fpfeat.finger2,512);
        return *this;
    }
#endif

    bool exist;
    unsigned char finger1[512];
    unsigned char finger2[512];
};

struct IDCardInfo
{
    IDCardInfo()
    {
        memset(&textInfo, 0, sizeof(IDCardTextInfo));
        photo = nullptr;
        photoLength = 0;
    }
    ~IDCardInfo()
    {
        if(photo != 0)
        {
            delete [] photo;
            photo = 0;
        }
    }
    IDCardInfo(const IDCardInfo & info)
    {
        textInfo = info.textInfo;
        fingerFeat.exist = info.fingerFeat.exist;
        memcpy(fingerFeat.finger1, info.fingerFeat.finger1, 512);
        memcpy(fingerFeat.finger2, info.fingerFeat.finger2, 512);

        photo = new unsigned char[info.photoLength];
        photoLength = info.photoLength;
        memcpy(photo, info.photo,info.photoLength);
    }
    IDCardInfo& operator=(const IDCardInfo& info){
        if(this == &info){
            return *this;
        }
        textInfo = info.textInfo;
        fingerFeat.exist = info.fingerFeat.exist;
        memcpy(fingerFeat.finger1, info.fingerFeat.finger1, 512);
        memcpy(fingerFeat.finger2, info.fingerFeat.finger2, 512);
        if(photoLength < info.photoLength){
            delete [] photo;
            photo = new unsigned char[info.photoLength];
        }
        memcpy(photo,info.photo,info.photoLength);
        photoLength = info.photoLength;
        return *this;
    }

    IDCardTextInfo  textInfo;
    FingerFeat fingerFeat;
    unsigned char * photo;
    long photoLength;
};

#endif
