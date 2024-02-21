# Protobuf



## 序列化认识

### 序列化与反序列化

> 序列化：将对象转为字节（二进制）序列的过程，称为对象的序列化。
>
> 反序列化：把字节（二进制）序列恢复为对象的过程，称为对象的反序列化。



### 使用情景

> 存储数据：数据存储到文件或数据库中。
>
> 网络传输：⽹络直接传输数据，但是⽆法直接传输对象，所以要在传输前序列化，传输完成后反序列化成对象。
>
> - 例如 socket 编程中发送与接收数据。



### 序列化方式

> xml、json、 protobuf



---



## Protobuf 的基本认识【安装】

### protobuf 特点

> **语⾔⽆关、平台⽆关**：即 ProtoBuf ⽀持 Java、C++、Python 等多种语⾔，⽀持多个平台。
>
> **⾼效**：即⽐ XML 更⼩、更快、更为简单。
>
> **扩展性、兼容性好**：你可以更新数据结构，⽽不影响和破坏原有的旧程序。



### 使用特点

> Protobuf 是需要依赖通过编译生成的头文件和源文件来使用的。
>
> ---
>
> 使用步骤：
>
> - 编写 .proto ⽂件，⽬的是为了定义结构对象（message）及属性内容。
> - 使⽤ protoc 编译器编译 .proto ⽂件，⽣成⼀系列接⼝代码，存放在新⽣成头⽂件和源⽂件中。
> - 依赖⽣成的接⼝，将编译⽣成的头⽂件包含进我们的代码中，实现对 .proto ⽂件中定义的字段进⾏设置和获取，和对 message 对象进⾏序列化和反序列化。
>
> ---
>
> 使用认识：
>
> - 在 proto 文件中，定义结构对象 message，写好基本的属性（就是C++对象中的属性）
> - 然后使用编译器，可以直接一键生成操作获取数据的方法和序列化与反序列化方法。



### 安装 for Win

> 下载链接：https://github.com/protocolbuffers/protobuf/releases
>
> ---
>
> 下载之后将压缩包解压到本地⽬录下。解压后的⽂件内包含 bin、include⽂件，以及⼀个readme.txt。
>
> 进入bin目录，复制路径配置到环境变量中。





### 安装 for Linux

#### 依赖库的安装

~~~c++
// 下载 ProtoBuf 前⼀定要安装依赖库：autoconf automake libtool curl make g++ unzip

// 如未安装，安装命令如下：
// Ubuntu ⽤⼾选择：
sudo apt-get install autoconf automake libtool curl make g++ unzip -y

// CentOS ⽤⼾选择：
sudo yum install autoconf automake libtool curl make gcc-c++ unzip
~~~



#### protobuf 的安装

~~~c++
// ProtoBuf 下载地址：
https://github.com/protocolbuffers/protobuf/releases

// 可以直接选择 protobuf-all-xxx（版本号）.zip

// 复制指定版本的下载连接
使用 wget + 链接下载

// 下载完成后，解压zip包：
unzip protobuf-all-21.11.zip
    
// 解压完成后，会⽣成 protobuf-21.11 ⽂件，进⼊⽂件：
cd protobuf-21.11
    
// 第⼀步执⾏autogen.sh，但如果下载的是具体的某⼀⻔语⾔，不需要执⾏这⼀步。
./autogen.sh 
 
// 第⼆步执⾏configure，有两种执⾏⽅式，任选其⼀即可，如下：
// 1、protobuf默认安装在 /usr/local ⽬录，lib、bin都是分散的
./configure 
// 2、修改安装⽬录，统⼀安装在/usr/local/protobuf下【推荐】
./configure --prefix=/usr/local/protobuf

// 再依次执行
make // 执⾏15分钟左右
make check // 执⾏15分钟左右
// 执⾏ make check 后 ，出现以下内容就可以执⾏ sudo make install 。【如图】
sudo make install
~~~





## Protobuf 的简单使用

### 基本认识

> protobuf 文件中：
>
> - 注释方式与C/C++相同



### .proto 文件的编写认识

~~~c++
// 以下是编写格式（要求）

/* ============================================ */

