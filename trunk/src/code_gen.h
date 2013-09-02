/********************************************************************
˵��:			sil������ . ����������
����ʱ��:	2013-8-23
����:			Ѧ�� 
��ϵ��ַ:	qq:308821698 ��http://t.qq.com/flysnowxg/��
*********************************************************************/
#pragma once
#include "base_define.h"
//�����ռ�   ����ռ� ȫ�����ݿռ� ��ջ�ռ�
enum e_instruction
{
	e_load_const,//(���ݶ�ջ�ռ�) ���س�����ջ��
	e_load,//(���ݶ�ջ�ռ� ȫ�����ݿռ�) �������ļ��ص�ջ��
	e_save,//(���ݶ�ջ�ռ� ȫ�����ݿռ�) ��ջ����ֵд�����
	e_pop,//(���ݶ�ջ�ռ�) ��reg_sb��С
	e_call,//(���ݴ���ռ� ��ջ�ռ�) ���ú���
	e_ret,//(���ݴ���ռ� ��ջ�ռ�) �Ӻ������÷���
	e_jmp,//(���ݴ���ռ�) ��������ת
	e_jpc,//(���ݴ���ռ�) ջ��Ԫ��Ϊ0ʱ��ת
	e_exit,//�˳�������
};
enum e_addr_type
{
	eab_invalid,
	eab_absolute_ip,//����Ѱַ(����ռ�)
	eab_relat_ip,//�����ipѰַ(����ռ�)
	eab_reg_sb,//�����sb�Ĵ���Ѱַ
	eab_global_data,
};
enum e_inst_value_t
{
	eiv_invalid,
	eiv_int,
	eiv_float,
	eiv_string
};
class inst_value
{
public:
	inst_value(int value=0):m_type(eiv_int),m_int_value(value),m_float_value(0){}
	inst_value(double value):m_type(eiv_float),m_int_value(0),m_float_value(value){}
	inst_value(const string& value):m_type(eiv_string),m_int_value(0),m_float_value(0),m_string_value(value){}
	bool can_invert_to(e_inst_value_t);
	int to_int();
	double to_float();
	string to_string();
	e_inst_value_t m_type;
	int m_int_value;
	double m_float_value;
	string m_string_value;
};

class _instruction
{
public:
	string to_string();
	int m_index;//
	e_instruction m_type;
	e_addr_type m_addr_t;//
	int m_addr;
	inst_value m_value;
};

class code_gen
{
public:
	code_gen(void);
	~code_gen(void){}
	_instruction* gen(e_instruction inst_type,e_addr_type base,int addr,inst_value value);
	int get_new_code_addr();
	vector<_instruction> m_codes;
};

code_gen* get_global_gener();
code_gen* get_top_gener();
int get_top_gener_id();//0--Ϊ���պϲ�����Ŀռ䣬1--Ϊȫ�ֱ�����������Ŀռ�
code_gen* create_gener();
void pop_gener();
int merge_code();
void print_code();

int alloc_global_data_space();
int get_new_code_addr(bool b_global=false);
_instruction*  gen_code(e_instruction inst_type,e_addr_type base=eab_invalid,int addr=0,inst_value value=0,bool b_global=false);
bool gen_fun_call(const string& fun_name,int param_count,int& stk_index);
_instruction*  gen_pop_instruction(int& stk_index,int pop_count=1);
void gen_load_const_instruction(int& stk_index,inst_value value);
