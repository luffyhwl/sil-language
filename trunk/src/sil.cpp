/********************************************************************
˵��:			sil������ .
����ʱ��:	2013-8-31
����:			Ѧ�� 
��ϵ��ַ:	qq:308821698 ��http://t.qq.com/flysnowxg/��
*********************************************************************/
#include "sil.h"
#include "normal_helper.cpp"
#include "word_parser.cpp"
#include "grammar_parser.cpp"
#include "symbol_manager.cpp"
#include "code_gen.cpp"
#include "interpret.cpp"
#include "func_extern_lib.cpp"
#include "function_extern.cpp"

bool init_sil()
{
	inital_internal_fun();
	return true;
}
void enter_sil_consle()
{
	//ִ��һ��sil�ű��������ô��ڱ������ɫ ������һ����ȡ�����ַ�������ֵ��ѭ��
	sil_eval(
		//"bat(\"assoc .sil=sil�ű�>nul\nftype sil�ű�=notepad.exe %%1 %%*>nul\");"
		"bat(\"title sil\ncolor 5f\");\
		while(true){\
			print(\"sil>\");\
			var code=read();\
			eval(code);\
			print(\"\n\");\
		}");
}