// 首行：语法指定行：指定使用的语法版本
syntax = "proto3";

// package 声明符
// package 是⼀个可选的声明符，能表⽰ .proto ⽂件的命名空间，在项⽬中要有唯⼀性。它的作⽤是为了避免我们定义的消息出现冲突。
// 使用方式：package + name;	// 与C++不同，不需要 {}

// 定义联系人 message
// 属性定义方式：
// 类型 属性名 = 字段编号;
// 字段编号与编译有关，是高效的实现底层之一
message PeopleInfo{
    string name = 1;
    int32 = 2;
}
~~~



### .proto 编译方式

~~~c++
// 指令
// 指令 protoc
// --cpp_out：输出 C++ 版本
// = 后跟目录；[.]表示当前目录
protoc --cpp_out=. 指定.proto
    
// 编译输出到指定目录
// -I 指定搜索的起始目录名
protoc -I 目录名 [目录名] --cpp_out=指定目录

// 生成的文件
protobuf文件名.pb.h
protobuf文件名.pb.cc
~~~







### 定义消息字段【类型】

> **在 message 中我们可以定义其属性字段，字段定义格式为：字段类型 字段名 = 字段唯⼀编号；**
>
> - **字段名称命名规范：全⼩写字⺟，多个字⺟之间⽤ _ 连接。**
> - **字段类型分为：标量数据类型 和 特殊类型**（包括枚举、其他消息类型等）。
> - **字段唯⼀编号：⽤来标识字段，⼀旦开始使⽤就不能够再改变。**
>
> ---
>
> **字段唯⼀编号的范围：**
>
> - 1 ~ 536,870,911 (2^29 - 1) ，其中 19000 ~ 19999 不可⽤。
> - **19000 ~ 19999 不可⽤**是因为：在 Protobuf 协议的实现中，对这些数进⾏了预留。如果⾮要在.proto ⽂件中使⽤这些预留标识号，例如将 name 字段的编号设置为19000，编译时就会报警
> - 范围为 1 ~ 15 的字段编号需要⼀个字节进⾏编码， 16 ~ 2047 内的数字需要两个字节
>   进⾏编码。编码后的字节不仅只包含了编号，还包含了字段类型。所以 **1 ~ 15 要⽤来标记出现⾮常频繁的字段，要为将来有可能添加的、频繁出现的字段预留⼀些出来。**
>
> ---
>
> **类型说明与对照表**
>
> - 该表格展⽰了定义于消息体中的标量数据类型，以及编译 .proto ⽂件之后⾃动⽣成的类中与之对应的字段类型。在这⾥展⽰了与 C++ 语⾔对应的类型。
> - [1] 变⻓编码是指：经过protobuf 编码后，原本4字节或8字节的数可能会被变为其他字节数。

| .proto type | Notes                                                        | C++ type |
| ----------- | ------------------------------------------------------------ | -------- |
| double      |                                                              | double   |
| float       |                                                              | float    |
| int32       | 使⽤变⻓编码[1]。负数的编码效率较低⸺若字段可能为负值，应使⽤ sint32 代替。 | int32    |
| int64       | 使⽤变⻓编码[1]。负数的编码效率较低⸺若字段可能为负值，应使⽤ sint64 代替。 | int64    |
| uint32      | 使⽤变⻓编码[1]。                                            | uint32   |
| uint64      | 使⽤变⻓编码[1]。                                            | uint64   |
| sint32      | 使⽤变⻓编码[1]。符号整型。负值的编码效率⾼于常规的 int32 类型。 | int32    |
| sint64      | 使⽤变⻓编码[1]。符号整型。负值的编码效率⾼于常规的 int64 类型。 | sint64   |
| fixed32     | 定⻓ 4 字节。若值常⼤于2^28 则会⽐ uint32 更⾼效。           | uint32   |
| fixed64     | 定⻓ 8 字节。若值常⼤于2^56 则会⽐ uint64 更⾼效。           | uint64   |
| sfixed32    | 定⻓ 4 字节。                                                | int32    |
| sfixed64    | 定⻓ 8 字节。                                                | int64    |
| bool        |                                                              | bool     |
| string      | 包含 UTF-8 和 ASCII 编码的字符串，⻓度不能超过2^32 。        | string   |
| bytes       | 可包含任意的字节序列但⻓度不能超过 2^32 。                   | string   |





