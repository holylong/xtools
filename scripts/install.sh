#!/bin/bash

#跳转行数,负责定位到压缩包所在的位置
lines=63

#检查系统的架构是否符合
if [[ "x86_64" =~ "$(arch)" ]]
then
	echo "架构相同"
else
	echo "架构不同, 本机架构为$(arch)"
	exit 0
fi

homepath=~
#获取安装路径
echo "输入安装路径, 按下回车确认，默认路径(${homepath})"
read -p "请输入：" installpath
if [ ! -n "$installpath" ]; then
	installpath=$homepath
fi


#解压对应的程序包
#根据安装脚本的行数,跳转到压缩包所在的位置
tail -n +$lines $0 > build_ninja.tar.gz

#解压缩
tar zxvf build_ninja.tar.gz

#将解压缩之后文件拷贝到对应的安装目录
mkdir -p $installpath/install/xtools
cp -rf build_ninja/* $installpath/install/xtools

#检查用户路径,获取桌面路径
test -f ~/.config/user-dirs.dirs && . ~/.config/user-dirs.dirs
desktopDir=~/${XDG_DESKTOP_DIR##*/}

#生成快捷方式,替换快捷方式中的安装路径
sed -i "s#INSTALLPATH#${installpath}#g" $installpath/install/xtools/xtools.desktop

#applications文件夹如果不存在则创建
if [ ! -d ~/.local/share/applications ];then
    mkdir -p ~/.local/share/applications
fi

#拷贝桌面快捷方式
cp $installpath/install/xtools/xtools.desktop ~/.local/share/applications

#自定义协议启动
xdg-mime default xtools.desktop x-scheme-handler/clerk

#快捷方式发送到桌面,并修改可执行权限
cp $installpath/install/xtools/xtools.desktop ${desktopDir}
chmod +x ${desktopDir}/xtools.desktop


#移除无用文件
rm -rf $installpath/install/xtools/xtools.desktop
rm -rf build_ninja
rm -rf build_ninja.tar.gz
exit 0
