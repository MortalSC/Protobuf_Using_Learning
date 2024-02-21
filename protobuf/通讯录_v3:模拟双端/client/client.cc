#include <iostream>
#include <fstream>
#include "contacts.pb.h"
using namespace std;
using namespace c_contacts;
using namespace google::protobuf;

/**
 * 打印联系⼈列表
 */
void PrintfContacts(const Contacts &contacts)
{
    for (int i = 0; i < contacts.contacts_size(); ++i)
    {
        const PeopleInfo &people = contacts.contacts(i);
        cout << "------------联系⼈" << i + 1 << "------------" << endl;
        cout << "姓名：" << people.name() << endl;
        cout << "年龄：" << people.age() << endl;
        int j = 1;
        for (const PeopleInfo_Phone &phone : people.phone())
        {
            cout << "电话" << j++ << ": " << phone.number() << endl;
        }
        const Reflection *reflection = PeopleInfo::GetReflection();
        const UnknownFieldSet &unknowSet = reflection->GetUnknownFields(people);
        for (int j = 0; j < unknowSet.field_count(); j++)
        {
            const UnknownField &unknow_field = unknowSet.field(j);
            cout << "未知字段" << j + 1 << ":"
                 << " 字段编号: " << unknow_field.number()
                 << " 类型: " << unknow_field.type();
            switch (unknow_field.type())
            {
            case UnknownField::Type::TYPE_VARINT:
                cout << " 值: " << unknow_field.varint() << endl;
                break;
            case UnknownField::Type::TYPE_LENGTH_DELIMITED:
                cout << " 值: " << unknow_field.length_delimited() << endl;
                break;
            }
        }
    }
}
int main(int argc, char *argv[])
{

    GOOGLE_PROTOBUF_VERIFY_VERSION;
    if (argc != 2)
    {
        cerr << "Usage: " << argv[0] << "CONTACTS_FILE" << endl;
        return -1;
    }
    // 以⼆进制⽅式读取 contacts
    Contacts contacts;

    string path = "../";
    path += argv[1];
    fstream input(path.c_str(), ios::in | ios::binary);
    if (!contacts.ParseFromIstream(&input))
    {
        cerr << "Failed to parse contacts." << endl;
        input.close();
        return -1;
    }

    // 打印 contacts
    PrintfContacts(contacts);
    input.close();
    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}