### 简单使用示例：通讯录v1【变量】

#### 注意编译说明

~~~c++
g++ -o TestPB main.cc contacts.pb.cc -std=c++11 -lprotobuf

// -lprotobuf：必加，不然会有链接错误。
// -std=c++11：必加，使⽤C++11语法。
~~~



#### .proto 文件内容

~~~c++
// 首行：语法指定行
syntax = "proto3";
package contacts;

// 定义联系人 message
// 属性定义方式：
// 类型 属性名 = 字段编号;
// 字段编号与编译有关，是高效的实现底层之一
message PeopleInfo{
    string name = 1;
    int32 age = 2;
}
~~~





#### 源码示例

> **v1 版本：学会编译 protobuf 以及 基本调用 序列化与反序列化 接口**

~~~c++
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
~~~





## Protobuf proto3 语法

### 字段规则

#### repeated

> **repeated ：消息中可以包含该字段任意多次（包括零次），其中重复值的顺序会被保留。可以理解为定义了⼀个数组。**

#### singular

> **singular ：消息中可以包含该字段零次或⼀次（不超过⼀次）。 proto3 语法中，字段默认使⽤该规则。**



### message 的使用方式【三种】

> **三种情形：**
>
> - **同文件内多个 message**
> - **message 嵌套使用**
> - **类型在其他 .proto 文件【使用import引入】**

~~~c++
syntax = "proto3";
package contacts2;

// 引入其他文件中的 message
import "phone.proto";

// 类似C++的类封装：电话号码类
// message 支持嵌套
// message Phone{
//     string number = 1;
// }

message PeopleInfo{
    string name = 1;
    int32 age = 2;

    // 使用数组存储电话号码：一个人可能多个

    // 写法一：同文件内多个 message
    // repeated string phone_numbers = 3;

    // 写法二：message 嵌套使用
    // message Phone{
    //     string number = 1;
    // }
    // repeated Phone phone = 3;

    // 写法三：情形：类型在其他 .proto 文件
    // import "phone.proto";【前面引入：文件信息】
    repeated phone.Phone phone = 3;
}
~~~













### 简单使用示例：通讯录v2【文件】

> 版本说明：
>
> - 不再打印联系⼈的序列化结果，⽽是将通讯录序列化后并写⼊⽂件中。
> - 从⽂件中将通讯录解析出来，并进⾏打印。
> - 新增联系⼈属性，共包括：姓名、年龄、电话信息、地址、其他联系⽅式、备注。



#### .proto 文件

~~~c++
syntax = "proto3";
package contacts2;

// 引入其他文件中的 message
import "phone.proto";

// 类似C++的类封装：电话号码类
// message 支持嵌套
// message Phone{
//     string number = 1;
// }

message PeopleInfo{
    string name = 1;
    int32 age = 2;

    // 使用数组存储电话号码：一个人可能多个

    // 写法一：同文件内多个 message
    // repeated string phone_numbers = 3;

    // 写法二：message 嵌套使用
    message Phone{
        string number = 1;
    }
    repeated Phone phone = 3;

    // 写法三：情形：类型在其他 .proto 文件
    // import "phone.proto";【前面引入：文件信息】
    // repeated phone.Phone phone = 3;
}

// 通讯录
message Contacts{
    repeated PeopleInfo people = 1;   
}
~~~



#### 写入文件代码

~~~c++
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
~~~





#### 读取文件代码

~~~c++
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
            std::cout << "电话" << j++ << ": " << phone.number() << std::endl;
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
~~~





### 查看 protobuf 命令选项

> **命令：protoc -h**
>
> - -I / -IPAHT：指定编译的文件放在哪个目录下
> - --decode：指定解析 protobuf 生成的二进制内容

```c++
// --decode 用法
// --decode=package.message xxx.proto 标准输入 / < 文件

[Mortal@iZ0jl35r9ol1wetwfacre1Z 通讯录_v2]$ protoc --decode=contacts2.Contacts contacts2.proto < contacts.bin
people {
  name: "\345\274\240\344\270\211"
  age: 20
  phone {
    number: "1234567890"
  }
  phone {
    number: "7894561230"
  }
  phone {
    number: "4561237890"
  }
}
```





