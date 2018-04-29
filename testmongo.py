# -*- coding:utf-8 -*-
#__author: allenboy
#date:  2018/4/25
import pymongo
import socket
import threading
import pymongo
from bson import json_util as jsonb
from bson.objectid import ObjectId
import struct
client=pymongo.MongoClient("localhost", 27017)
#获取数据库 test
db=client.test
#获取数据库集合
stu=db.stu
def AcceptProc(*args, **kwargs):
    # 将绑定的套接字传进来
    sServer = kwargs['socket']
    while True:
        # 获取和客户端交互的套接字以及端口
        print("runing........")
        client, addr = sServer.accept()
        # 获取返回的ip和端口号
        ip, port = addr
        print("用户 " + ip + " 通过 " + str(port) + " 端口启用云查杀")
        # 建立接收客户端消息的线程
        t2 = threading.Thread(name='ThreadRecv', target=RecvProc, kwargs={'socket': client, 'addr': addr})
        t2.start()

# 创建一个套接字
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM, socket.IPPROTO_TCP)
# 绑定套接字
server.bind(("192.168.1.192", 1234))
# 监听
server.listen(socket.SOMAXCONN)
# 等待客户端连接的线程
t1 = threading.Thread(name='ThreadAccept', target=AcceptProc, kwargs={'socket': server})
t1.start()

def RecvProc(*args, **kwargs):
    print(kwargs)
    data = kwargs['socket'].recv(1024).decode("gb2312")
    print(data)
    temp=data.split('###')
    if temp is not None:
        print(list(stu.find()))
        print(temp)
        print((temp[0]))
        print((temp[1]))
        print((temp[2]))
        s1 = {temp[0]: temp[1]}
        #如果为1代表查
        if temp[1]=='1':
            #先在集合查找
            temp2 = temp[0].split('.')
            print(temp2)
            s2 = {temp2[0]: temp[2]}
            retn=stu.find_one(s2)
            print(retn)
            if retn is None:
                print('None')
                str='None'.encode('gb2312')
                kwargs['socket'].send(str)
                kwargs['socket'].close()
                return
            if retn is not None:
                print('数据库里有')
                str='数据库里有'.encode('gb2312')
                kwargs['socket'].send(str)
                kwargs['socket'].close()
                return
        #0  save
        if temp[1]=='0':
            print("save")
            # 先在集合查找
            print(list(stu.find()))
            temp2 = temp[0].split('.')
            print(temp2)
            s2 = {temp2[0]: temp[2]}
            retn = stu.find_one(s2)
            print(retn)
            if retn is not None:
                print('已经保存了')
                str = '已经保存了'.encode('gb2312')
                kwargs['socket'].send(str)
                kwargs['socket'].close()
                return
            if retn is None:
                temp3=temp[0].split('.')
                print(temp3)
                s1 = {temp3[0]: temp[2]}
                s1_id = stu.insert_one(s1)
                retn = stu.find_one(s1)
                print(retn)
                if s1_id is not None:
                  print(type(s1_id))
                  print(type(s1_id.inserted_id))
                  print('ok')
                  str='ok'.encode('gb2312')
                  kwargs['socket'].send(str)
                  kwargs['socket'].close()
                  return

        # structin,=struct.unpack("i",data[0:4])
    # print(structin)
    # structnamelen, = struct.unpack("i", data[4:8])
    # print(structnamelen)
    # structname, = struct.unpack("p", data[8:structnamelen])
    # data=structname.decode("gb2312")
    # print(data)
    # structmd5len, = struct.unpack("i", data[structnamelen:structnamelen+4])
    # print(structmd5len)
    # structmd5, = struct.unpack("p", data[structnamelen+4:structmd5len])
    # data = structmd5.decode("gb2312")
    # print(data)


# sock_server = socket.socket(socket.AF_INET,socket.SOCK_STREAM,socket.IPPROTO_TCP)
# sock_server.bind(('192.168.2.186',0x6899))
# sock_server.listen(socket.SOMAXCONN)
# while True:
#     print('I am waiting for the client')
#     conn, addr = sock_server.accept()
#     # thread = threading.Thread(target=jonnys, args=(conn, addr))
#     data = conn.recv(1024)
#     print(data)
#     conn.sendall(str('<h1>welcome nginx</h1>'))
#     conn.close()

# client=pymongo.MongoClient("localhost", 27017)
# #获取数据库 test
# db=client.test
# #获取数据库集合
# stu=db.stu
# #创建一个字典
# s1={'name':'allen', 'age': 18}
# #获取键值对的 id
# s1_id = stu.insert_one(s1).inserted_id
# #获取一行
# s2=stu.find_one()
# print(s2)
# print(s1_id)
# print(stu.count())
# if __name__ == '__main__':
#     print(stu.count())
#     s1 = {'name': 'allen', 'age': 18}
#     s2 = {'name': 'allenboy', 'age': 19}
#     for i in range(0,30):
#         stu.remove(s2)
#     print(list(stu.find()))
    # #查获取id
    # s1_id = stu.insert_one(s1).inserted_id
    # s2_id = stu.insert_one(s2).inserted_id
    # print(s1_id)
    # temp=stu.find_one(s1)
    # print(temp)
    # print(type(temp))
    # print(stu.find(s2))
    # all = db.col.find()
    # print(jsonb.dumps(list(db.col.find({'name':'alen'}))))
    # print(stu.count())
    # print(type(all))
    # results = stu.find({'age': 20})
    # for result in results:
    #     print(result)
    # result = stu.find_one({'_id': ObjectId('5ae032631d41c8280dbdd167')})
    # print(result)
    # print("hhh")
    # temp = stu.find_one()
    # print(temp)
    # print(type(temp))
    # print(temp['name'])
    # result = []
    # for x in db.test.find():
    #     result.append(x)
    # print(result)
    # print(list(stu.find()))