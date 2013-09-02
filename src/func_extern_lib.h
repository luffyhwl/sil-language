/********************************************************************
˵��:			sil������ . ������չ֧�ֿ�
����ʱ��:	2013-8-29
����:			Ѧ�� 
��ϵ��ַ:	qq:308821698 ��http://t.qq.com/flysnowxg/��
*********************************************************************/
#pragma once
#include "base_define.h"
#include "code_gen.h"

void inital_internal_fun();
bool find_internal_function(const string& fun_name);
bool internel_fun_call(const string&fun_name,int param_count,vector<inst_value>& stk,int first_param);

class func_extern;
//����ת�������ǿ����Զ���ģ�һ�������õļ�������
typedef bool (*param_invert_rule_t)(int,vector<inst_value>&,int,func_extern*);
//����������ת������Ĭ�Ϲ�������
bool default_param_invert_rule(int param_count,vector<inst_value>& stk,int first_param,func_extern* pfe);
//���ڼӼ��˳������ò�����Ӧ�������������� ��int��������Ϊfloat��float����������string
bool internal_param_invert_rule(int param_count,vector<inst_value>& stk,int first_param,func_extern* pfe);

class func_extern
{
public:
	func_extern(const string& fun_name,param_invert_rule_t invert_f=default_param_invert_rule,e_inst_value_t return_t=eiv_invalid)
		:m_fun_name(fun_name),m_return_t(return_t),m_invert_f(invert_f){}
	bool can_invert_params(int param_count,vector<inst_value>& stk,int first_param)
	{
		return (*m_invert_f)(param_count,stk,first_param,this);
	}
	virtual void operator()(int param_count,vector<inst_value>& stk,int first_param)=0;
	const string m_fun_name;
	e_inst_value_t m_return_t;
	vector<e_inst_value_t> m_params_t;
	param_invert_rule_t m_invert_f;
};

class weak_param{};
template<typename T> T invert_param_to(vector<inst_value>& stk,int index=0);

template<typename T>
struct type_to_eiv
{
	static const e_inst_value_t eiv=eiv_invalid;
};
template<> struct type_to_eiv<int>
{
	static const e_inst_value_t eiv=eiv_int;
};
template<> struct type_to_eiv<double>
{
	static const e_inst_value_t eiv=eiv_float;
};
template<> struct type_to_eiv<string>
{
	static const e_inst_value_t eiv=eiv_string;
};

//��չ�����ı�ʾ
template<typename ResultT,
	typename P1=weak_param,typename P2=weak_param,
	typename P3=weak_param,typename P4=weak_param,
	typename P5=weak_param,typename P6=weak_param>
