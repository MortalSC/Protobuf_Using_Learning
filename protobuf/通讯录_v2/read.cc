#include <iostream>
#include <fstream>

#include "contacts2.pb.h"

void OutputContacts(contacts2::Contacts &contacts)
{
    for (int i = 0; i < contacts.people_size(); i++)
    {
        // 通讯录的成员类型：contacts2::PeopleInfo
        // contacts.people：people 是数组名
        const contacts2::PeopleInfo &info = contacts.people(i);
        std::cout << "------------联系⼈" << i + 1 << "------------" << std::endl;
        std::cout << "姓名：" << info.name() << std::endl;
        std::cout << "年龄：" << info.age() << std::endl;
        int j = 1;
        for (const contacts2::PeopleInfo_Phone &phone : info.phone())
        {
            std::cout << "电话" << j++ << ": " << phone.number();
            std::cout << " (" << phone.PhoneType_Name(phone.type()) << ")" << std::endl;
        }

        if (info.has_data() && info.data().Is<contacts2::Address>())
        {
            contacts2::Address addr;
            info.data().UnpackTo(&addr);
            if (!addr.home_addr().empty())
            {
                std::cout << "联系人家庭地址：" << addr.home_addr() << std::endl;
            }
            if (!addr.work_addr().empty())
            {
                std::cout << "联系人工作单位地址：" << addr.work_addr() << std::endl;
            }
        }

        switch (info.other_contact_case())
        {
        case contacts2::PeopleInfo::OtherContactCase::kQq:
            /* code */
            std::cout << "联系人 QQ：" << info.qq() << std::endl;
            break;
        case contacts2::PeopleInfo::OtherContactCase::kWechat:
            std::cout << "联系人 微信：" << info.wechat() << std::endl;
            break;
        default:
            break;
        }

        if (info.remark_size())
        {
            std::cout << "备注信息: ";
        }
        for (auto it = info.remark().cbegin(); it != info.remark().cend();
             ++it)
        {
            std::cout << " " << it->first << ": " << it->second << std::endl;
        }
    }
}

int main()
{
    // 定义通讯录对象
    contacts2::Contacts contacts;

    // 添加本地已存在的联系人
    std::fstream input("contacts.bin", std::ios::in | std::ios::binary);
    if (!input)
    {
        std::cout << "contacts.bin not find, create new file!" << std::endl;
    }
    else if (!contacts.ParseFromIstream(&input))
    {
        // ParseFromIstream：传入指定 istream 对象，即可直接读取其中内容，并进行反序列化
        std::cerr << "parse fail" << std::endl;
        input.close();
        return -1;
    }

    // 打印通讯录数据
    OutputContacts(contacts);

    return 0;
}