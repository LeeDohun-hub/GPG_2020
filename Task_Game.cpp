#include "MyPG.h"
#include "MyGameMain.h"

//게임본편
namespace Game
{
    //게임정보
    DG::Image::SP imgMapChip;
    int timeCnt;
    int chipState;
    struct MapData {
        int arr[8][15]; //가로8, 세로15, 
        ML::Box2D chip[25]; //칩의사짐을갖고오는 범위(사진을 둘러싸는단형)
    };

    void Map_Initialize(MapData& md_);
    bool Map_Load(MapData& md_, int n_);
    void Map_UpData(MapData& md_);
    void Map_Render(MapData& md_);

    MapData mapData; //형정의(설계도만들기)가 끝나면, 
    //변수선언을 진행, 맵용의 변수를 선언하고 있습니다
    //----------------------------------------
    //초기화처리
    //기능개요: 프로그램기동시에1회실행된다(소재등의준비를실행)
    //----------------------------------------
    void Initialize()
    {
        ge->dgi->EffectState().param.bgColor = ML::Color(1, 0, 1, 0);
        imgMapChip = DG::Image::Create("./data/image/MapChip01.bmp"); //배경
        //맵칩정보의 초기화
        Map_Initialize(mapData);
        Map_Load(mapData, 1);
        timeCnt = 0;
        chipState = 32;
    }

    //-----------------------------------------
    //해방처리
    //기능개요: 프로그램종료시에1회실행된다(소재등의해방을진행)
    //-----------------------------------------
    void Finalize()
    {
        imgMapChip.reset();
    }

    //-----------------------------------------
    //실행처리
    //기능개요 : 게임 1프레임에 달하는 처리
    //-----------------------------------------
    TaskFlag UpDate()
    {
        auto inp = ge->in1->GetState();
        Map_UpData(mapData);
        TaskFlag rtv = TaskFlag::Game; //일단현재의업무를지정
        // SE 버튼을 눌렀을 때 타이틀 화면으로 전환
        if (true == inp.SE.down) {
            rtv = TaskFlag::Title;
        }
        else if (true == inp.ST.down) {
            rtv = TaskFlag::Ending; //다음태스크를타이틀로
        }
        return rtv;
    }

    //----------------------------------------------------
    //렌더링처리
    //기능개요 : 게임1프레임에 달하는 표시처리
    //----------------------------------------------------
    void Render()
    {
        //배경묘화
        Map_Render(mapData);
    }

    void Map_UpData(MapData& md_)
    {
        timeCnt++;
        if (timeCnt >= 2)
        {
            chipState--; // chipState를 계속 증가시킴

            // chipState가 0에서 32 사이로 유지되도록 조정
            if (chipState <= 0) {
                chipState = 32; // 32 이상이 되면 다시 0으로 리셋
            }
            for (int y = 0; y < 8; ++y)
            {
                for (int x = 0; x < 15; ++x)
                {
                    if (md_.arr[y][x] == 16)
                    {
                        // 수직강
                        md_.chip[16] = ML::Box2D(0, (chipState + 64), 32, 32);
                    }
                    if (md_.arr[y][x] == 17)
                    {
                        // 수평강
                        md_.chip[17] = ML::Box2D((chipState+32), 64, 32, 32);
                    }
                }
            }
            timeCnt = 0;
        }
    }


    void Map_Render(MapData& md_)
    {
        //배경묘화
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
        //맵칩정보의 초기화
        for (int c = 0; c < 25; ++c) {
            int x = (c % 8);
            int y = (c / 8);
            md_.chip[c] = ML::Box2D(x * 32, y * 32, 32, 32);
        }
        //맵의 재로클리어
        for (int y = 0; y < 8; ++y)
        {
            for (int x = 0; x < 15; ++x) {
                md_.arr[y][x] = 0;
            }
        }
    }

    bool Map_Load(MapData& md_, int n_)
    {
        //현재는 가처리(실제로는 맵파일로부터 데이터를 읽습니다)
        //맵배열정보의 초기화
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
        //데이터의 복사
        for (int y = 0; y < 8; ++y)
        {
            for (int x = 0; x < 15; ++x) {
                md_.arr[y][x] = w_map[y][x];
            }
        }
        return true;
    }
} // namespace Game //