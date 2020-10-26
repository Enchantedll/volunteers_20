# volunteers_20
创建版本库
英文名repository,git可以管理里面的所有文件，追踪文件的修改和删除以及还原文件。
创建，创建一个空目录
$ mkdir learngit
$ cd learngit
$ pwd
/Users/michael/learngit
pwd命令用于显示当前目录。在我的Mac上，这个仓库位于/Users/michael/learngit。
通过git init命令把这个目录变成Git可以管理的仓库：
$ git init
Initialized empty Git repository in /Users/michael/learngit/.git/
多出的git目录是Git来跟踪管理版本库的,如果没有看到.git目录，那是因为这个目录默认是隐藏的，用ls -ah命令就可以看见。
选择一个有东西的目录创建git仓库也可以。
把文件添加到版本库
git能跟踪文本文件的改动，而图片、视频这些二进制文件，虽然也能由版本控制系统管理，但没法跟踪文件的变化，只能把二进制文件每次改动串起来，也就是只知道图片从100KB改成了120KB，但到底改了啥，版本控制系统不知道，也没法知道。Microsoft的Word格式是二进制格式，版本的控制系统没法跟踪Word文件的改动。如果要真正使用版本控制系统，就要以纯文本方式编写文件，使用标准的UTF-8编码。
使用Windows的下载Notepad++来编辑文本文件。
编写一个readme.txt文件
Git is a version control system.
Git is free software.
用命令git add告诉Git，把文件添加到仓库：
$ git add readme.txt
用命令git commit告诉Git，把文件提交到仓库：
$ git commit -m "wrote a readme file"
[master (root-commit) eaadf4e] wrote a readme file
 1 file changed, 2 insertions(+)
 create mode 100644 readme.txt
-m后面输入的是本次提交的说明，git commit命令执行成功后会告诉你，1 file changed：1个文件被改动（我们新添加的readme.txt文件）；2 insertions：插入了两行内容（readme.txt有两行内容）。git add<file>反复多次使用，添加多个文件。



修改readme.txt文件，改成如下内容：
Git is a distributed version control system.
Git is free software.
运行git status命令看看系统的工作区的状态：

$ git status
On branch master
Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git checkout -- <file>..." to discard changes in working directory)

	modified:   readme.txt

no changes added to commit (use "git add" and/or "git commit -a")
用git diff来看修改内容:

$ git diff readme.txt 
diff --git a/readme.txt b/readme.txt
index 46d49bf..9247db6 100644
--- a/readme.txt
+++ b/readme.txt
@@ -1,2 +1,2 @@
-Git is a version control system.
+Git is a distributed version control system.
 Git is free software.




版本回退
在git中，每当你觉得文件修改到一定程度的时候，就可以“保存一个快照”，这个快照在Git中被称为commit。一旦你把文件改乱了，或者误删了文件，还可以从最近的一个commit恢复，然后继续工作。在Git中，我们用git log命令查看每次修改的内容，git log命令显示从最近到最远的提交日志。如果嫌输出信息太多，看得眼花缭乱的，可以试试加上--pretty=oneline参数：

$ git log --pretty=oneline
1094adb7b9b3807259d8cb349e7df1d4d6477073 (HEAD -> master) append GPL
e475afc93c209a690c39c13a46716e8fa000c366 add distributed
eaadf4e385e865d25c48e7ca9c8395c3f7dfaef0 wrote a readme file
看到的一大串类似1094adb...的是commit id（版本号)，在Git中，用HEAD表示当前版本，上一个版本就是HEAD^，上上一个版本就是HEAD^^，当然往上100个版本写100个^比较容易数不过来，所以写成HEAD~100。回退版本使用git reset:
$ git reset --hard HEAD^
HEAD is now at e475afc add distributed
此时最新版本已经用git log已经看不到了，但是如果上面的命令行窗口还没有被关掉，你就可以顺着往上找啊找啊，找到那个append GPL的commit id是1094adb...，于是就可以指定回到未来的某个版本：
$ git reset --hard 1094a
HEAD is now at 83b0afe append GPL
如果命令窗口已经关掉，可以用git reflog找到你所需版本的commit id
工作区(working derectory)与暂停区
Git的版本库里有暂停区stage（或者叫index）和Git为我们自动创建的第一个分支master，以及指向master的一个指针叫HEAD。
第一步是用git add把文件添加进去，实际上就是把文件修改添加到暂存区；
第二步是用git commit提交更改，实际上就是把暂存区的所有内容提交到当前分支。