class func_extern_impl :public func_extern
{
public:
	typedef ResultT (*fun0_t)() ;
	typedef ResultT (*fun1_t)(P1) ;
	typedef ResultT (*fun2_t)(P1,P2) ;
	typedef ResultT (*fun3_t)(P1,P2,P3) ;
	typedef ResultT (*fun4_t)(P1,P2,P3,P4) ;
	typedef ResultT (*fun5_t)(P1,P2,P3,P4,P5) ;
	typedef ResultT (*fun6_t)(P1,P2,P3,P4,P5,P6) ;
private:
	int m_fun_index;
	union{
		fun0_t _0;
		fun1_t _1;
		fun2_t _2;
		fun3_t _3;
		fun4_t _4;
		fun5_t _5;
		fun6_t _6;
	}m_fun;
public:
	void init_params()
	{
		m_return_t=type_to_eiv<ResultT>::eiv;
		if(type_to_eiv<P1>::eiv!=eiv_invalid) m_params_t.push_back(type_to_eiv<P1>::eiv);
		if(type_to_eiv<P2>::eiv!=eiv_invalid) m_params_t.push_back(type_to_eiv<P2>::eiv);
		if(type_to_eiv<P3>::eiv!=eiv_invalid) m_params_t.push_back(type_to_eiv<P3>::eiv);
		if(type_to_eiv<P4>::eiv!=eiv_invalid) m_params_t.push_back(type_to_eiv<P4>::eiv);
		if(type_to_eiv<P5>::eiv!=eiv_invalid) m_params_t.push_back(type_to_eiv<P5>::eiv);
		if(type_to_eiv<P6>::eiv!=eiv_invalid) m_params_t.push_back(type_to_eiv<P6>::eiv);
	}
#define FUNC_EXTERN_IMPL_CONSTRUCTOR(num) \
	func_extern_impl(const string& fun_name,fun##num##_t pf,param_invert_rule_t invert_f)\
	:func_extern(fun_name,invert_f)\
	{\
		m_fun._##num=pf;\
		m_fun_index=##num;\
		init_params();\
	}
	FUNC_EXTERN_IMPL_CONSTRUCTOR(0);
	FUNC_EXTERN_IMPL_CONSTRUCTOR(1);
	FUNC_EXTERN_IMPL_CONSTRUCTOR(2);
	FUNC_EXTERN_IMPL_CONSTRUCTOR(3);
	FUNC_EXTERN_IMPL_CONSTRUCTOR(4);
	FUNC_EXTERN_IMPL_CONSTRUCTOR(5);
	FUNC_EXTERN_IMPL_CONSTRUCTOR(6);

	template<typename ResultT,typename P1,typename P2,typename P3,typename P4,typename P5,typename P6>
	ResultT call_wrap(P1 p1,P2 p2,P3 p3,P4 p4,P5 p5,P6 p6)
	{
		if(m_fun_index==0) return m_fun._0();
		if(m_fun_index==1) return m_fun._1(p1);
		if(m_fun_index==2) return m_fun._2(p1,p2);
		if(m_fun_index==3) return m_fun._3(p1,p2,p3);
		if(m_fun_index==4) return m_fun._4(p1,p2,p3,p4);
		if(m_fun_index==5) return m_fun._5(p1,p2,p3,p4,p5);
		if(m_fun_index==6) return m_fun._6(p1,p2,p3,p4,p5,p6);
		return ResultT();
	}

	virtual void operator()(int param_count,vector<inst_value>& stk,int first_param)
	{
		stk[first_param] =call_wrap<ResultT>(
			invert_param_to<P1>(stk,first_param),
			invert_param_to<P2>(stk,first_param+1),
			invert_param_to<P3>(stk,first_param+2),
			invert_param_to<P4>(stk,first_param+3),
			invert_param_to<P5>(stk,first_param+4),
			invert_param_to<P6>(stk,first_param+5)
			);
	}
};

//��չ�������Ϲ������͵��÷�װ
class extern_fun_manager
{
public:
	bool register_fun(shared_ptr<func_extern> sp_fun);
	bool find(const string& fun_name);
	bool call(const string&fun_name,int param_count,vector<inst_value>& stk,int first_param);
	void list_function();
private:
	map<string,vector<shared_ptr<func_extern> > > m_funs;
};
extern_fun_manager* funs_manager();

//ע����չ������sil
template<typename ResultT>
void register_function(const string&fun_name,ResultT (*pf)(),param_invert_rule_t invert_f=default_param_invert_rule)
{
	funs_manager()->register_fun(shared_ptr<func_extern_impl<ResultT> >(new func_extern_impl<ResultT>(fun_name,pf,invert_f)));
}
template<typename ResultT,typename P1>
void register_function(const string&fun_name, ResultT (*pf)(P1),param_invert_rule_t invert_f=default_param_invert_rule)
{
	funs_manager()->register_fun(shared_ptr<func_extern_impl<ResultT,P1> >(new func_extern_impl<ResultT,P1>(fun_name,pf,invert_f)));
}
template<typename ResultT,typename P1,typename P2>
void register_function(const string&fun_name, ResultT (*pf)(P1,P2),param_invert_rule_t invert_f=default_param_invert_rule)
{
	funs_manager()->register_fun(shared_ptr<func_extern_impl<ResultT,P1,P2> >(new func_extern_impl<ResultT,P1,P2>(fun_name,pf,invert_f)));
}
template<typename ResultT,typename P1,typename P2,typename P3>
void register_function(const string&fun_name, ResultT (*pf)(P1,P2,P3),param_invert_rule_t invert_f=default_param_invert_rule)
{
	funs_manager()->register_fun(shared_ptr<func_extern_impl<ResultT,P1,P2,P3> >(new func_extern_impl<ResultT,P1,P2,P3>(fun_name,pf,invert_f)));
}
template<typename ResultT,typename P1,typename P2,typename P3,typename P4>
void register_function(const string&fun_name, ResultT (*pf)(P1,P2,P3,P4),param_invert_rule_t invert_f=default_param_invert_rule)
{
	funs_manager()->register_fun(shared_ptr<func_extern_impl<ResultT,P1,P2,P3,P4> >(new func_extern_impl<ResultT,P1,P2,P3,P4>(fun_name,pf,invert_f)));
}
template<typename ResultT,typename P1,typename P2,typename P3,typename P4,typename P5>
void register_function(const string&fun_name, ResultT (*pf)(P1,P2,P3,P4,P5),param_invert_rule_t invert_f=default_param_invert_rule)
{
	funs_manager()->register_fun(shared_ptr<func_extern_impl<ResultT,P1,P2,P3,P4,P5> >(new func_extern_impl<ResultT,P1,P2,P3,P4,P5>(fun_name,pf,invert_f)));
}
template<typename ResultT,typename P1,typename P2,typename P3,typename P4,typename P5,typename P6>
void register_function(const string&fun_name, ResultT (*pf)(P1,P2,P3,P4,P5,P6),param_invert_rule_t invert_f=default_param_invert_rule)
{
	funs_manager()->register_fun(shared_ptr<func_extern_impl<ResultT,P1,P2,P3,P4,P5,P6> >(new func_extern_impl<ResultT,P1,P2,P3,P4,P5,P6>(fun_name,pf,invert_f)));
}