### enum 枚举类型

> 语法⽀持我们定义枚举类型并使⽤。在.proto⽂件中枚举类型的书写规范为：
>
> - 枚举类型名称：使⽤驼峰命名法，⾸字⺟⼤写。 例如： MyEnum
> - 常量值名称：全⼤写字⺟，多个字⺟之间⽤ _ 连接。例如： ENUM_CONST = 0;
>
> ------
>
> **要注意枚举类型的定义有以下⼏种规则：**
>
> 1. **0 值常量必须存在，且要作为第⼀个元素。这是为了与 proto2 的语义兼容：第⼀个元素作为默认值，且值为 0。**
> 2. **枚举类型可以在消息外定义，也可以在消息体内定义（嵌套）。**
> 3. **枚举的常量值在 32 位整数的范围内。但因负值⽆效因⽽不建议使⽤（与编码规则有关）。**
>
> ------
>
> 将两个 ‘具有相同枚举值名称’ 的枚举类型放在单个 .proto ⽂件下测试时，编译后会报错：某某某常
> 量已经被定义！所以这⾥要注意：
> • 同级（同层）的枚举类型，各个枚举类型中的常量不能重名。
> • 单个 .proto ⽂件下，最外层枚举类型和嵌套枚举类型，不算同级。
> • 多个 .proto ⽂件下，若⼀个⽂件引⼊了其他⽂件，且每个⽂件都未声明 package，每个 proto ⽂件中的枚举类型都在最外层，算同级。
> • 多个 .proto ⽂件下，若⼀个⽂件引⼊了其他⽂件，且每个⽂件都声明了 package，不算同级。

```c++
// ---------------------- 情况1：同级枚举类型包含相同枚举值名称--------------------
enum PhoneType {
     MP = 0; // 移动电话
     TEL = 1; // 固定电话
}
enum PhoneTypeCopy {
     MP = 0; // 移动电话 // 编译后报错：MP 已经定义
}

// ---------------------- 情况2：不同级枚举类型包含相同枚举值名称-------------------
enum PhoneTypeCopy {
     MP = 0; // 移动电话 // ⽤法正确
}
message Phone {
     string number = 1; // 电话号码
     enum PhoneType {
     	MP = 0; // 移动电话
     	TEL = 1; // 固定电话
     }
}
// ---------------------- 情况3：多⽂件下都未声明package--------------------
// phone1.proto
import "phone1.proto"
enum PhoneType {
     MP = 0; // 移动电话 // 编译后报错：MP 已经定义
     TEL = 1; // 固定电话
}
// phone2.proto
enum PhoneTypeCopy {
     MP = 0; // 移动电话 
}
// ---------------------- 情况4：多⽂件下都声明了package--------------------
// phone1.proto
import "phone1.proto"
package phone1;
enum PhoneType {
     MP = 0; // 移动电话 // ⽤法正确
     TEL = 1; // 固定电话
}
// phone2.proto
package phone2;
enum PhoneTypeCopy {
     MP = 0; // 移动电话 
}
```



### enum 类型与通讯录v2.1【电话类型】



#### .proto

~~~c++
syntax = "proto3";
package contacts2;

message PeopleInfo{
    string name = 1;
    int32 age = 2;
    message Phone{
        string number = 1;
        enum PhoneType{
            MT = 0;
            TEL = 1;
        }
        PhoneType type = 2;
    }
    repeated Phone phone = 3;
}

// 通讯录
message Contacts{
    repeated PeopleInfo people = 1;   
}
~~~



### Any 类型及其使用：通讯录v2.2【增加地址信息】

> Any类型实际就是 protobuf 提前写好的 message，是一种泛型，说白了就是其中的数据类型可以是任意的。
>
> 使用前必须引入：
>
> - import "google/protobuf/any.proto";
>
> 类型用法：
>
> - google.protubuf.Any 变量名 = x;

#### .proto 文件

~~~c++
syntax = "proto3";
package contacts2;