管理修改
Git跟踪并管理的是修改，每次修改，如果不用git add到暂存区，那就不会加入到commit中。
撤销修改
命令git checkout -- readme.txt意思就是，把readme.txt文件在工作区的修改全部撤销，这里有两种情况：
一种是readme.txt自修改后还没有被放到暂存区，现在，撤销修改就回到和版本库一模一样的状态；
一种是readme.txt已经添加到暂存区后，又作了修改，现在，撤销修改就回到添加到暂存区后的状态。
总之，就是让这个文件回到最近一次git commit或git add时的状态。
命令git reset HEAD <file>可以把暂存区的修改撤销掉（unstage），重新放回工作区

删除文件
直接在文件管理器中把没用的文件删了，或者用rm命令删了，这个时候，Git知道你删除了文件，因此，工作区和版本库就不一致了，git status命令会立刻告诉你哪些文件被删除了，
现在你有两个选择:
一是确实要从版本库中删除该文件，那就用命令git rm删掉，并且git commit，文件就从版本库中被删除了。
先手动删除文件，然后使用git rm <file>和git add<file>效果是一样的。
另一种情况是删错了，因为版本库里还有呢，所以可以很轻松地把误删的文件恢复到最新版本：
$ git checkout -- test.txt
但是从来没有被添加到版本库就被删除的文件，是无法恢复的！


远程仓库
第1步：创建SSH Key。在用户主目录下，看看有没有.ssh目录，如果有，再看看这个目录下有没有id_rsa和id_rsa.pub这两个文件，如果已经有了，可直接跳到下一步。如果没有，打开Shell（Windows下打开Git Bash），创建SSH Key：
$ ssh-keygen -t rsa -C "youremail@example.com"
如果一切顺利的话，可以在用户主目录里找到.ssh目录，里面有id_rsa和id_rsa.pub两个文件，这两个就是SSH Key的秘钥对，id_rsa是私钥，id_rsa.pub是公钥

第2步：登陆GitHub，打开“Account settings”，“SSH Keys”页面。然后，点“Add SSH Key”，填上任意Title，在Key文本框里粘贴id_rsa.pub文件的内容，点“Add Key”，你就应该看到已经添加的Key

添加远程库

想在GitHub创建一个Git仓库，并且让这两个仓库进行远程同步，这样，GitHub上的仓库既可以作为备份，又可以让其他人通过该仓库来协作。
首先，登陆GitHub，然后，在右上角找到“Create a new repo”按钮，创建一个新的仓库：
github-create-repo-1
在Repository name填入learngit，其他保持默认设置，点击“Create repository”按钮，就成功地创建了一个新的Git仓库
现在，我们根据GitHub的提示，在本地的learngit仓库下关联一个远程库。
$ git remote add origin git@github.com:michaelliao/learngit.gi
添加后，远程库的名字就是origin，把本地库的内容推送到远程，用git push命令。
关联后，使用命令git push -u origin master第一次推送master分支的所有内容；从现在起，只要本地作了提交，就可以通过命令：
$ git push origin master
把本地master分支的最新修改推送至GitHub


从远程库克隆
从远程库到本地库:
首先，登陆GitHub，创建一个新的仓库，名字叫gitskills
我们勾选Initialize this repository with a README，这样GitHub会自动为我们创建一个README.md文件。创建完毕后，可以看到README.md文件：
github-init-repo-2
现在，远程库已经准备好了，下一步是用命令git clone克隆一个本地库
注意把Git库的地址换成你自己的，然后进入gitskills目录看看，已经有README.md文件了。
GitHub给出的地址不止一个，还可以用https://github.com/michaelliao/gitskills.git这样的地址。实际上，Git支持多种协议，默认的git://使用ssh，但也可以使用https等其他协议。
使用https除了速度慢以外，还有个最大的麻烦是每次推送都必须输入口令，但是在某些只开放http端口的公司内部就无法使用ssh协议而只能用https。

