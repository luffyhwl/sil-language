/********************************************************************
˵��:			sil������
����ʱ��:	2013-8-30
����:			Ѧ�� 
��ϵ��ַ:	qq:308821698 ��http://t.qq.com/flysnowxg/��
*********************************************************************/
#include "../src/sil.h"

int main(int argc, char* argv[])
{
	init_sil();
	//�������һ��Ҫ���͵��ļ�������ִ���ļ����ɣ��������������н�����
	if(argc<2)
	{
		printf("sil v0.1(����ʱ��:%s)author:xuegang[qq:308821698]\n",__TIMESTAMP__ );
		printf("����  help();  ����ʾ������Ϣ\n");
		interpret::is_output_last_value(true);
		enter_sil_consle();
	}
	else
	{
		sil_load(argv[1]);
	}
	return 0;
}