// 引入 Any 类型
import "google/protobuf/any.proto";

// 定义地址类型
message Address{
    string home_addr = 1;
    string work_addr = 2;
}


// 联系人信息
message PeopleInfo{
    string name = 1;
    int32 age = 2;
    message Phone{
        string number = 1;
        enum PhoneType{
            MT = 0;
            TEL = 1;
        }
        PhoneType type = 2;
    }
    repeated Phone phone = 3;
    google.protubuf.Any data =4;
}

// 通讯录
message Contacts{
    repeated PeopleInfo people = 1;   
}
~~~



#### any 类型的使用方式

> 类型声明方式：
>
> - google.protubuf.Any 变量名 = x;
>
> ---
>
> **实际类型关联方式：**
>
> - 使用 any 后，会生成特定函数接口
> - **PackFrom(xxx::messge&)：将传入的任意消息类型转成 Any 类型！**
> - **UnpackTo(xxx::message*)：将 Any 类型转回给定的类型**
> - Is()：判断是否为指定类型 / 判断 Any 的实际类型是什么





#### Any 类型自动关联的常用方法

~~~c++
mutable_data() => 返回 Any*
// 获取 Any 指针

mutable_data()->PackFrom(被绑定类型) => 返回 bool
// 将 Any 与被包装类型进行绑定

message.has_data(); 
// 用于判断 message 中 Any 声明的 data 属性是否被设定值！
    
message.data();
// 可以用于提取 message 中 Any 声明的 data 的值

message.data().Is<类型>(); => 返回 bool
// 可以用于判断 message 中 Any 声明的 data 类型是否为指定类型

info.data().UnpackTo(被包装类型对象); => 返回 bool
// 用于获取 any 包含的实际被包装类型对象值【输出型参数】

被包装类型对象.属性名().empty();
// 用于判断指定属性是否被设定值！
~~~







### oneof 类型及其使用：通讯录v2.3【增加其他联系方式（多选一）】

#### 类型使用说明！

> **oneof 类型里可以设置多种字段属性！**
>
> - **但是它的实际取值，只能是其中之一！**
> - **且如果同时设置，只认定字段属性中被设定值的最后一个**
>
> 转义成 cpp 后，属性就会被设置在枚举类型中。
>
> ---
>
> 举例说明：
>
> - 比如我们通讯录中可以保留其他联系方式
> - 如：QQ，wechat
> - 如果只能存储其中一种，就可以使用 oneof 包装！
> - 如果QQ，wechat同时被赋值，认定最后被设定的一个，即 wechat！
>
> ---
>
> **注意：oneof 中的字段序号与 oneof 同级声明的其他类型在一个作用域中，即 oneof 中的类型就是常规字段，只不过通过 oneof 限定，只使用多个中的一个。**
>
> **注意：oneof 中不能使用 repeated 关键字**



#### .proto 文件示例

~~~c++
syntax = "proto3";
package contacts2;

// 引入 Any 类型
import "google/protobuf/any.proto";

// 定义地址类型
message Address{
    string home_addr = 1;
    string work_addr = 2;
}


// 联系人信息
message PeopleInfo{
    string name = 1;
    int32 age = 2;
    message Phone{
        string number = 1;
        enum PhoneType{
            MT = 0;
            TEL = 1;
        }
        PhoneType type = 2;
    }
    repeated Phone phone = 3;
    google.protubuf.Any data =4;
    oneof other_contact{
        string qq = 5;
        string wechat = 6;
    }
}

// 通讯录
message Contacts{
    repeated PeopleInfo people = 1;   
}
~~~





#### oneof 类型自动关联的常用方法

~~~c++
has_字段名();
// 用于判断 oneof 中是否有/是否被赋值

clear_字段名();
// 用于清楚对应字段的值

字段名();
// 用于获取指定字段的值

clear_other_contact();
// 用于清理字段：非指定/赋值/最后赋值

other_contact_case();
// 获取当前 oneof 实际关联字段
// 返回 0 标识什么也没设置
// 若有返回字段序号
~~~





### map 类型及其使用：通讯录v2.4【增加备注信息】

#### 类型说明

