
# 代码工程管理及编译指导

---

## 功能介绍 

 - **每个独立的功能组件使用一个对应的以`.mk`作为后缀的`Makefile`文件进行管理。** 

 开发者可在其中添加期望被编译的源文件、仅被本组件内部访问的头文件路径、可被所有组件访问的头文件路径、仅被本组件内部使用的宏定义、可被所有组件使用的宏定义，以及本组件需要依赖的其他组件。 

 - **支持同一个代码工程里包含多个不同业务功能的应用代码。** 

开发者可以在该SDK下添加多个不同的应用代码文件夹，如`app`、`app2`等。应用代码目录的存放位置可放在SDK根目录下的任何位置，为了规范起见，建议直接放在根目录下。如果在某个组件中需要添加相应的组件测试`demo`，该`demo`应用建议放在该组件的目录下。 

 - **通过编译脚本的命令行进行指定应用的编译和目标清除** 

 启动`heliso`命令，可以将指定应用目录下的代码和SDK一起编译，也可以调用`helios clean`命令，清除编译生成的`output`文件夹。 
 
## 操作说明

#### **1. 使用`.mk`文件进行组件的管理** 

 任何一个组件的根目录下必须存在一个和当前文件夹同名的`.mk`文件。该Makefile文件中可以添加以下脚本代码： 

``` 
NAME = component_name                # 组件名称，建议和所在目录名称一致

GLOBAL_INCS = public/inc             # 允许外部引用的头文件路径，不在此列的头文件路径，其他组件无法直接引用

GLOBAL_DEFINE = PUBLIC_MACRO         # 当前组件内定义的、允许外部组件引用的宏。

$(NAME)_CFLAGS = -Wno-error=incompatible-pointer-types  # 仅当前组件内部可引用的编译选项

$(NAME)_ARCHIVES := src/archive.a    # 当前组件内参与编译的库文件

$(NAME)_SRCS := src/source.c asm.s   # 当前组件内参与编译的源码文件，包括c和汇编

$(NAME)_INCS := local/Inc            # 仅当前组件内部可引用的头文件路径，在此列的头文件路径，其他组件无法直接引用

$(NAME)_DEFINE := LOCAL_MACRO        # 当前组件内定义的、仅组件内部可引用的宏，不允许外部组件引用。

$(NAME)_COMPONENTS := third_party/LinkSDK \
                     system/protocols/ftp     # 当前组件依赖的其他组件的相对路径（相对于根目录）
``` 

#### **2. 编译脚本的命令使用** 

编译命令格式：**`<cmd> <action> [<app>] [<at>] [<fw_name>]`**

`<cmd>`：编译命令，即`helios`

`<action>`：脚本的行为，取值如下：

&ensp;&ensp;&ensp;&ensp;`help`：打印编译脚本的用法。

&ensp;&ensp;&ensp;&ensp;`menuconfig`：编译配置菜单。

&ensp;&ensp;&ensp;&ensp; `make`：构建编译目标。

&ensp;&ensp;&ensp;&ensp;`private_clean`：清除应用层内部在编译前生成的私有的目标文件，比如python服务需要提前生成_frozen_mpy.c和相关头文件，该命令可清除之。

&ensp;&ensp;&ensp;&ensp;`clean`：清除编译目标（即output目录）。

`<app>`：可选项，当`<action>`取值为make时，必选。

&ensp;&ensp;&ensp;&ensp;指定应用入口的相对位置（即编译或烧录哪一个应用固件，相对于根目录）。

`<at>`：可选项，当`<action>`取值为make时生效。

&ensp;&ensp;&ensp;&ensp;参数格式：`@`分隔的多个单词，目前限定于`模块型号`和`编译命令回显开关`。例如`EC200UCN_AA@verbose`，表示编译EC200UCN_AA的模块，打开编译命令回显开关。该参数的首尾也可以添加`@`。

&ensp;&ensp;&ensp;&ensp;当只有一个单词时，务必在首或尾，或首尾同时，添加`@`。

&ensp;&ensp;&ensp;&ensp;默认：编译EC200UCN_AA模块，并且不开启编译命令回显。

`<fw_name>`：可选项，当`<action>`取值为make时生效。

&ensp;&ensp;&ensp;&ensp;用来指定固件版本号，默认值为应用根目录名称。

>【注意】 
>1. 通过应用配置脚本指定的全局宏定义，在每一次变更宏定义时，会自动删除编译目录，以期全部重新编译所有代码，从而让变更后的全局宏定义能够起作用，否则，由于源文件没变化过，引用该宏定义的源码将不会被编译，导致宏定义无效。 
>2. 通过`.mk`文件定义的宏，在宏定义有变动后，一定要先执行`clean`命令，原因同上。 
>3. `<at>`和`<fw_name>`两个参数顺序可互换。
