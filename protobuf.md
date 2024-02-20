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





### 消息类型的定义与使用