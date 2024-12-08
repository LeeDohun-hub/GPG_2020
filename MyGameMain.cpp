#include "MyGameMain.h"

//게임정보
TaskFlag			actTask, nextTask;

//-----------------------------------------------------------------------------
//초기화처리
//게임개요 : 프로그램기동시1회실행됨(소재등의준비를진행)
//-----------------------------------------------------------------------------
void  MyGameMain_Initialize()
{
	//키보드의입력을받는오브젝트를생성
	//아날로그스틱L
	XI::AnalogAxisKB	ls = { DIK_LEFT, DIK_RIGHT, DIK_UP, DIK_DOWN };
	XI::AnalogAxisKB	rs = { DIK_NUMPAD4, DIK_NUMPAD6, DIK_NUMPAD8, DIK_NUMPAD2 };
	XI::AnalogTriggerKB  tg = { DIK_E, DIK_R };
	XI::KeyDatas_KB	 key = {
	{ DIK_Z, XI::VGP::B1 },{ DIK_X, XI::VGP::B2 },{ DIK_C, XI::VGP::B3 },
	{ DIK_V, XI::VGP::B4 },{ DIK_A, XI::VGP::SE },{ DIK_S, XI::VGP::ST },
	{ DIK_Q, XI::VGP::L1 },{ DIK_W, XI::VGP::R1 },
	{ DIK_D, XI::VGP::L3 },{ DIK_NUMPAD5, XI::VGP::R3 },
	};
	ge->in1 = XI::GamePad::CreateKB(ls, rs, tg, key);

	//게임패드의입력을받는오브잭트를생성
	XI::KeyDatas_GP	but = {
	{ XI::RGP::B01, XI::VGP::B1 },{ XI::RGP::B02, XI::VGP::B2 },
	{ XI::RGP::B03, XI::VGP::B3 },{ XI::RGP::B04, XI::VGP::B4 },
	{ XI::RGP::B05, XI::VGP::L1 },{ XI::RGP::B06, XI::VGP::R1 },
	{ XI::RGP::B07, XI::VGP::SE },{ XI::RGP::B08, XI::VGP::ST },
	{ XI::RGP::B09, XI::VGP::L3 },{ XI::RGP::B10, XI::VGP::R3 },
	};
	auto wgp = XI::GamePad::CreateGP(0, but);
	//키보드와게임패드의통합
	XI::GamePad::Link(ge->in1, wgp);

	ge->in2 = XI::GamePad::CreateGP(1, but);
	ge->in3 = XI::GamePad::CreateGP(2, but);
	ge->in4 = XI::GamePad::CreateGP(3, but);
	ge->mouse = XI::Mouse::Create(2, 2);

	actTask = TaskFlag::Non;	//초기상태는실행중의태스크를무효화
	nextTask = TaskFlag::Title;	//다음의태스크를타이틀로하는것으로처음의타이틀이실행
}
//-----------------------------------------------------------------------------
//외부파일로부터
namespace  Title {//타이틀태스크
	extern  void Initialize();
	extern TaskFlag UpDate();
	extern  void Render();
	extern  void Finalize();
}
namespace  Game {//게임본편태스크
	extern  void  Initialize();
	extern  TaskFlag  UpDate();
	extern  void  Render();
	extern  void  Finalize();
}
//이하필요에따라추가
namespace  Ending {//게임본편태스크
	extern  void  Initialize();
	extern  TaskFlag  UpDate();
	extern  void  Render();
	extern  void  Finalize();
}
//-----------------------------------------------------------------------------
//해방처리
//기능개요: 프로그램 종료시에 1회실행된다(소재등의해방을 진행)
//-----------------------------------------------------------------------------
void  MyGameMain_Finalize()
{
	//도중의종료요구된경우대등
	//지금실행중의태스크의종료처리를불러온다
	switch (actTask) {
	case TaskFlag::Title:	Title::Finalize();	break;
	case TaskFlag::Game:	Game::Finalize();	break;
		//이하필요에따라추가
	case TaskFlag::Ending:	Ending::Finalize();	break;
	}

	ge->in1.reset();
	ge->in2.reset();
	ge->in3.reset();
	ge->in4.reset();
	ge->mouse.reset();
}
//-----------------------------------------------------------------------------
//업데이트처리
//기능개요 : 게임의 1프레임에 따른 처리
//-----------------------------------------------------------------------------
void  MyGameMain_UpDate()
{
	//다음의실행하는태스크는, 지금의태스크와일치하지않음
	if (actTask != nextTask) {
		//지금실행중의태스크의종료처리를불러온다
		switch (actTask) {
		case TaskFlag::Title:		Title::Finalize();	break;
		case TaskFlag::Game:		Game::Finalize();	break;
			//이하필요에따라추가
		case TaskFlag::Ending:		Ending::Finalize();	break;
		}
		//다음의태스크로이동
		actTask = nextTask;
		//다음의태스크의초기화처리를불러온다
		switch (actTask) {
		case TaskFlag::Title:		Title::Initialize();	break;
		case TaskFlag::Game:		Game::Initialize();		break;
		case TaskFlag::Ending:		Ending::Initialize();	break;
			//이하필요에따라추가
		}
	}
	//현재의태스크의실행, 갱신처리를불러온다
	switch (actTask) {
	case TaskFlag::Title:		nextTask = Title::UpDate();		break;
	case TaskFlag::Game:		nextTask = Game::UpDate();		break;
		//이하필요에따라추가
	case TaskFlag::Ending:		nextTask = Ending::UpDate();	break;
	}
}
//-----------------------------------------------------------------------------
//렌더링처리
//기능개요 : 게임의 1프레임에 대한 표시처리
//-----------------------------------------------------------------------------
void  MyGameMain_Render2D()
{
	switch (actTask) {
	case TaskFlag::Title:		Title::Render();	break;
	case TaskFlag::Game:		Game::Render();		break;
		//이하 필요에 따라 추가
	case TaskFlag::Ending:		Ending::Render();		break;
	}
}
