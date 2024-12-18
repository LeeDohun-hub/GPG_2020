#include "MyPG.h"
#include "MyGameMain.h"

//타이틀화면
namespace Ending
{
	//게임본편
	int logoPosY;
	DG::Image::SP img;

	//---------------------------------------------------------
	//초기화처리
	//기능개요: 프로그램기동시에1회실행된다(소재등의준비를진행)
	//---------------------------------------------------------
	void Initialize()
	{
		img = DG::Image::Create("./data/image/Ending.bmp");
		logoPosY = 270; //타이틀사진의초기위치를화면외부에배치
	}
	//---------------------------------------------------------
	//해방처리
	//기능개요: 프로그램종료시에1회실행(소재등의해방을처리)
	//---------------------------------------------------------
	void Finalize()
	{
		img.reset();
	}
	//---------------------------------------------------------
	//갱신처리
	//기능개요: 게임의1프레임에해당하는처리
	//---------------------------------------------------------
	TaskFlag UpDate()
	{
		auto inp = ge->in1->GetState();
		logoPosY -= 9;
		if (logoPosY < 0) { logoPosY = 0; }
		//logoPosY = min(logoPosY + 9, 0);

		TaskFlag rtv = TaskFlag::Ending;//일단현재의태스크를지정
		if (logoPosY <= 0) {
			if (true == inp.ST.down) {
				rtv = TaskFlag::Title; //다음의태스크를게임본편에
			}
		}
		return rtv;
	}
	//------------------------------------------------------------
	//렌더링처리
	//기능개요: 게임의 1프레임에 달하는 표시처리
	//---------------------------------------------------------
	void Render()
	{
		ML::Box2D draw(0, 0, 480, 270);
		draw.Offset(0, logoPosY);
		ML::Box2D src(0, 0, 240, 135);

		img->Draw(draw, src);
	}
}
