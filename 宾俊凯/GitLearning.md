**命令总结**

先让机器自报家门用下面的命令 

```git
$$ git config --global user.name "Your Name"
$ git config --global user.email "email@example.com"
```

然后创建空目录

```
$ mkdir learngit
$ cd learngit
$ pwd
```

`pwd`是用于显示当前目录的

上面的`Learngit`是创建的文件夹的名字，可以根据实际需要进行修改

```git
$ git init
```

用`git init`命令来把这个目录变成仓库，创建完成后会多一个.git的目录

```git
$ git add "file"
```

用`git add`命令添加文件（注意文件一定要放在仓库内），然后再运行下面的命令

```git
$ git commit -m"   "
```

添加完后我们就应当进行提交操作，其中双引号的内容最好写对这次提交操作的简单说明，接着运行下面的命令

```git
$ git status
```

这个命令可以让我们掌握仓库当前的状态，每当我们对文件进行修改后，都应该运行这个指令查看当前仓库的状况，如果修改了却没有进行提交，后果会非常麻烦。

如果我们想查看文件被修改了的什么地方那就需要到下面的指令了

```git
$ git diff "file"
```

运行这个指令就可以让我们看到文件被修改了什么地方

知道文件修改了什么地方后我们就可以放心的把文件提交了同样执行下面的命令

```git
$ git add "file"
$ git commit -m"description"
```

**版本回溯**

首先我们要用下面的命令来获得从近到远的版本信息

```git
$ git log
```

如果嫌输出信息太多，看得眼花缭乱的，可以试试加上`--pretty=oneline`参数即

```git
$ git log --pretty=oneline
```

需要友情提示的是，你看到的一大串类似`1094adb...`的是`commit id`(版本号)

当我们需要回到上一个版本时就可以用`reset`命令

```git
$ git reset --hard HEAD^
```

这里的HEAD^表示的就是上一个版本，HEAD^^就是上上个版本，上100个版本就是HEAD~100

版本回退后我们来看看是不是成功了

```git
$ cat "file"
```

好家伙，成功了

这时我们其实还可以回退到更之前的版本，但是且慢，我们再用`git log`查看版本信息，我们发现刚刚最新的版本已经不见了

那怎么办，1，在命令窗口没有关闭的时候，我们可以通过上翻翻到之前版本的版本号，通过reset的命令来恢复。

2，运行下面的指令

```git
$ git reflag
```

这个命令会显示我们的操作历史，通过它来找到我们提交的记录进而找到版本号，这样我们就可以故技重施，回到之前的版本了。

**远程仓库**

首先我们要在`Github`创建一个`Repository`(仓库)，然后在本地运行下面的命令

```git
$ git remote add origin https://github.com/Aurora0201/LearnGit.git  或
$ git remote add origin git@github.com:Aurora0201/LearnGit.git
```

千万注意上面的`Aurora0201`和要改成我们自己的账户名,`LearnGit`要改成我们的仓库名，添加后，远程库的名字就叫`origin`这是默认叫法看到`origin`就会知道这是远程库

下一步就是把本地库的所有内容推送到远程库上，运行下面的命令

```git
$ git push -u origin master
```

把本地库的内容推送到远程，用`git push`命令，实际上是把当前分支`master`推送到远程。

由于远程库是空的，我们第一次推送`master`分支时，加上了`-u`参数，Git不但会把本地的`master`分支内容推送的远程新的`master`分支，还会把本地的`master`分支和远程的`master`分支关联起来，在以后的推送或者拉取时就可以简化命令。

当推送成功后，我们就可以看到`Github`远程库已经和本地一模一样,现在只要本地做了提交，就可以通过下面的命令把本地的master分支的最新修改推送至GitHub，现在我们就拥有了真正的分布式版本库。

```
$ git push origin master
```

**克隆远程库**

先在GitHub创建一个仓库

下一步我们用`git clone`命令克隆一个本地库

```
$ git clone git@github.com:Aurora0201/GitSkill.git
```

然后`Aurora0201`是我们的用户名，`GitSkill`是我们要克隆的仓库

**分支管理**

首先我们创建dev分支然后切换到dev分支，运行下面的命令

```
$ git checkout -b dev
```

加上`-b`参数表示创建并切换，相当于下面两条命令

```
$ git branch dev
$ git checkout dev
```

然后用`git branch`查看当前分支

```
$ git branch
* dev
  master
```

`git branch`命令会列出所有分支，当前分支前面会标一个`*`号。

然后，我们就可以在`dev`分支上正常提交，比如对`readme.txt`做个修改，加上一行：

```
Creating a new branch is quick.
```

然后提交：

```
$ git add readme.txt 
$ git commit -m "branch test"
[dev b17d20e] branch test
 1 file changed, 1 insertion(+)
```

现在，`dev`分支的工作完成，我们就可以切换回`master`分支：

```
$ git checkout master
Switched to branch 'master'
```

切换回`master`分支后，再查看一个`readme.txt`文件，刚才添加的内容不见了！因为那个提交是在`dev`分支上，而`master`分支此刻的提交点并没有变：

现在，我们把`dev`分支的工作成果合并到`master`分支上：

```
$ git merge dev
Updating d46f35e..b17d20e
Fast-forward
 readme.txt | 1 +
 1 file changed, 1 insertion(+)
```

`git merge`命令用于合并指定分支到当前分支。合并后，再查看`readme.txt`的内容，就可以看到，和`dev`分支的最新提交是完全一样的。

注意到上面的`Fast-forward`信息，Git告诉我们，这次合并是“快进模式”，也就是直接把`master`指向`dev`的当前提交，所以合并速度非常快。

当然，也不是每次合并都能`Fast-forward`，我们后面会讲其他方式的合并。

合并完成后，就可以放心地删除`dev`分支了：

```
$ git branch -d dev
Deleted branch dev (was b17d20e).
```

删除后，查看`branch`，就只剩下`master`分支了：

```
$ git branch
* master
```

因为创建、合并和删除分支非常快，所以Git鼓励你使用分支完成某个任务，合并后再删掉分支，这和直接在`master`分支上工作效果是一样的，但过程更安全。

创建并切换到新的`dev`分支，可以使用：

```
$ git switch -c dev
```

直接切换到已有的`master`分支，可以使用：

```
$ git switch master
```

待续