分支管理
创建与合并分支
在Git里，这个分支叫主分支，即master分支。HEAD严格来说不是指向提交，而是指向master，master才是指向提交的，所以，HEAD指向的就是当前分支。
查看分支：git branch
创建分支：git branch <name>
切换分支：git checkout <name>或者git switch <name>
创建+切换分支：git checkout -b <name>或者git switch -c <name>
合并某分支到当前分支：git merge <name>
删除分支：git branch -d <name>

解决冲突
当Git无法自动合并分支时，就必须首先解决冲突。解决冲突后，再提交，合并完成。

解决冲突就是把Git合并失败的文件手动编辑为我们希望的内容，再提交。
用git log --graph命令可以看到分支合并图。
分支管理策略
合并分支时，加上--no-ff参数就可以用普通模式合并，合并后的历史有分支，能看出来曾经做过合并，而fast forward合并就看不出来曾经做过合并。
bug分支
Git还提供了一个stash功能，可以把当前工作现场“储藏”起来，等以后恢复现场后继续工作。修复好bug后，用git stash list命令找到之前隐藏的工作现场。恢复有两种办法，
一是用git stash apply恢复，但是恢复后，stash内容并不删除，你需要用git stash drop来删除
另一种方式是用git stash pop，恢复的同时把stash内容也删了
同样的bug，要在dev上修复，我们只需要把4c805e2 fix bug 101这个提交所做的修改“复制”到dev分支，Git专门提供了一个cherry-pick命令，让我们能复制一个特定的提交到当前分支。
feature分支
添加新功能时，为了不希望一些实验性质的代码把主分支弄乱，最好新建一个feature分支，在上面开发，完成后，合并，最后，删除该feature分支。如果要丢弃一个没有被合并过的分支，可以通过git branch -D <name>强行删除。
多人协作
当你从远程仓库克隆时，实际上Git自动把本地的master分支和远程的master分支对应起来了，并且，远程仓库的默认名称是origin。
要查看远程库的信息，用git remote。或者，用git remote -v显示更详细的信息。
上面显示了可以抓取和推送的origin的地址。如果没有推送权限，就看不到push的地址。
推送分支，就是把该分支上的所有本地提交推送到远程库。推送时，要指定本地分支，这样，Git就会把该分支推送到远程库对应的远程分支上，
master分支是主分支，因此要时刻与远程同步；
dev分支是开发分支，团队所有成员都需要在上面工作，所以也需要与远程同步；
bug分支只用于在本地修复bug，就没必要推到远程了，除非老板要看看你每周到底修复了几个bug；
feature分支是否推到远程，取决于你是否和你的小伙伴合作在上面开发。
多人协作:首先，可以试图用git push origin <branch-name>推送自己的修改；
如果推送失败，则因为远程分支比你的本地更新，需要先用git pull试图合并；
如果合并有冲突，则解决冲突，并在本地提交；
没有冲突或者解决掉冲突后，再用git push origin <branch-name>推送就能成功！
如果git pull提示no tracking information，则说明本地分支和远程分支的链接关系没有创建，用命令git branch --set-upstream-to <branch-name> origin/<branch-name>。
rebase
rebase操作可以把本地未push的分叉提交历史整理成直线；
rebase的目的是使得我们在查看历史提交的变化时更容易，因为分叉的提交需要三方对比。


标签管理
创建标签
首先，切换到需要打标签的分支上，然后，敲命令git tag <name>就可以打一个新标签，可以用命令git tag查看所有标签。
默认标签是打在最新提交的commit上的。要对add merge这次提交打标签，它对应的commit id是f52c633，敲入命令：
$ git tag v0.9 f52c633
再用命令git tag查看标签
注意，标签不是按时间顺序列出，而是按字母排序的。可以用git show <tagname>查看标签信息。还可以创建带有说明的标签，用-a指定标签名，-m指定说明文字：
$ git tag -a v0.1 -m "version 0.1 released" 1094adb

