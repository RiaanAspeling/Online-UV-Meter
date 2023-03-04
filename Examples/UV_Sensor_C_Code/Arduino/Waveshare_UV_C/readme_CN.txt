/*****************************************************************************
* | File      	:   Readme_CN.txt
* | Author      :   Waveshare team
* | Function    :   Help with user
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2021-08-13
* | Info        :   在这里提供一个中文版本的使用文档，以便你的快速使用
******************************************************************************/
这个文件是帮助您使用本例程。

1.基本信息：
本例程是基于Arduino进行开发的，例程均在Arduino UNO上进行了验证;
本例程使用UV Sensor C模块进行了验证。

2.代码简介：
DEV_Config.cpp/h为底层接口
LTR390.cpp/h 为驱动文件


3.基本使用：
由于本工程是一个综合工程，对于使用而言，你可能需要阅读以下内容：
方法1:
    将整个EPD文件夹复制到Arduino安装路径下libraries文件夹中
        ..\Arduino\libraries
方法2:
    将EPD文件夹中src文件夹复制到
        C:\Users\用户名\Documents\Arduino\libraries
        或者 ..\文档\Arduino\libraries

然后打开examples文件夹中对应的工程烧录即可。
