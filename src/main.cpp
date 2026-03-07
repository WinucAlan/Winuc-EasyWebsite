#include <bits/stdc++.h>
#include <winsock2.h> 
#define PORT 8888
#define  BUFFER_SIZE 4196
using namespace std;
struct sockaddr_in client_addr;
SOCKET server_socket;
int client_addr_len;
char buf[BUFFER_SIZE+100];
SOCKET client_socket;
const std::unordered_map<std::string, std::string> EXT_TO_CONTENT_TYPE = {
	{"txt",    "text/plain; charset=utf-8"},
	{"html",   "text/html; charset=utf-8"},
	{"htm",    "text/html; charset=utf-8"},
	{"css",    "text/css"},
	{"js",     "application/javascript"},
	{"json",   "application/json; charset=utf-8"},
	{"xml",    "text/xml; charset=utf-8"},
	{"csv",    "text/csv; charset=utf-8"},
	{"md",     "text/markdown; charset=utf-8"},
	{"yaml",   "application/x-yaml"},
	{"yml",    "application/x-yaml"},
	{"ini",    "text/plain; charset=utf-8"},
	{"conf",   "text/plain; charset=utf-8"},
	{"c",      "text/x-csrc; charset=utf-8"},
	{"cpp",    "text/x-c++src; charset=utf-8"},
	{"h",      "text/x-chdr; charset=utf-8"},
	{"hpp",    "text/x-c++hdr; charset=utf-8"},
	{"java",   "text/x-java-source; charset=utf-8"},
	{"py",     "text/x-python; charset=utf-8"},
	{"php",    "application/x-httpd-php"},
	{"go",     "text/x-go; charset=utf-8"},
	{"rs",     "text/x-rust; charset=utf-8"},
	{"swift",  "text/x-swift; charset=utf-8"},
	{"kotlin", "text/x-kotlin; charset=utf-8"},
	{"ts",     "application/typescript"},
	{"vue",    "application/x-vue"},
	{"sh",     "application/x-sh"},
	{"bat",    "text/plain; charset=utf-8"},
	{"ps1",    "text/plain; charset=utf-8"},
	{"sql",    "text/x-sql; charset=utf-8"},
	{"ruby",   "text/x-ruby; charset=utf-8"},
	{"perl",   "text/x-perl; charset=utf-8"},
	{"lua",    "text/x-lua; charset=utf-8"},
	{"dart",   "text/x-dart; charset=utf-8"},
	{"asm",    "text/x-asm; charset=utf-8"},
	{"cmake",  "text/x-cmake; charset=utf-8"},
	{"jpg",    "image/jpeg"},
	{"jpeg",   "image/jpeg"},
	{"png",    "image/png"},
	{"gif",    "image/gif"},
	{"webp",   "image/webp"},
	{"svg",    "image/svg+xml"},
	{"bmp",    "image/bmp"},
	{"ico",    "image/x-icon"},
	{"tiff",   "image/tiff"},
	{"tif",    "image/tiff"},
	{"heic",   "image/heic"},                  // 苹果HEIC图片
	{"psd",    "image/vnd.adobe.photoshop"},   // PSD文件
	{"ai",     "application/postscript"},      // AI矢量图
	{"eps",    "application/postscript"},      // EPS矢量图
	{"mp3",    "audio/mpeg"},
	{"wav",    "audio/wav"},
	{"ogg",    "audio/ogg"},
	{"flac",   "audio/flac"},
	{"aac",    "audio/aac"},
	{"m4a",    "audio/mp4"},
	{"wma",    "audio/x-ms-wma"},
	{"mid",    "audio/midi"},                  // MIDI音频
	{"opus",   "audio/opus"},                  // OPUS音频
	{"mp4",    "video/mp4"},
	{"avi",    "video/x-msvideo"},
	{"mov",    "video/quicktime"},
	{"wmv",    "video/x-ms-wmv"},
	{"flv",    "video/x-flv"},
	{"mkv",    "video/x-matroska"},
	{"webm",   "video/webm"},
	{"mpeg",   "video/mpeg"},
	{"mpg",    "video/mpeg"},
	{"3gp",    "video/3gpp"},
	{"mts",    "video/mp2t"},
	{"vob",    "video/x-ms-vob"},
	{"rmvb",   "application/vnd.rn-realmedia-vbr"},
	{"pdf",    "application/pdf"},
	{"doc",    "application/msword"},
	{"docx",   "application/vnd.openxmlformats-officedocument.wordprocessingml.document"},
	{"xls",    "application/vnd.ms-excel"},
	{"xlsx",   "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet"},
	{"ppt",    "application/vnd.ms-powerpoint"},
	{"pptx",   "application/vnd.openxmlformats-officedocument.presentationml.presentation"},
	{"odt",    "application/vnd.oasis.opendocument.text"},
	{"ods",    "application/vnd.oasis.opendocument.spreadsheet"},
	{"odp",    "application/vnd.oasis.opendocument.presentation"},
	{"rtf",    "application/rtf"},
	{"pages",  "application/x-iwork-pages-sffpages"},
	{"numbers","application/x-iwork-numbers-sffnumbers"},
	{"key",    "application/x-iwork-keynote-sffkey"},
	{"epub",   "application/epub+zip"},
	{"mobi",   "application/x-mobipocket-ebook"},
	{"azw3",   "application/x-mobipocket-ebook"},
	{"fb2",    "application/x-fictionbook+xml"},
	{"chm",    "application/x-chm"},
	{"pdb",    "application/x-palm-database"},
	{"zip",    "application/zip"},
	{"rar",    "application/x-rar-compressed"},
	{"7z",     "application/x-7z-compressed"},
	{"tar",    "application/x-tar"},
	{"gz",     "application/gzip"},
	{"bz2",    "application/x-bzip2"},
	{"xz",     "application/x-xz"},
	{"cab",    "application/vnd.ms-cab-compressed"},
	{"z",      "application/x-compress"},
	{"lzma",   "application/x-lzma"},
	{"iso",    "application/x-iso9660-image"},
	{"msi",    "application/x-msi"},
	{"apk",    "application/vnd.android.package-archive"},
	{"deb",    "application/x-deb"},
	{"rpm",    "application/x-rpm"},
	{"db",     "application/octet-stream"},
	{"sqlite", "application/x-sqlite3"},
	{"dbf",    "application/x-dbf"},
	{"mdb",    "application/x-msaccess"},
	{"accdb",  "application/x-msaccess"},
	{"ttf",    "font/ttf"},
	{"otf",    "font/otf"},
	{"woff",   "font/woff"},
	{"woff2",  "font/woff2"},
	{"eot",    "application/vnd.ms-fontobject"},
	{"dwg",    "application/acad"},
	{"dxf",    "application/dxf"},
	{"stl",    "application/sla"},
	{"step",   "application/step"},
	{"iges",   "application/iges"},
	{"gpg",    "application/pgp-encrypted"},   // GPG加密文件
	{"p12",    "application/x-pkcs12"},        // PKCS12证书
	{"cer",    "application/x-x509-ca-cert"},  // 证书文件
	{"asc",    "text/plain; charset=utf-8"},   // 签名文件
	{"torrent","application/x-bittorrent"},
	{"log",    "text/plain; charset=utf-8"},
	{"cert",   "application/x-x509-ca-cert"},
	{"pem",    "application/x-pem-file"},
	{"m3u",    "audio/x-mpegurl"},
	{"m3u8",   "application/x-mpegURL"},
	{"wv",     "audio/x-wavpack"},
	{"aiff",   "audio/x-aiff"},
	{"m4v",    "video/mp4"},
	{"ics",    "text/calendar; charset=utf-8"},
	{"vcard",  "text/vcard; charset=utf-8"},
	{"vcf",    "text/vcard; charset=utf-8"},
	{"srt",    "text/plain; charset=utf-8"},
	{"ass",    "text/plain; charset=utf-8"},
	{"vtt",    "text/vtt; charset=utf-8"},
	{"xhtml",  "application/xhtml+xml; charset=utf-8"},
	{"mathml", "application/mathml+xml; charset=utf-8"},
	{"rdf",    "application/rdf+xml; charset=utf-8"},
	{"xsd",    "application/xml-schema; charset=utf-8"},
	{"dtd",    "application/xml-dtd; charset=utf-8"},
	{"xsl",    "application/xml; charset=utf-8"},
	{"xslt",   "application/xslt+xml; charset=utf-8"},
	{"xlf",    "application/x-xliff+xml; charset=utf-8"},
	{"mbox",   "application/mbox"},
	{"eml",    "message/rfc822"},
	{"crt",    "application/x-x509-ca-cert"},
	{"crl",    "application/pkix-crl"},
	{"der",    "application/x-x509-ca-cert"},
	{"p7b",    "application/x-pkcs7-certificates"},
	{"p7c",    "application/x-pkcs7-mime"},
	{"p8",     "application/x-pkcs8"},
	{"sct",    "application/ocsp-request"},
	{"tsp",    "application/timestamp-response"},
	{"po",     "text/x-gettext-translation; charset=utf-8"},
	{"pot",    "text/x-gettext-translation-template; charset=utf-8"},
	{"mo",     "application/x-gettext-translation"},
	{"diff",   "text/x-diff; charset=utf-8"},
	{"patch",  "text/x-diff; charset=utf-8"},
	{"manifest","text/cache-manifest; charset=utf-8"},
	{"wasm",   "application/wasm"},
	{"wgsl",   "text/wgsl; charset=utf-8"},
	{"glsl",   "text/x-glsl; charset=utf-8"},
	{"frag",   "text/x-glsl; charset=utf-8"},
	{"vert",   "text/x-glsl; charset=utf-8"},
	{"comp",   "text/x-glsl; charset=utf-8"},
	
	{"default","application/octet-stream"}
};
int IsTcpDataAvailable(SOCKET s, int timeout_ms)
{
	fd_set read_fds;
	struct timeval timeout;
	// 初始化fd_set，只关注目标套接字
	FD_ZERO(&read_fds);
	FD_SET(s, &read_fds);
	// 设置超时时间
	timeout.tv_sec = timeout_ms / 1000;
	timeout.tv_usec = (timeout_ms % 1000) * 1000;
	// 调用select，只检查读状态
	int ret = select(0, &read_fds, NULL, NULL, &timeout);
	if (ret == SOCKET_ERROR)
	{
		// 出错，打印错误码
		printf("select error: %d\n", WSAGetLastError());
		return -1;
	}
	else if (ret > 0) // 返回值>0表示有套接字就绪，检查目标套接字是否在就绪集合中
		if (FD_ISSET(s, &read_fds))
			return 1; // 有数据可读
	// 超时，无数据可读
	return 0;
}
bool canReadFile(string s)
{
	ifstream fin(s);
	if(fin.is_open())
	{
		fin.close();
		return 1;
	}
	return 0;
}
string getFileExtension(string path)
{
	int pos=path.find_last_of('.');
	if(pos==string::npos)
		return "";
	string res="";
	for(int i=pos+1;i<path.size();i++)
		res+=tolower(path[i]);
	return res;
}
string getContentTypeByExtension(string filePath)
{
	string ext=getFileExtension(filePath);
	auto it=EXT_TO_CONTENT_TYPE.find(ext);
	if (it!=EXT_TO_CONTENT_TYPE.end())
		return it->second;
	return EXT_TO_CONTENT_TYPE.at("default");
}
int main()
{
	WORD winsock_version = MAKEWORD(2,2);
	WSADATA wsa_data;
	if (WSAStartup(winsock_version, &wsa_data) != 0)
	{
		printf("Failed to init socket dll!\n");
		return 1;
	}
	server_socket= socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (server_socket == INVALID_SOCKET)
	{
		printf("Failed to create server socket!\n");
		return 2;
	}
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(server_socket, (LPSOCKADDR)&server_addr, sizeof(server_addr)) == SOCKET_ERROR)
	{
		printf("Failed to bind port!\n");
		return 3;
	}
	if (listen(server_socket, 10))
	{
		printf("Failed to listen!\n");
		return 4;
	}
	client_addr_len = sizeof(client_addr);
	printf("Wait for connecting...\n");
	while(1)
	{
		client_socket = accept(server_socket, (SOCKADDR*)&client_addr, &client_addr_len);
		printf("[info]connect to new client: IP=%s\n" , inet_ntoa(client_addr.sin_addr));
		if (client_socket == INVALID_SOCKET)
		{
			printf("Failed to accept!\n");
			continue;
		}
		string childLabel;
		if(IsTcpDataAvailable(client_socket,1000))
		{
			memset(buf,0,sizeof(buf));
			recv(client_socket,buf,BUFFER_SIZE,0);
			printf("%s\n",buf);
			int startPos=string(buf).find("GET");
			if(startPos==string::npos)
			{
				printf("ERROR:Undefined request\n");
				send(client_socket,"HTTP/1.1 404 Not Found",sizeof("HTTP/1.1 404 Not Found"),0);
				closesocket(client_socket);
				continue;
			}
			for(int i=startPos+4;i<strlen(buf)&&buf[i]!=' ';i++) childLabel+=buf[i];
		}
		bool flag=0;
		string fileName,type;
		//自动查找
		if(canReadFile("webpage"+childLabel))
		{
			flag=1;
			fileName="webpage"+childLabel;
			type=getContentTypeByExtension(childLabel);
		}
		else if(canReadFile("webpage"+childLabel+".html"))
		{
			flag=1;
			fileName="webpage"+childLabel+".html";
			type="text/html; charset=utf-8";
		}
		else
		{
			//加载网页列表
			ifstream lists("list.txt");
			string child;
			while(lists>>child>>type>>fileName)
			{
				if(child==childLabel)
				{
					flag=1;
					break;
				}
			}
			lists.close();
		}
		if(!flag)
		{
			printf("ERROR:Undefined child:%s\n",childLabel.c_str());
			send(client_socket,"HTTP/1.1 404 Not Found",sizeof("HTTP/1.1 404 Not Found"),0);
			closesocket(client_socket);
			continue;
		}
		//加载HTML源码 
		string response="HTTP/1.1 200 OK\r\nContent-Type: "+type+"\r\nContent-Length: "+to_string(filesystem::file_size(fileName))+"\r\n\r\n"; 
		ifstream fin(fileName,ios::binary);
		char c;
		while(fin.get(c))
		{
			response+=c;
			if(response.size()>BUFFER_SIZE)
			{
				send(client_socket,response.c_str(),response.size(),0);
				response.clear();
			}
		}
		fin.close();
		if(!response.empty())
			send(client_socket,response.c_str(),response.size(),0);
//		Sleep(100);
		closesocket(client_socket);
	}
	closesocket(server_socket);
	WSACleanup();
	return 0;
}
