#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Media::Animation;
using namespace Microsoft::UI::Xaml::Media;
using namespace Windows::Foundation;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::BgLabelControlApp::implementation
{
    int32_t MainWindow::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainWindow::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void MainWindow::myButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        myButton().Content(box_value(L"Animating..."));

        // 1. Storyboard 및 Animation 객체 초기화 (최초 1회만)
        if (m_storyboard == nullptr)
        {
            m_storyboard = Storyboard();

            // --- 1-1. DoubleAnimation (회전) 설정 ---
            m_doubleAnimation = DoubleAnimation();

            auto rotationTimeSpan = winrt::Windows::Foundation::TimeSpan{ std::chrono::milliseconds{ 2000 } };
            m_doubleAnimation.Duration(Microsoft::UI::Xaml::Duration{ rotationTimeSpan }); // 2초
            m_doubleAnimation.From(0.0);
            m_doubleAnimation.To(360.0);
            m_doubleAnimation.RepeatBehavior(RepeatBehaviorHelper::Forever());

            Storyboard::SetTarget(m_doubleAnimation, ControlRotateTransform());
            Storyboard::SetTargetProperty(m_doubleAnimation, L"Angle");

            // Storyboard에 회전 애니메이션 추가
            m_storyboard.Children().Append(m_doubleAnimation);


            // --- 1-2. DoubleAnimation (크기 조절) 설정: 커졌다 작아졌다 하는 애니메이션 추가 ---
            auto scaleTimeSpan = winrt::Windows::Foundation::TimeSpan{ std::chrono::milliseconds{ 1000 } };

            // X축 스케일 애니메이션
            m_scaleXAnimation = DoubleAnimation();
            m_scaleXAnimation.Duration(Microsoft::UI::Xaml::Duration{ scaleTimeSpan }); // 1초
            m_scaleXAnimation.From(1.0); // 100% 크기에서 시작
            m_scaleXAnimation.To(1.5); // 150% 크기로 커짐
            m_scaleXAnimation.AutoReverse(true); // 커졌다가 다시 작아짐
            m_scaleXAnimation.RepeatBehavior(RepeatBehaviorHelper::Forever()); // 무한 반복

            // Y축 스케일 애니메이션
            m_scaleYAnimation = DoubleAnimation();
            m_scaleYAnimation.Duration(Microsoft::UI::Xaml::Duration{ scaleTimeSpan }); // 1초
            m_scaleYAnimation.From(1.0);
            m_scaleYAnimation.To(1.5);
            m_scaleYAnimation.AutoReverse(true);
            m_scaleYAnimation.RepeatBehavior(RepeatBehaviorHelper::Forever());

            // 스케일 애니메이션 대상 및 속성 설정
            // XAML에서 ControlScaleTransform이라는 이름으로 ScaleTransform을 찾아 지정합니다.
            Storyboard::SetTarget(m_scaleXAnimation, ControlScaleTransform());
            Storyboard::SetTargetProperty(m_scaleXAnimation, L"ScaleX");

            Storyboard::SetTarget(m_scaleYAnimation, ControlScaleTransform());
            Storyboard::SetTargetProperty(m_scaleYAnimation, L"ScaleY");

            // Storyboard에 스케일 애니메이션 추가
            m_storyboard.Children().Append(m_scaleXAnimation);
            m_storyboard.Children().Append(m_scaleYAnimation);


            // --- 1-3. ColorAnimation (배경색 변경) 설정 ---
            m_colorAnimation = ColorAnimation();

            // 배경색 브러시를 가져오거나 생성합니다. ColorAnimation은 SolidColorBrush의 'Color' 속성을 대상으로 합니다.
            winrt::Microsoft::UI::Xaml::Media::SolidColorBrush backgroundBrush{ nullptr };
            if (auto brush = MyBgControl().Background().try_as<winrt::Microsoft::UI::Xaml::Media::SolidColorBrush>())
            {
                backgroundBrush = brush;
            }
            else
            {
                // Background가 SolidColorBrush가 아니었다면, 새로 생성하여 적용
                backgroundBrush = winrt::Microsoft::UI::Xaml::Media::SolidColorBrush{ winrt::Microsoft::UI::Colors::Green() };
                MyBgControl().Background(backgroundBrush);
            }

            // 컬러 애니메이션 설정
            auto colorTimeSpan = winrt::Windows::Foundation::TimeSpan{ std::chrono::milliseconds{ 4000 } };
            m_colorAnimation.Duration(Microsoft::UI::Xaml::Duration{ colorTimeSpan }); // 4초
            m_colorAnimation.From(winrt::Microsoft::UI::Colors::Green()); // 시작 색상: 녹색
            m_colorAnimation.To(winrt::Microsoft::UI::Colors::Yellow());    // 끝 색상: 노란색
            m_colorAnimation.AutoReverse(true); // 애니메이션 반전 (노란색에서 다시 녹색으로)
            m_colorAnimation.RepeatBehavior(RepeatBehaviorHelper::Forever()); // 무한 반복

            // 컬러 애니메이션 대상 및 속성 설정
            Storyboard::SetTarget(m_colorAnimation, backgroundBrush);
            Storyboard::SetTargetProperty(m_colorAnimation, L"Color"); // SolidColorBrush의 Color 속성을 대상으로 지정

            // Storyboard에 컬러 애니메이션 추가
            m_storyboard.Children().Append(m_colorAnimation);
        }

        // 2. 애니메이션 시작 (이미 실행 중이라면 정지 후 다시 시작)
        m_storyboard.Stop();
        m_storyboard.Begin();
    }
}