操作标签
推送某个标签到远程，使用命令git push origin <tagname>。命令git push origin --tags可以推送全部未推送过的本地标签。
想要删除时，如果标签已经推送到远程，要删除远程标签就麻烦一点，先从本地删除，
命令git tag -d <tagname>可以删除一个本地标签。
然后，从远程删除。删除命令也是push，但是格式如下：
$ git push origin :refs/tags/v0.9
To github.com:michaelliao/learngit.git
 - [deleted]         v0.9
要看看是否真的从远程库删除了标签，可以登陆GitHub查看。
使用GitHub
在GitHub上，可以任意Fork开源仓库；
自己拥有Fork后的仓库的读写权限；
可以推送pull request给官方仓库来贡献代码。
使用gitee
首先，我们在Gitee上创建一个新的项目,项目名称最好与本地库保持一致。
然后，我们在本地库上使用命令git remote add把它和Gitee的远程库关联。
如果在使用命令git remote add时报错：这说明本地库已经关联了一个名叫origin的远程库，我们可以删除的oringe远程库指向的GitHub远程库，再关联Gitee的远程库。也可以我们先删除已关联的名为origin的远程库，然后再关联GitHub和Gitee的远程库。


自定义git
忽略特殊文件
在Git工作区的根目录下创建一个特殊的.gitignore文件，然后把要忽略的文件名填进去，Git就会自动忽略这些文件。忽略文件的原则是：
忽略操作系统自动生成的文件，比如缩略图等；
忽略编译生成的中间文件、可执行文件等，也就是如果一个文件是通过另一个文件自动生成的，那自动生成的文件就没必要放进版本库，比如Java编译产生的.class文件；
忽略你自己的带有敏感信息的配置文件，比如存放口令的配置文件。
最后一步就是把.gitignore也提交到Git，就完成了！当然检验.gitignore的标准是git status命令是不是说working directory clean。
在windows中在资源管理器里新建一个.gitignore文件，在文本编辑器里“保存”或者“另存为”就可以把文件保存为.gitignore了。有些时候，你想添加一个文件到Git，但发现添加不了，原因是这个文件被.gitignore忽略了，如果你确实想添加该文件，可以用-f强制添加到Git：
$ git add -f App.class
或者你发现，可能是.gitignore写得有问题，需要找出来到底哪个规则写错了，可以用git check-ignore命令检查。把指定文件排除在.gitignore规则外的写法就是!+文件名，所以，只需把例外文件添加进去即可。
配置别名
配置Git的时候，加上--global是针对当前用户起作用的，如果不加，那只针对当前的仓库起作用。每个仓库的Git配置文件都放在.git/config文件，别名就在[alias]后面，要删除别名，直接把对应的行删掉即可。而当前用户的Git配置文件放在用户主目录下的一个隐藏文件.gitconfig中。
搭建git服务器
搭建Git服务器需要准备一台运行Linux的机器，强烈推荐用Ubuntu或Debian，这样，通过几条简单的apt命令就可以完成安装。假设你已经有sudo权限的用户账号，第一步——安装git，第二步——创建一个git用户，用来运行git服务。第三步——创建证书登录：收集所有需要登录的用户的公钥，就是他们自己的id_rsa.pub文件，把所有公钥导入到/home/git/.ssh/authorized_keys文件里，一行一个。第四步——初始化Git仓库：先选定一个目录作为Git仓库，假定是/srv/sample.git，在/srv目录下输入命令：$ sudo git init --bare sample.git
第五步——禁用shell登录：出于安全考虑，第二步创建的git用户不允许登录shell，这可以通过编辑/etc/passwd文件完成。第六步——克隆远程仓库。要方便管理公钥，用Gitosis；
要像SVN那样变态地控制权限，用Gitolite。
使用source tree
如果本地已经有了Git库，直接从资源管理器把文件夹拖拽到SourceTree上，就添加了一个本地Git库，也可以选择“New”-“Clone from URL”直接从远程克隆到本地。
使用SourceTree可以以图形界面操作Git，省去了敲命令的过程，对于常用的提交、分支、推送等操作来说非常方便。
SourceTree使用Git命令执行操作，出错时，仍然需要阅读Git命令返回的错误信息。
