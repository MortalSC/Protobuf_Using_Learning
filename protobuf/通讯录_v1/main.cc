#include <iostream>
#include "contacts.pb.h"
#include <string>

/**
 * v1 版本：学会编译 protobuf 以及 基本调用 序列化与反序列化 接口
 */
int main()
{
    std::string str; // 存储序列化字符串

    // 序列化操作
    {
        contacts::PeopleInfo people;
        // 成员 name age
        // 设置成员值得方法：set_成员名();
        people.set_name("张三");
        people.set_age(20);
        // 调用序列化接口：SerializeToXXX：即指定序列化成哪种形式
        if (!people.SerializeToString(&str))
        {
            std::cout << "序列化失败！" << std::endl;
            return -1;
        }
        std::cout << "序列化成功：" << str << std::endl;
    }

    // 反序列化操作
    {
        // 调用反序列化接口
        contacts::PeopleInfo people;
        // 调用序列化接口：ParseFromXXX：即指定反序列化从哪种形式来
        if (!people.ParseFromString(str))
        {
            std::cout << "反序列化失败！" << std::endl;
            return -1;
        }
        std::cout << "序列化成功：" << std::endl;
        std::cout << "姓名：" << people.name() << std::endl;
        std::cout << "年龄：" << people.age() << std::endl;
    }

    return 0;
}