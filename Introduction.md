## Introduction

本项目为C++编写的基于epoll的网络服务器框架，应用层实现了简单的HTTP服务器，以及对MYSQL数据库的接入，其中HTTP服务器实现了HTTP的解析和Get方法请求，目前支持静态资源访问，该框架不限于这两类服务器，用户可根据需要编写应用层服务。

## Origin and purpose of the project

- 项目目的：学习C++知识、部分C++11的语法和编码规范、学习巩固网络编程、网络IO模型、多线程、git使用、Linux命令、性能分析、TCP/IP、HTTP协议等知识 

## Envoirment

- OS:  Ubuntu-20.4
- kernel: Linux 5.11.0-36-generic x86_64
- Complier: g++ 9.3.0

## Build

```
make
```

## Run

```
./main
```

## Tech

- 基于epoll的IO复用机制实现Reactor模式，采用边缘触发（ET）模式，和非阻塞模式 
- 由于采用ET模式，read、write和accept的时候必须采用循环的方式，直到error==EAGAIN为止，防止漏读等清况，这样的效率会比LT模式高很多，减少了触发次数 
- 目前基于单线程实现，接下来继续进行多线程开发，基于one loop per thread的IO模式 
- 支持HTTP长连接 
- 支持优雅关闭连接 
  - 通常情况下，由客户端主动发起FIN关闭连接 
  - 客户端发送FIN关闭连接后，服务器把数据发完才close，而不是直接暴力close 
  - 如果连接出错，则服务器可以直接close 

## Performance Test

- 本项目采用了两款开源的HTTP压力测试工具“wrk”和“WebBench”进行测试，其中使用了林亚改写后的[WebBench](https://github.com/linyacool/WebBench) 
- 测试方法
  - 模拟1000条TCP连接，持续时间30s 
  - 测试长连接情况 
  - 考虑到磁盘IO的影响，分别对有/无磁盘IO影响两种情况做测试，测试时服务器的响应报文分别为: 保存到内存中的HTTP报文（无磁盘IO影响）、HTTP报头+读取磁盘的index.html网页（有磁盘IO影响） 
- 测试环境（虚拟机环境下测试，性能可能较物理机低）
  - CPU: Intel(R) Core(TM) i5-4440 CPU @ 3.10GHz 
  - Memory: 2G 
  - VirtualBox 5.2.20 
  - OS: CentOS Linux release 7.0.1406 
  - kernel: 3.10.0-123.el7.x86_64 
- wrk测试结果：8万+QPS、4万+QPS
  - 内存中的HTTP报文（无磁盘IO影响） [wrk](https://github.com/chenshuaihao/NetServer/blob/master/docs/images/wrk_hello.png)
  - index.html网页（有磁盘IO影响） [wrk](https://github.com/chenshuaihao/NetServer/blob/master/docs/images/wrk_html.png)
- WebBench测试结果
  - 内存中的HTTP报文（无磁盘IO影响） [WebBench](https://github.com/chenshuaihao/NetServer/blob/master/docs/images/WebBench_hello.png)
  - index.html网页（有磁盘IO影响） [WebBench](https://github.com/chenshuaihao/NetServer/blob/master/docs/images/WebBench_html.png)

## License

See [LICENSE](https://github.com/chenshuaihao/NetServer/blob/master/LICENSE)

## Roadmap

多线程、线程池、定时器、日志系统、内存池等

## Others

本项目将一直进行开发和维护，也非常欢迎各位小伙伴提出建议，共同学习，共同进步！

Enjoy!