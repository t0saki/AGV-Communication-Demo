//#include "pch.h"
#include<iostream>
#include<winsock.h>
#include<cstring>
#include<string>
#include<atlstr.h>

#include "Resource.h"
#include "MFCCommDlg.h"
#pragma comment(lib,"ws2_32.lib")
using namespace std;
void initialization();





void Cstring2Char(CString src, char* dst)
{
	DWORD dwMinSize;
	dwMinSize = WideCharToMultiByte(CP_ACP, NULL, src, -1, NULL, 0, NULL, FALSE);
	char* pp = new char[dwMinSize];
	WideCharToMultiByte(CP_OEMCP, NULL, src, -1, pp, dwMinSize, NULL, FALSE);
	strcpy(dst, pp);
	delete[] pp;
}



//定义长度变量
int send_len = 0;
int recv_len = 0;
//定义发送缓冲区和接受缓冲区
char send_buf[100];
char recv_buf[100];

//定义服务端套接字，接受请求套接字
SOCKET s_server;
SOCKET s_accept;

void closes() {
	//关闭套接字
	closesocket(s_server);
	closesocket(s_accept);
	//释放DLL资源
	WSACleanup();
}


CString setclient(CString addr, int port) {
	CString ret = _T("");
	//服务端地址客户端地址
	SOCKADDR_IN server_addr;
	initialization();
	//填充服务端信息
	char saddr[255];
	Cstring2Char(addr,saddr);
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.S_un.S_addr = inet_addr(saddr);
	server_addr.sin_port = htons(port);
	//创建套接字
	s_server = socket(AF_INET, SOCK_STREAM, 0);
	if (connect(s_server, (SOCKADDR*)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
		ret+= "服务器连接失败！\r\n";
		closes();
	}
	else {
		ret += "服务器连接成功！\r\n";
	}
	return ret;

}

CString client(CString input) {

	CString ret = _T(""); 
	Cstring2Char(input, send_buf);
	//cin >> send_buf;
	send_len = send(s_server, send_buf, 100, 0);
	if (send_len < 0) {
		ret += "发送失败！\r\n";
		return ret;
	}
	ret += _T("客户端信息：");
	ret += input;
	//发送,接收数据
	/**while (1) {
		//ret += "请输入发送信息:\r\n";
		Cstring2Char(input, send_buf);
		//cin >> send_buf;
		send_len = send(s_server, send_buf, 100, 0);
		if (send_len < 0) {
			ret += "发送失败！\r\n";
			break;
		}
		recv_len = recv(s_server, recv_buf, 100, 0);
		if (recv_len < 0) {
			ret += "接受失败！\r\n";
			break;
		}
		else {
			//cout << "服务端信息:" << recv_buf << endl;
			CString tmp = ((CString)"服务端信息:" + (CString)recv_buf + "\r\n");
			ret += tmp;
		}

	}**/
	return ret;
}
CString clientrecv() {
	CString ret = _T(""); recv_len = recv(s_server, recv_buf, 100, 0);
	if (recv_len < 0) {
		ret = "接受失败！\r\n";
		return ret;
	}
	else {
		//cout << "服务端信息:" << recv_buf << endl;
		CString tmp = ((CString)"服务端信息：" + (CString)recv_buf + "\r\n");
		ret += tmp;
	}
	return ret;
}



CString setserver(int port) {
	//MsgList.AddString(_T("Msg"));
	int len = 0;
	CString ret= _T("");
	//服务端地址客户端地址
	SOCKADDR_IN server_addr;
	SOCKADDR_IN accept_addr;
	initialization();
	//填充服务端信息
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(port);
	//创建套接字
	s_server = socket(AF_INET, SOCK_STREAM, 0);
	if (bind(s_server, (SOCKADDR*)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
		closes();
		ret+= "套接字绑定失败！\r\n";
	}
	else {
		ret += "套接字绑定成功！\r\n";
	}
	//设置套接字为监听状态
	if (listen(s_server, SOMAXCONN) < 0) {
		closes();
		ret += "设置监听状态失败！\r\n";
	}
	else {
		ret += "设置监听状态成功！\r\n";
	}
	cout << "服务端正在监听连接，请稍候....\r\n" << endl;
	//接受连接请求
	len = sizeof(SOCKADDR);
	s_accept = accept(s_server, (SOCKADDR*)&accept_addr, &len);
	if (s_accept == SOCKET_ERROR) {
		ret += "连接失败！\r\n";
		closes();
		return ret;
	}
	//ret += "连接建立，准备发送数据\r\n";
	//接收数据
	return ret;
}

CString serverrecv() {
	CString ret;		
	recv_len = recv(s_accept, recv_buf, 100, 0);
	if (recv_len < 0) {
		ret += "接受失败！\r\n";
		return ret;
	}
	else {
		CString tmp = (CString)"客户端信息：" + (CString)recv_buf + "\r\n";
		ret += tmp;
	}
	return ret;
}

CString server(CString input) {
	CString ret;
	/**while (1) {
		//cout << "请输入回复信息:";
		//cin >> send_buf;
		Cstring2Char(input, send_buf);
		send_len = send(s_accept, send_buf, 100, 0);
		if (send_len < 0) {
			ret += "发送失败！\r\n";
			break;
		}
		recv_len = recv(s_accept, recv_buf, 100, 0);
		if (recv_len < 0) {
			ret += "接受失败！\r\n";
			break;
		}
		else {
			CString tmp = (CString)"客户端信息:" + (CString)recv_buf + "\r\n";
			ret += tmp;
		}
	}**/		
	Cstring2Char(input, send_buf);
	send_len = send(s_accept, send_buf, 100, 0);
	if (send_len < 0) {
		ret += "发送失败！\r\n";
		return ret;
	}
	ret += _T("服务端信息：");
	ret += input;
	return ret;
}


void initialization() {
	//初始化套接字库
	WORD w_req = MAKEWORD(2, 2);//版本号
	WSADATA wsadata;
	int err;
	err = WSAStartup(w_req, &wsadata);
	if (err != 0) {
		cout << "初始化套接字库失败！" << endl;
	}
	else {
		cout << "初始化套接字库成功！" << endl;
	}
	//检测版本号
	if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2) {
		cout << "套接字库版本号不符！" << endl;
		WSACleanup();
	}
	else {
		cout << "套接字库版本正确！" << endl;
	}
	//填充服务端地址信息

}