> 语法⽀持创建⼀个关联映射字段，也就是可以使⽤ map 类型去声明字段类型，格式为：
> map map_field = N;
>
> ---
>
> **注意点：**
>
> - **key_type 是除了 float 和 bytes 类型以外的任意标量类型。 value_type 可以是任意类型**
> - **map 字段不可以⽤ repeated 修饰**
> - **map 中存⼊的元素是⽆序的**



#### .proto 文件

~~~c++
syntax = "proto3";
package contacts2;

// 引入 Any 类型
import "google/protobuf/any.proto";

// 定义地址类型
message Address{
    string home_addr = 1;
    string work_addr = 2;
}


// 联系人信息
message PeopleInfo{
    string name = 1;
    int32 age = 2;
    message Phone{
        string number = 1;
        enum PhoneType{
            MT = 0;
            TEL = 1;
        }
        PhoneType type = 2;
    }
    repeated Phone phone = 3;
    google.protubuf.Any data =4;
    oneof other_contact{
        string qq = 5;
        string wechat = 6;
    }
    map<string, string> remark = 7;
}

// 通讯录
message Contacts{
    repeated PeopleInfo people = 1;   
}
~~~



#### map 类型自动关联的常用方法

~~~c++
字段名_size();
// 获取 map 大小

clear_字段名();
// 清除 map 内容

字段名();
// 返回 map 的引用

mutalbe_字段名();
// 返回 map 的地址

insert({key，value});
// 向 map 中插入数据
~~~





### 默认值

#### 基本说明认识

> 反序列化消息时，如果被反序列化的⼆进制序列中不包含某个字段，反序列化对象中相应字段时，就会设置为该字段的默认值。不同的类型对应的默认值不同：
>
> ---
>
> 

| type                   | 默认值                                         |
| ---------------------- | ---------------------------------------------- |
| 字符串                 | 空字符串                                       |
| 字节                   | 空字节                                         |
| 数值类型               | 0                                              |
| 枚举类型               | 第一个定义的枚举值（必须是0）                  |
| 消息字段               | 未设置该字段。它的取值是依赖于语⾔。           |
| 设置了 repeated 的字段 | 的默认值是空的（ 通常是相应语⾔的⼀个空列表 ） |



#### 特别说明

> 对于 消息字段 、 oneof字段 和 any字段 ，C++ 和 Java 语⾔中都有 has_ ⽅法来检测当前字段是否被设置。
>
> ---
>
> 对于标量数据类型，在 proto3 语法下，没有生成 has_ 方法！
>
> ---
>
> 举例：
>
> - massage 中设定 a，b，c 三个字段
> - 使用中，只对 a，b 赋值，然后序列化
> - 反序列化后，a，b 就是指定值，c 会有默认值。
> - 但是，此时我们没办法确定 c 是被给定的值刚好是默认值，还是没有赋值就序列化了！





### 更新消息【reserved】

#### 认识更新规则

> **更新消息（message）：涉及新增、修改、删除字段！**

#### 更新规则：新增 / 修改

> ---
>
> **规则：**
>
> - **【新增】禁⽌修改任何已有字段的字段编号**
> - **【修改】**int32， uint32， int64， uint64 和 bool 是完全兼容的。可以从这些类型中的⼀个改为另⼀个，⽽不破坏前后兼容性。若解析出来的数值与相应的类型不匹配，会采⽤与 C++ ⼀致的处理⽅案（例如，若将 64 位整数当做 32 位进⾏读取，它将被截断为 32 位）。
> - **【修改】**sint32 和 sint64 相互兼容但不与其他的整型兼容。
> - 【修改】string 和 bytes 在合法 UTF-8 字节前提下也是兼容的。
> - **【修改】**bytes 包含消息编码版本的情况下，嵌套消息与 bytes 也是兼容的。
> - **【修改】**fixed32 与 sfixed32 兼容， fixed64 与 sfixed64兼容。
> - **【修改】**enum 与 int32，uint32， int64 和 uint64 兼容（注意若值不匹配会被截断）。但要注意当反序列化消息时会根据语⾔采⽤不同的处理⽅案：例如，未识别的 proto3 枚举类型会被保存在消息中，但是当消息反序列化时如何表⽰是依赖于编程语⾔的。整型字段总是会保持其的值。
> - **【修改】**oneof：
>   - 将⼀个单独的值更改为 新 oneof 类型成员之⼀是安全和⼆进制兼容的。
>   - 若确定没有代码⼀次性设置多个值那么将多个字段移⼊⼀个新 oneof 类型也是可⾏的。
>   - **将任何字段移⼊已存在的 oneof 类型是不安全的。**



