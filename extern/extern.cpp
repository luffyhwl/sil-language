/********************************************************************
˵��:			sil������ . ��չ������
����ʱ��:	2013-8-31
����:			Ѧ�� 
��ϵ��ַ:	qq:308821698 ��http://t.qq.com/flysnowxg/��
*********************************************************************/
//����һ�����ӣ�չʾ�����ȥ��չsilȥ֧�ֶ��ļ����в���
//���Ȼᶨ��һЩ����sil�ӿڹ淶�ĺ���������sil�ľ��ޣ�silֻ֧�ֲ�����int float string ���������͵ĺ�����
//Ȼ�����register_function();ע�ắ��
//������file_rw.sil�ű��������ļ�
#include "../src/sil.h"
#pragma warning(disable:4311)
#pragma warning(disable:4312)
typedef int file_handle;
file_handle sil_fopen(string file_path,string open_mode)
{
	FILE* fp=fopen(file_path.c_str(),open_mode.c_str());
	return (file_handle)fp;
}
int sil_fcolse(file_handle file)
{
	return fclose((FILE*)file);
}
string sil_fread(file_handle file,int size)
{
	char* p_buf=new char[size+1];
	fread(p_buf,1,size,(FILE*)file);
	return p_buf;
}
bool sil_fwrite(file_handle file,string data)
{
	int size=fwrite(data.c_str(),1,data.size(),(FILE*)file);
	return size==data.size();
}
int sil_fseek(file_handle file,int mode,int offset)
{
	return fseek((FILE*)file,offset,mode);
}
int sil_ftell(file_handle file)
{
	return ftell((FILE*)file);
}
int main(int argc, char* argv[])
{
	printf("sil v0.1(����ʱ��:%s)author:xuegang[qq:308821698]\n",__TIMESTAMP__ );
	printf("��ֻ�Ǹ���������չʾ���ȥ��c++��չsil�ĺ�������\n");
	init_sil();
	register_function("fopen",sil_fopen);
	register_function("fclose",sil_fcolse);
	register_function("fread",sil_fread);
	register_function("fwrite",sil_fwrite);
	register_function("fseek",sil_fseek);
	register_function("ftell",sil_ftell);
	interpret::is_output_last_value(true);
	sil_load("../extern/file_rw.sil");
	enter_sil_consle();
	return 0;
}

