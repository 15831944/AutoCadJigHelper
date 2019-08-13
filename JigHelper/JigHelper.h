/**
 * @file    JigHelper.h
 * @brief   ����ͨ��jig��
 * @author  Gergul
 * @date    2018/10/29
 * Note:    
 */
#pragma once
#include <dbjig.h>
#include <functional>
#include <vector>
#include "SDBDumyJigEntity.h"

 //����jigʵ�庯��ԭ��
typedef Adesk::Boolean (*pfnUpdateJig)(class CJigHelper *pJigHelper, const AcGePoint3d &posCur, const AcGePoint3d &posLast);

//�����洢�ṹ
#define FUNC_UPDATE_JIG std::function<Adesk::Boolean(class CJigHelper *pJigHelper, const AcGePoint3d &posCur, const AcGePoint3d &posLast)>

/**
 * @class   CJigHelper
 * @brief   ����ͨ��jig������
 * @author  Gergul
 * @date    2018/10/29
 * Note:    
 */
class CJigHelper :
	public AcEdJig
{
public:
	CJigHelper(void);
	virtual ~CJigHelper(void);

public:
	/**
	 * @brief   ���ø���jigʵ�庯��
	 * @param   pFunc - ���º���
	 * @author  Gergul
	 * @date    2018/10/29
	 * Note:    
	 */
	void SetUpdateJigFunc(FUNC_UPDATE_JIG pFunc);

	/**
	 * @brief   �����Ա��������Ϊjig��Update����
	 * @param   ClassFunc - ���Ա���������磺CClass::UpdateJig
	 * @param   pClassObj - Update�������ڵ����������ΪCClass��һ���Ϊthis
	 * @param   pJigHelper - jig����ָ��
	 * @author  Gergul
	 * @date    2018/10/29
	 * Note:    �˺�Ϊ����SetUpdateJigFunc����ʹ��
	 */
#define SetUpdateClassFunc(ClassFunc, pClassObj, pJigHelper) \
	(pJigHelper)->SetUpdateJigFunc(std::bind(&ClassFunc, (pClassObj), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	 /**
	  * @brief   �ѷ����Ա�������ྲ̬��Ա��������Ϊjig��Update����
	  * @param   GeneralFunc - ȫ�ֻ����Ա�����������磺UpdateJig
	  * @param   pJigHelper - jigHelper����ָ��
	  * @author  Gergul
	  * @date    2018/10/29
	  * Note:    �˺�Ϊ����SetUpdateJigFunc����ʹ��
	  */
#define SetUpdateFunc(GeneralFunc, pJigHelper) \
	(pJigHelper)->SetUpdateJigFunc(std::bind(&GeneralFunc, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	/**
	 * @brief   ����jig����
	 * @param   ptOrigin - ����
	 * @author  Gergul
	 * @date    2018/10/29
	 * Note:    
	 */
	void SetBasePoint(const AcGePoint3d &ptOrigin);

	/**
	 * @brief   ȡ������jig����
	 * @author  Gergul
	 * @date    2018/10/29
	 * Note:    ���patʹ��
	 */
	void UnSetBasePoint();
	
	/**
	* @brief   ��û���
	* @author  Gergul
	* @date    2018/10/29
	* @return  ���ػ���
	* Note:
	*/
	const AcGePoint3d& GetBasePoint() const { return m_posBase; }

	/**
	 * @brief   �����Ƿ���������
	 * @param   bPat - �Ƿ�����Ϊ����ģʽ
	 * @author  Gergul
	 * @date    2018/10/29
	 * Note:    
	 */
	void SetPat(bool bPat);
	
	/**
	 * @brief   ���ͼ��ʵ��
	 * @param   pEnt - ͼ��ʵ��(ʵ����Ҫ��AcDb::kForWrite�ķ�ʽ��)
	 * @author  Gergul
	 * @date    2018/10/29
	 * Note:    
	 */
	void RegisterAsJigEntity(AcDbEntity *pEnt);

	/**
	* @brief   �������ͼ��ʵ��
	* @param   vctEnts - ͼ��ʵ�弯��(ʵ����Ҫ��AcDb::kForWrite�ķ�ʽ��)
	* @author  Gergul
	* @date    2018/10/29
	* Note:
	*/
	void RegisterAsJigEntity(std::vector<AcDbEntity *> &vctEnts);
	
	/**
	 * @brief   ����ע���ͼ��ʵ��
	 * @param   pEnt - Ҫ������ʵ��
	 * @author  Gergul
	 * @date    2018/10/29
	 * Note:    �����رգ���Ҫ���йر�
	 */
	void UnregisterJigEntity(AcDbEntity *pEnt);

	/**
	* @brief   ��������ע���ͼ��ʵ��
	* @param   vctEnts - Ҫ������ʵ�弯��
	* @author  Gergul
	* @date    2018/10/29
	* Note:    �����رգ���Ҫ���йر�
	*/
	void UnregisterJigEntity(std::vector<AcDbEntity *> &vctEnts);
	
	/**
	* @brief   ����ע��ȫ��JIGʵ��
	* @author  Gergul
	* @date    2018/10/29
	* Note:    �����رգ���Ҫ���йر�
	*/
	void UnregisterAllJigEntity();

	//startJig����ֵ
	typedef enum
	{
		RET_POINT,	//��
		RET_STRING,	//�ַ���
		RET_CANCEL,	//ȡ��
		RET_STOP,	//ֹͣ�����л�DWG��ʱ��
	} RESULT;

	/**
	 * @brief   ��ʼjigЧ��
	 * @author  Gergul
	 * @date    2018/10/29
	 * @return  ��jig�������������Ľ��
	 * Note:    
	 */
	CJigHelper::RESULT startJig();

	/**
	 * @brief   ����ַ���
	 * @author  Gergul
	 * @date    2018/10/29
	 * @return  ���startJig����RET_POINTʱ��ʹ�ô˺�������������ַ���
	 * Note:    
	 */
	const ACHAR *GetStringResult() const { return (ACHAR *)m_str; }
	
	/**
	* @brief   ��õ�ǰ��
	* @author  Gergul
	* @date    2018/10/29
	* @return  ���startJig����RET_STRINGʱ��ʹ�ô˺�����������ĵ�
	* Note:
	*/
	const AcGePoint3d &GetPosition() const { return m_posCur; }

	/**
	 * @brief   ǿ����ֹjig
	 * @author  Gergul
	 * @date    2018/10/29
	 * @return  
	 * Note:    �˳�jigЧ��
	 */
	void cancel() { m_bCanecl = true; }

	/**
	 * @brief   ���ͼ��ʵ������ʵ��
	 * @author  Gergul
	 * @date    2018/10/30
	 * @return  
	 * Note:    
	 */
	CSDBDumyJigEntity* GetJigEntity() { return &m_DumyJigEnt; }

protected:
	/**
	 * @brief   ȱʡ��Update����
	 * @param   posCur - ��ǰ��
	 * @param   posLast - ��һ�ν���UpdateJig�ĵ�
	 * @author  Gergul
	 * @date    2018/10/29
	 * @return  
	 * Note:    
	 */
	Adesk::Boolean CALLBACK UpdateJig(class CJigHelper *pJigHelper, const AcGePoint3d &posCur, const AcGePoint3d &posLast);

protected:
	//- AcEdJig overrides
	//- input sampler
	virtual AcEdJig::DragStatus sampler();
	//- jigged entity update
	virtual Adesk::Boolean update();
	//- jigged entity pointer return
	virtual AcDbEntity *entity() const;

protected:
	//- Entity being jigged
	CSDBDumyJigEntity m_DumyJigEnt;

	AcGePoint3d m_posLast;//ǰһ��λ��

	AcGePoint3d m_posCur;//��ǰλ��

	bool m_bHasSetBasePos;//�Ƿ��Ѿ������˻���
	AcGePoint3d m_posBase;//����

	ACHAR m_str[2049];	//���ܽ�����ַ���

	FUNC_UPDATE_JIG m_funcUpdateJig;//����jigʵ�庯��

	bool m_bPat;	//�Ƿ���������
	bool m_bCanecl;	//�û��Ƿ���ֹ
};