#### 更新规则：删除

> **删除问题：错误删除字段 造成的数据损坏**
>
> ---
>
> 





#### 更新操作说明 / 解释

~~~c++
// 【新增】禁⽌修改任何已有字段的字段编号
/**
* 假设在服务端，存在 一个 age 字段，绑定的编号是 2；
* 同时由于业务需求，不在需要 age 字段！
* 此时的操作：注释掉 age，使用一个新的字段 birth 绑定 编号 2！！！
* 由于业务更改只是在服务端！客服端没有变化，现在如果使用 message 进行序列化的数据，设定新字段 birth = 123456789
* 现场如下：客户端输出现象 age => 123456789
* 
* 原因：protobuf 认定的是编号！根据编号绑定数据进行反序列化
* => 因此：禁⽌修改任何已有字段的字段编号
* => 使用建议：不注释！不删除！直接增加新字段与新序号，修改双端代码，操作新字段即可！！！
* => 或者说：使用 reserved 关键字 保证不在使用已经被删除的或不注释掉的字段编号
*/

// 联系⼈
message PeopleInfo {
    reserved 2;
    string name = 1; // 姓名
//  int32 age = 2; // 年龄
//  int32 birth = 2; // 年龄：错误
    int32 birth = 4; // 年龄：错误
    
    message Phone {
       string number = 1; // 电话号码
    }
 repeated Phone phone = 3; // 电话
}

// 图示：看 pic 文件夹！
~~~



![](.\pic\resered关键字与字段更新示例图.png)



#### reserved 关键字

> **用法：**
>
> - **reserved + 编号, 编号, ...**
>   - **保留指定编号**
> - **reserved + 编号x to 编号y**
>   - **保留从 x 到 y 的所有编号**
>
> ---
>
> **作用说明：关键字指示保留给定的编号，如果使用，就会编译时报错！**





### 未知字段

> 如上《更新消息》中，我们更新了服务端中的 protobuf 字段，同时进行了序列化，客户端中不知道！没有同步更新，客户端反序列化后，不认识的字段（新的字段编号）就会放在未知字段。
>
> ---
>
> - 未知字段：解析结构良好的 protocol buffer 已序列化数据中的未识别字段的表⽰⽅式。例如，当旧程序解析带有新字段的数据时，这些新字段就会成为旧程序的未知字段。
> - 本来，proto3 在解析消息时总是会丢弃未知字段，但在 3.5 版本中重新引⼊了对未知字段的保留机制。所以在 3.5 或更⾼版本中，未知字段在反序列化时会被保留，同时也会包含在序列化的结果
>   中。
>
> ---
>
> 未知字段，在 UnkownField 类中



#### 未知字段的使用认识

> **UnknownFieldSet 包含在分析消息时遇到但未由其类型定义的所有字段。**
>
> **若要将 UnknownFieldSet 附加到任何消息，请、需要调⽤ Reflection::GetUnknownFields()。**
>
> 类定义在 unknown_field_set.h 中。



#### UnknownFieldSet 类中的基本方法

~~~c++
clear();
// 清除

empty();
// 判断是否有未知字段

field_count();
// 获取未知字段个数

field(int idx);
// 每个类型对象

number();
// 位置字段编号

type();
// 未知字段类型

enum Type {
	TYPE_VARINT,
	TYPE_FIXED32,
	TYPE_FIXED64,
	TYPE_LENGTH_DELIMITED,
	TYPE_GROUP
};
inline uint64_t varint() const;
inline uint32_t fixed32() const;
inline uint64_t fixed64() const;
inline const std::string& length_delimited() const;
inline const UnknownFieldSet& group() const;
// 获取未知字段的值【枚举类型匹配才能使用对应方法】
~~~





