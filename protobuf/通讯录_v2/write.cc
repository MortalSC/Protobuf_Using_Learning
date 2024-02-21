#include <iostream>
#include <string>
#include <fstream>
#include "contacts2.pb.h"

// 设置通讯录中人员信息
void AddPeopleInfo(contacts2::PeopleInfo *people)
{
    std::cout << "-------------新增联系⼈-------------" << std::endl;
    std::cout << "请输⼊联系⼈姓名: ";
    std::string name;
    std::getline(std::cin, name);
    people->set_name(name);
    std::cout << "请输⼊联系⼈年龄: ";
    int age;
    std::cin >> age;
    people->set_age(age);
    std::cin.ignore(256, '\n');
    for (int i = 1;; i++)
    {
        std::cout << "请输⼊联系⼈电话" << i << "(只输⼊回⻋完成电话新增): ";
        std::string number;
        std::getline(std::cin, number);
        if (number.empty())
        {
            break;
        }
        contacts2::PeopleInfo_Phone *phone = people->add_phone();
        phone->set_number(number);

        std::cout << "选择此电话类型 (1、移动电话 2、固定电话) : ";
        int type;
        std::cin >> type;
        std::cin.ignore(256, '\n');
        switch (type)
        {
        case 1:
            phone->set_type(contacts2::PeopleInfo_Phone_PhoneType::PeopleInfo_Phone_PhoneType_MT);
            break;
        case 2:
            phone->set_type(contacts2::PeopleInfo_Phone_PhoneType::PeopleInfo_Phone_PhoneType_TEL);
            break;
        default:
            std::cout << "⾮法选择，使⽤默认值！" << std::endl;
            break;
        }
    }

    // Any类型的使用方式：先定义地址对象
    contacts2::Address addr;
    std::cout << "请输入联系人的家庭地址信息：";
    std::string home_addr;
    std::getline(std::cin, home_addr);
    addr.set_home_addr(home_addr);
    std::cout << "请输入联系人的单位地址信息：";
    std::string work_addr;
    std::getline(std::cin, work_addr);
    addr.set_home_addr(work_addr);

    // Address => Any
    people->mutable_data()->PackFrom(addr);

    std::cout << "请选择要添加的其他联系方式（1.QQ；2.wechat）:";
    int other_contact;
    std::cin >> other_contact;
    std::cin.ignore(256, '\n');
    if (1 == other_contact)
    {
        std::cout << "请输⼊qq号: ";
        std::string qq;
        std::getline(std::cin, qq);
        people->set_qq(qq);
    }
    else if (2 == other_contact)
    {
        std::cout << "请输⼊微信号: ";
        std::string wechat;
        std::getline(std::cin, wechat);
        people->set_wechat(wechat);
    }
    else
    {
        std::cout << "⾮法选择，该项设置失败！" << std::endl;
    }

    std::cout << "-----------添加联系⼈成功-----------" << std::endl;
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

    // 向通讯录中添加数据
    // 通讯录就是一个数组形式
    AddPeopleInfo(contacts.add_people());

    // 将序列化数据写入文件
    std::fstream output("contacts.bin", std::ios::out | std::ios::trunc | std::ios::binary);
    if (!contacts.SerializePartialToOstream(&output))
    {
        std::cerr << "write fail" << std::endl;
        input.close();
        output.close();
        return -1;
    }

    std::cout << "write success" << std::endl;
    input.close();
    output.close();

    return 0;
}