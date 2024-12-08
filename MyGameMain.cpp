#include "MyGameMain.h"

//��������
TaskFlag			actTask, nextTask;

//-----------------------------------------------------------------------------
//�ʱ�ȭó��
//���Ӱ��� : ���α׷��⵿��1ȸ�����(��������غ�����)
//-----------------------------------------------------------------------------
void  MyGameMain_Initialize()
{
	//Ű�������Է����޴¿�����Ʈ������
	//�Ƴ��α׽�ƽL
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

	//�����е����Է����޴¿�����Ʈ������
	XI::KeyDatas_GP	but = {
	{ XI::RGP::B01, XI::VGP::B1 },{ XI::RGP::B02, XI::VGP::B2 },
	{ XI::RGP::B03, XI::VGP::B3 },{ XI::RGP::B04, XI::VGP::B4 },
	{ XI::RGP::B05, XI::VGP::L1 },{ XI::RGP::B06, XI::VGP::R1 },
	{ XI::RGP::B07, XI::VGP::SE },{ XI::RGP::B08, XI::VGP::ST },
	{ XI::RGP::B09, XI::VGP::L3 },{ XI::RGP::B10, XI::VGP::R3 },
	};
	auto wgp = XI::GamePad::CreateGP(0, but);
	//Ű����Ͱ����е�������
	XI::GamePad::Link(ge->in1, wgp);

	ge->in2 = XI::GamePad::CreateGP(1, but);
	ge->in3 = XI::GamePad::CreateGP(2, but);
	ge->in4 = XI::GamePad::CreateGP(3, but);
	ge->mouse = XI::Mouse::Create(2, 2);

	actTask = TaskFlag::Non;	//�ʱ���´½��������½�ũ����ȿȭ
	nextTask = TaskFlag::Title;	//�������½�ũ��Ÿ��Ʋ���ϴ°�����ó����Ÿ��Ʋ�̽���
}
//-----------------------------------------------------------------------------
//�ܺ����Ϸκ���
namespace  Title {//Ÿ��Ʋ�½�ũ
	extern  void Initialize();
	extern TaskFlag UpDate();
	extern  void Render();
	extern  void Finalize();
}
namespace  Game {//���Ӻ����½�ũ
	extern  void  Initialize();
	extern  TaskFlag  UpDate();
	extern  void  Render();
	extern  void  Finalize();
}
//�����ʿ信�����߰�
namespace  Ending {//���Ӻ����½�ũ
	extern  void  Initialize();
	extern  TaskFlag  UpDate();
	extern  void  Render();
	extern  void  Finalize();
}
//-----------------------------------------------------------------------------
//�ع�ó��
//��ɰ���: ���α׷� ����ÿ� 1ȸ����ȴ�(��������ع��� ����)
//-----------------------------------------------------------------------------
void  MyGameMain_Finalize()
{
	//����������䱸�Ȱ����
	//���ݽ��������½�ũ������ó�����ҷ��´�
	switch (actTask) {
	case TaskFlag::Title:	Title::Finalize();	break;
	case TaskFlag::Game:	Game::Finalize();	break;
		//�����ʿ信�����߰�
	case TaskFlag::Ending:	Ending::Finalize();	break;
	}

	ge->in1.reset();
	ge->in2.reset();
	ge->in3.reset();
	ge->in4.reset();
	ge->mouse.reset();
}
//-----------------------------------------------------------------------------
//������Ʈó��
//��ɰ��� : ������ 1�����ӿ� ���� ó��
//-----------------------------------------------------------------------------
void  MyGameMain_UpDate()
{
	//�����ǽ����ϴ��½�ũ��, �������½�ũ����ġ��������
	if (actTask != nextTask) {
		//���ݽ��������½�ũ������ó�����ҷ��´�
		switch (actTask) {
		case TaskFlag::Title:		Title::Finalize();	break;
		case TaskFlag::Game:		Game::Finalize();	break;
			//�����ʿ信�����߰�
		case TaskFlag::Ending:		Ending::Finalize();	break;
		}
		//�������½�ũ���̵�
		actTask = nextTask;
		//�������½�ũ���ʱ�ȭó�����ҷ��´�
		switch (actTask) {
		case TaskFlag::Title:		Title::Initialize();	break;
		case TaskFlag::Game:		Game::Initialize();		break;
		case TaskFlag::Ending:		Ending::Initialize();	break;
			//�����ʿ信�����߰�
		}
	}
	//�������½�ũ�ǽ���, ����ó�����ҷ��´�
	switch (actTask) {
	case TaskFlag::Title:		nextTask = Title::UpDate();		break;
	case TaskFlag::Game:		nextTask = Game::UpDate();		break;
		//�����ʿ信�����߰�
	case TaskFlag::Ending:		nextTask = Ending::UpDate();	break;
	}
}
//-----------------------------------------------------------------------------
//������ó��
//��ɰ��� : ������ 1�����ӿ� ���� ǥ��ó��
//-----------------------------------------------------------------------------
void  MyGameMain_Render2D()
{
	switch (actTask) {
	case TaskFlag::Title:		Title::Render();	break;
	case TaskFlag::Game:		Game::Render();		break;
		//���� �ʿ信 ���� �߰�
	case TaskFlag::Ending:		Ending::Render();		break;
	}
}