#### UnknownField 类介绍

> 表⽰未知字段集中的⼀个字段。
>
> 类定义在 unknown_field_set.h 中。



#### 未知字段获取实操【重点：含步骤和方法】

~~~c++
// 1. 定义一个 Reflection 对象
// 对象的位置：google::protobuf

// 2. 使用 全局静态方法 GetReflection() 初始化 Reflection 对象。函数返回值：Reflection*

// 以上步骤合并：
using namespace goolge.protobuf;

const Reflection* reflection = message::GetReflection();

// 3. 使用对象获取指定 message 的未知字段
// 调用 GetUnknownFields 函数返回值类型：UnknownFieldSet
const GetUnknownFields& set = reflection->GetUnknownFields(message);

// 4. 遍历存在的未知字段

~~~





### Option 选项

#### 选项作用认识

> **.proto ⽂件中可以声明许多选项，使⽤ option 标注。选项能影响 proto 编译器的某些处理⽅式。**
>
> ---
>
> **如使用：LITE_RUNTIME**
>
> - **原来没使用 选项时：生成的 message 父类是 Message**
> - **使用选项后：父类 MessageLite**



#### 选项分类

> 选项的完整列表在 google/protobuf/descriptor.proto 中定义。
>
> 选项分为 ⽂件级、消息级、字段级 等等， 但并没有⼀种选项能作⽤于所有的类型。

~~~c++
syntax = "proto2"; // descriptor.proto 使⽤ proto2 语法版本
message FileOptions { ... } // ⽂件选项 定义在 FileOptions 消息中
message MessageOptions { ... } // 消息类型选项 定义在 MessageOptions 消息中
message FieldOptions { ... } // 消息字段选项 定义在 FieldOptions 消息中
message OneofOptions { ... } // oneof字段选项 定义在 OneofOptions 消息中
message EnumOptions { ... } // 枚举类型选项 定义在 EnumOptions 消息中
message EnumValueOptions { .. } // 枚举值选项 定义在 EnumValueOptions 消息中
message ServiceOptions { ... } // 服务选项 定义在 ServiceOptions 消息中
message MethodOptions { ... } // 服务⽅法选项 定义在 MethodOptions 消息中
...
~~~





#### 常⽤选项列举

> **optimize_for : 该选项为⽂件选项，可以设置 protoc 编译器的优化级别**，分别为 SPEED 、CODE_SIZE 、 LITE_RUNTIME 。受该选项影响，设置不同的优化级别，编译 .proto ⽂件后⽣成的代码内容不同。
>
> - **SPEED** : protoc 编译器将⽣成的代码是⾼度优化的，代码运⾏效率⾼，但是由此⽣成的代码编译后会占⽤更多的空间。 SPEED 是默认选项。
> - **CODE_SIZE** : proto 编译器将⽣成最少的类，会占⽤更少的空间，是依赖基于反射的代码来实现序列化、反序列化和各种其他操作。但和 SPEED 恰恰相反，它的代码运⾏效率较低。这种⽅式适合⽤在包含⼤量的.proto⽂件，但并不盲⽬追求速度的应⽤中。
> - **LITE_RUNTIM**E : ⽣成的代码执⾏效率⾼，同时⽣成代码编译后的所占⽤的空间也是⾮常少。这是以牺牲Protocol Buffer提供的反射功能为代价的，仅仅提供 encoding+序列化 功能，所以我们在链接 BP 库时仅需链接libprotobuf-lite，⽽⾮libprotobuf。这种模式通常⽤于资源有限的平台，例如移动⼿机平台中。
>
> ---
>
> allow_alias ： 允许将相同的常量值分配给不同的枚举常量，⽤来定义别名。该选项为枚举选项。

~~~c++
enum PhoneType {
	option allow_alias = true;
	MP = 0;
	TEL = 1;
	LANDLINE = 1; // 若不加 option allow_alias = true; 这⼀⾏会编译报错
}
~~~





#### 自定义选项

> 参考链接：https://developers.google.cn/protocol-buffers/docs/proto?hl=zh-cn#customoptions
>
> 大部分场景用不到。