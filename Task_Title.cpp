#include "MyPG.h"
#include "MyGameMain.h"


//Ÿ��Ʋȭ��
namespace Title
{
	//���Ӻ���
	int logoPosY;
	DG::Image::SP img;

	//---------------------------------------------------------
	//�ʱ�ȭó��
	//��ɰ���: ���α׷��⵿�ÿ�1ȸ����ȴ�(��������غ�����)
	//---------------------------------------------------------
	void Initialize()
	{
		img = DG::Image::Create("./data/image/Title.bmp");
		logoPosY = -270; //Ÿ��Ʋ�������ʱ���ġ��ȭ��ܺο���ġ
	}
	//---------------------------------------------------------
	//�ع�ó��
	//��ɰ���: ���α׷�����ÿ�1ȸ����(��������ع���ó��)
	//---------------------------------------------------------
	void Finalize()
	{
		img.reset();
	}
	//---------------------------------------------------------
	//����ó��
	//��ɰ���: ������1�����ӿ��ش��ϴ�ó��
	//---------------------------------------------------------
	TaskFlag UpDate()
	{
		auto inp = ge->in1->GetState();
		logoPosY += 9;
		if (logoPosY > 0) { logoPosY = 0; }
		//logoPosY = min(logoPosY + 9, 0);

		TaskFlag rtv = TaskFlag::Title;//�ϴ��������½�ũ������
		if (logoPosY >= 0) {
			if (true == inp.ST.down) {
				rtv = TaskFlag::Game; //�������½�ũ�����Ӻ�����
			}
		}
		return rtv;
	}
	//------------------------------------------------------------
	//������ó��
	//��ɰ���: ������ 1�����ӿ� ���ϴ� ǥ��ó��
	//---------------------------------------------------------
	void Render()
	{
		ML::Box2D draw(0, 0, 480, 270);
		draw.Offset(0, logoPosY);
		ML::Box2D src(0, 0, 240, 135);

		img->Draw(draw, src);
	}
}