/********************************************************************
˵��:			sil������ . ������չ֧�ֿ�
����ʱ��:	2013-8-29
����:			Ѧ�� 
��ϵ��ַ:	qq:308821698 ��http://t.qq.com/flysnowxg/��
*********************************************************************/
#include "func_extern_lib.h"
e_inst_value_t type_to_eiv<int>::eiv=eiv_int;
e_inst_value_t type_to_eiv<double>::eiv=eiv_float;
e_inst_value_t type_to_eiv<string>::eiv=eiv_string;

//����������ת������Ĭ�Ϲ�������
bool default_param_invert_rule(int param_count,vector<inst_value>& stk,int first_param,func_extern* pfe)
{
	for(int count_i=0;count_i<param_count;count_i++)
	{
		if(!stk[first_param+count_i].can_invert_to(pfe->m_params_t[count_i])) return false;
	}
	return true;
}
//���ڼӼ��˳������ò�����Ӧ�������������� ��int��������Ϊfloat��float����������string
bool internal_param_invert_rule(int param_count,vector<inst_value>& stk,int first_param,func_extern* pfe)
{
	for(int count_i=0;count_i<param_count;count_i++)
	{
		e_inst_value_t real_param_t=stk[first_param+count_i].m_type;
		e_inst_value_t form_param_t=pfe->m_params_t[count_i];
		if(real_param_t>form_param_t) return false;
	}
	return true;
}

template<> weak_param invert_param_to<weak_param>(vector<inst_value>& stk,int index)
{
	return weak_param();
}
template<> int invert_param_to<int>(vector<inst_value>& stk,int index)
{
	return stk[index].to_int();
}
template<> double  invert_param_to<double>(vector<inst_value>& stk,int index)
{
	return stk[index].to_float();
}
template<> string invert_param_to<string>(vector<inst_value>& stk,int index)
{
	return stk[index].to_string();
}

bool extern_fun_manager::register_fun(shared_ptr<func_extern> sp_fun)
{
	m_funs[sp_fun->m_fun_name].push_back(sp_fun);
	return true;
}

bool extern_fun_manager::find(const string& fun_name)
{
	map<string,vector<shared_ptr<func_extern> > >::iterator it=m_funs.find(fun_name);
	if(it!=m_funs.end()) return true;
	else return false;
}

bool extern_fun_manager::call(const string&fun_name,int param_count,vector<inst_value>& stk,int first_param)
{
	//�����㷨:
	//	�ȽϺ������õ���ѡ��������
	//	�Ƚ��βθ�����ȥ������������ƥ���
	//	�Ƚ�ʵ�κ��βΣ�����Ƿ�����ȫ���ϵ�,����ҵ��������Ҳ�����
	//	��ʵ�ν�������ת�������ҵ�һ����ƥ��ĺ���,����ҵ��������Ҳ�����
	//	�������
	map<string,vector<shared_ptr<func_extern> > >::iterator it=m_funs.find(fun_name);
	if(it==m_funs.end()) return false;
	vector<shared_ptr<func_extern> > funs=it->second;
	for(vector<shared_ptr<func_extern> >::iterator it=funs.begin();it!=funs.end();)
	{
		if((*it)->m_params_t.size()!=param_count) it=funs.erase(it);
		else it++;
	}
	for(vector<shared_ptr<func_extern> >::iterator it=funs.begin();it!=funs.end();it++)
	{
		int count_i=0;
		for(;count_i<param_count;count_i++)
		{
			if(stk[first_param+count_i].m_type!=(*it)->m_params_t[count_i]) break;
		}
		if(count_i==param_count) 
		{
			(**it)(param_count,stk,first_param);
			return true;
		}
	}
	for(vector<shared_ptr<func_extern> >::iterator it=funs.begin();it!=funs.end();it++)
	{
		if((*it)->can_invert_params(param_count,stk,first_param))
		{
			(**it)(param_count,stk,first_param);
			return true;
		}
	}
	return false;
}

void extern_fun_manager::list_function()
{
	for(map<string,vector<shared_ptr<func_extern> > >::iterator it=m_funs.begin();it!=m_funs.end();it++)
	{
		printf("kernel#  %s\n",it->first.c_str());
	}
}

extern_fun_manager* funs_manager()
{
	static extern_fun_manager s_manager;
	return &s_manager;
}

bool find_internal_function(const string& fun_name)
{
	if(funs_manager()->find(fun_name)) return true;
	return false;
}

bool internel_fun_call(const string&fun_name,int param_count,vector<inst_value>& stk,int first_param)
{
	return funs_manager()->call(fun_name,param_count,stk,first_param);
}
