#pragma once
#include "MyPG.h"

extern  void  MyGameMain_Finalize( );
extern  void  MyGameMain_Initialize( );
extern  void  MyGameMain_UpDate( );
extern  void  MyGameMain_Render2D( );

enum class TaskFlag
{
	Non,		//�½�ũ�� �̼��û���
	Title,		//Ÿ��Ʋ
	Game,		//���Ӻ���

	//���ϴ� �ʿ信 ���� �߰�
	UpDate,
	Ending
};
