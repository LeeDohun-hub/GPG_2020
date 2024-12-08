#pragma once
#include "GameEngine_Ver3_83.h"
#include <fstream>
#include <sstream>

namespace MyPG
{
    class Camera
    {
    public:
        Camera() { }
        Camera(
            const ML::Vec3& tg_,    // Target position
            const ML::Vec3& pos_,   // Camera position
            const ML::Vec3& up_,    // Up direction
            float              fov_,   // Field of view
            float              np_,    // Near plane
            float              fp_,    // Far plane
            float              asp_);  // Aspect ratio
    public:
        ML::Vec3 target;         // Target position
        ML::Vec3 pos;            // Camera position
        ML::Vec3 up;             // Up direction
        float fov;               // Field of view
        float nearPlane;        // Near plane
        float forePlane;        // Far plane
        float aspect;           // Aspect ratio
        ML::Mat4x4  matView, matProj;
        ~Camera();
        using SP = shared_ptr<Camera>;
        static SP Create(
            const ML::Vec3& tg_,    // Target position
            const ML::Vec3& pos_,   // Camera position
            const ML::Vec3& up_,    // Up direction
            float              fov_,   // Field of view
            float              np_,    // Near plane
            float              fp_,    // Far plane
            float              asp_);  // Aspect ratio
        void UpDate();
    };

    class MyGameEngine : public GameEngine
    {
    public:
        MyGameEngine();
        bool Initialize(HWND wnd_);
        ~MyGameEngine();
        void UpDate();

        void Set2DRenderState(DWORD l_);
        void Set3DRenderState(DWORD l_);

        MyPG::Camera::SP    camera[4];  // Camera instances

        XI::Mouse::SP  mouse;
        XI::GamePad::SP  in1, in2, in3, in4;  // Gamepad instances
    };
}

extern MyPG::MyGameEngine* ge;
