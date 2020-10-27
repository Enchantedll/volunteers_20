GIT学习分享
1.GIT是什么？（来源：百度百科）
Git是一个开源的分布式版本控制系统，可以有效、高速地处理从很小到非常大的项目版本管理。
Git 是 Linus Torvalds 为了帮助管理 Linux 内核开发而开发的一个开放源码的版本控制软件。
Torvalds 开始着手开发 Git 是为了作为一种过渡方案来替代 BitKeeper。
2.GIT优缺点： （来源：百度百科 以及 https://www.liaoxuefeng.com/wiki/896043488029600 ）
 优  1）适合分布式开发，强调个体。
       2）公共服务器压力和数据量都不会太大。
       3）速度快、灵活。
       4）任意两个开发者之间可以很容易的解决冲突。
       5）离线工作。
缺   1）资料少（起码中文资料很少）。
  （保姆级教学：https://www.bilibili.com/video/BV1Xx411m7kn/?p=10  适合纯小白建议2倍速）
       2）学习周期相对而言比较长。
       3）不符合常规思维。
       4）代码保密性差，一旦开发者把整个库克隆下来就可以完全公开所有代码和版本信息。
             （或者你搞个私人服务器）
3.安装GIT: 
      https://git-scm.com/downloads 下好以后一路next
4.GIT基本指令：
        1）准备：账户初始化
              git config --global user.name "你的github用户名"
              git cinfig --global user.email "你的邮箱"

        注：当账号被冒充也有办法追查
	2）创建版本库(仓库) Repository
git init

 3）文件相关操作
               文件创建
touch 文件名

 	文件修改
vim 文件名      

        查看文件
cat 文件名

       将文件提交到暂存区
git add 文件名

       将文件提交到仓库
