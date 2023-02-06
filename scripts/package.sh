#!/bin/bash
cp ./scripts/xtools.desktop ./build_ninja
#将源文件打包成压缩包
tar czvf build_ninja.tar.gz build_ninja
#创建.run的输出目录
mkdir -p output

#从外界获取输入的版本号
echo "请输入版本号,回车结束, 示例(1.0.0)"
read -p "请输入：" version
if [ ! -n "$version" ]; then
	version=1.0.0.1
fi

# 打包生成.run文件
cat ./scripts/install.sh build_ninja.tar.gz > output/xtools_"$version".run
# 删除之前的文件压缩包
rm  -f build_ninja.tar.gz