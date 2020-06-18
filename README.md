# IPC-performance-compare
Compare performance of IPC(Inter-Process Communication), include file, zeromq, socket, unixsocket, share-memory, msq-queue and so on 

# 共享内存不能运行问题已经修复
# 关于共享内存的资料可以参考[共享内存](http://users.cs.cf.ac.uk/Dave.Marshall/C/node27.html)
后续会把代码重新整理

在项目中，经常会遇到单机上进程间的通信，常用的进程间通信方式一般有以下几种

1 socket 

2 unixsocket

3 共享内存（share-memory)

4 管道(pipe)

5 消息队列（message-queue）

6 文件（file）

7 消息总线（比如zeromq）

8 其他中间件（比如redis， memchache， 数据库等）

如果项目仅仅是消息的传递，对性能要求不高，则以上每种方式都可以实现进程间通信，我们可以选择较容易实现的方式来运用。

如果项目对消息传递性能要求很高，则我们可能会选用unixsocket，file，或者socket等， 具体哪种方式是最快的，性能最好的，则可能不太清楚。

所以，近日针对项目需要高性能的进程间通信需求，对几种通信方式的性能进行了比较，结论如下：

性能综合排序结果为（从好到差）
0	share-memory(采用信号量进行同步控制，共享内存性能最好)
1	zmq	 
2	file（no flush）
3	msgqueue	 
4	unixsocket
5	pipe	 
6	socket	 
7	file(flush)
测试方式为：把一定量的数据从服务器端发出，客户端进行接收，最后比较总耗时，并计算每秒能够处理的记录数。

