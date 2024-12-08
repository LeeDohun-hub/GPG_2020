#include "MyPG.h"
#include "MyGameMain.h"

//���Ӻ���
namespace Game
{
    //��������
    DG::Image::SP imgMapChip;
    int timeCnt;
    int chipState;
    struct MapData {
        int arr[8][15]; //����8, ����15, 
        ML::Box2D chip[25]; //Ĩ�ǻ������������ ����(������ �ѷ��δ´���)
    };

    void Map_Initialize(MapData& md_);
    bool Map_Load(MapData& md_, int n_);
    void Map_UpData(MapData& md_);
    void Map_Render(MapData& md_);

    MapData mapData; //������(���赵�����)�� ������, 
    //���������� ����, �ʿ��� ������ �����ϰ� �ֽ��ϴ�
    //----------------------------------------
    //�ʱ�ȭó��
    //��ɰ���: ���α׷��⵿�ÿ�1ȸ����ȴ�(��������غ񸦽���)
    //----------------------------------------
    void Initialize()
    {
        ge->dgi->EffectState().param.bgColor = ML::Color(1, 0, 1, 0);
        imgMapChip = DG::Image::Create("./data/image/MapChip01.bmp"); //���
        //��Ĩ������ �ʱ�ȭ
        Map_Initialize(mapData);
        Map_Load(mapData, 1);
        timeCnt = 0;
        chipState = 32;
    }

    //-----------------------------------------
    //�ع�ó��
    //��ɰ���: ���α׷�����ÿ�1ȸ����ȴ�(��������ع�������)
    //-----------------------------------------
    void Finalize()
    {
        imgMapChip.reset();
    }

    //-----------------------------------------
    //����ó��
    //��ɰ��� : ���� 1�����ӿ� ���ϴ� ó��
    //-----------------------------------------
    TaskFlag UpDate()
    {
        auto inp = ge->in1->GetState();
        Map_UpData(mapData);
        TaskFlag rtv = TaskFlag::Game; //�ϴ������Ǿ���������
        // SE ��ư�� ������ �� Ÿ��Ʋ ȭ������ ��ȯ
        if (true == inp.SE.down) {
            rtv = TaskFlag::Title;
        }
        else if (true == inp.ST.down) {
            rtv = TaskFlag::Ending; //�����½�ũ��Ÿ��Ʋ��
        }
        return rtv;
    }

    //----------------------------------------------------
    //������ó��
    //��ɰ��� : ����1�����ӿ� ���ϴ� ǥ��ó��
    //----------------------------------------------------
    void Render()
    {
        //��湦ȭ
        Map_Render(mapData);
    }

    void Map_UpData(MapData& md_)
    {
        timeCnt++;
        if (timeCnt >= 2)
        {
            chipState--; // chipState�� ��� ������Ŵ

            // chipState�� 0���� 32 ���̷� �����ǵ��� ����
            if (chipState <= 0) {
                chipState = 32; // 32 �̻��� �Ǹ� �ٽ� 0���� ����
            }
            for (int y = 0; y < 8; ++y)
            {
                for (int x = 0; x < 15; ++x)
                {
                    if (md_.arr[y][x] == 16)
                    {
                        // ������
                        md_.chip[16] = ML::Box2D(0, (chipState + 64), 32, 32);
                    }
                    if (md_.arr[y][x] == 17)
                    {
                        // ����
                        md_.chip[17] = ML::Box2D((chipState+32), 64, 32, 32);
                    }
                }
            }
            timeCnt = 0;
        }
    }


    void Map_Render(MapData& md_)
    {
        //��湦ȭ
        for (int y = 0; y < 8; ++y) {
            for (int x = 0; x < 15; ++x) {
                ML::Box2D draw(0, 0, 32, 32);
                draw.Offset(x * 32, y * 32);
                imgMapChip->Draw(draw, md_.chip[md_.arr[y][x]]);
            }
        }
    }

    void Map_Initialize(MapData& md_)
    {
        //��Ĩ������ �ʱ�ȭ
        for (int c = 0; c < 25; ++c) {
            int x = (c % 8);
            int y = (c / 8);
            md_.chip[c] = ML::Box2D(x * 32, y * 32, 32, 32);
        }
        //���� ���Ŭ����
        for (int y = 0; y < 8; ++y)
        {
            for (int x = 0; x < 15; ++x) {
                md_.arr[y][x] = 0;
            }
        }
    }

    bool Map_Load(MapData& md_, int n_)
    {
        //����� ��ó��(�����δ� �����Ϸκ��� �����͸� �н��ϴ�)
        //�ʹ迭������ �ʱ�ȭ
        int w_map[8][15] = {
            {8, 8, 8, 8, 16, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8},
            {0, 1, 0, 0, 16, 0, 8, 0, 0, 0, 1, 0, 0, 2, 0},
            {0, 0, 0, 0, 16, 0, 8, 0, 0, 3, 0, 3, 0, 0, 8},
            {8, 0, 0, 0, 17, 17, 8, 17, 17, 16, 0, 0, 0, 0, 8},
            {8, 0, 0, 8, 8, 0, 8, 0, 0, 16, 8, 8, 0, 0, 8},
            {8, 0, 0, 8, 1, 0, 0, 0, 0, 16, 8, 0, 0, 0, 0},
            {8, 3, 0, 8, 0, 0, 0, 0, 0, 16, 8, 0, 0, 1, 0},
            {8, 8, 0, 8, 8, 8, 8, 8, 8, 16, 8, 8, 8, 0, 8},
        };
        //�������� ����
        for (int y = 0; y < 8; ++y)
        {
            for (int x = 0; x < 15; ++x) {
                md_.arr[y][x] = w_map[y][x];
            }
        }
        return true;
    }
} // namespace Game //