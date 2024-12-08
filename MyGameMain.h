#pragma once
#include "MyPG.h"

extern  void  MyGameMain_Finalize( );
extern  void  MyGameMain_Initialize( );
extern  void  MyGameMain_UpDate( );
extern  void  MyGameMain_Render2D( );

enum class TaskFlag
{
	Non,		//태스크가 미선택상태
	Title,		//타이틀
	Game,		//게임본편

	//이하는 필요에 따라 추가
	UpDate,
	Ending
};
