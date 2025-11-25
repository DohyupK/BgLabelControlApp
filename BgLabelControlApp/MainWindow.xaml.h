#pragma once

#include "MainWindow.g.h"
#include "BgLabelControl.h"

// 필요한 헤더 추가
#include <winrt/Microsoft.UI.Xaml.Media.Animation.h>
#include <winrt/Microsoft.UI.Xaml.Media.h>
// TimeSpan 사용을 위한 네임스페이스 추가
#include <winrt/Windows.Foundation.h>

namespace winrt::BgLabelControlApp::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow()
        {
            // !!! 중요: XAML에 이름 붙인 요소(ControlRotateTransform, ControlScaleTransform 등)에 접근하려면
            // InitializeComponent()를 호출해야 합니다.
            InitializeComponent();
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void myButton_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);

    private:
        // 애니메이션 객체 선언
        winrt::Microsoft::UI::Xaml::Media::Animation::Storyboard m_storyboard{ nullptr };
        winrt::Microsoft::UI::Xaml::Media::Animation::DoubleAnimation m_doubleAnimation{ nullptr }; // 기존: 회전 애니메이션

        // 새로 추가된 크기 조절(Scale) 애니메이션
        winrt::Microsoft::UI::Xaml::Media::Animation::DoubleAnimation m_scaleXAnimation{ nullptr };
        winrt::Microsoft::UI::Xaml::Media::Animation::DoubleAnimation m_scaleYAnimation{ nullptr };

        // 기존 ColorAnimation 객체 선언
        winrt::Microsoft::UI::Xaml::Media::Animation::ColorAnimation m_colorAnimation{ nullptr };
    };
}

namespace winrt::BgLabelControlApp::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}