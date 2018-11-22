#pragma once

/* <editor-fold desc="MIT License">

Copyright(c) 2018 Robert Osfield

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

</editor-fold> */

#define VK_USE_PLATFORM_WIN32_KHR

#include <vsg/viewer/Window.h>

#include <unordered_map>

#include <windows.h>
#include <windowsx.h>

namespace vsg
{
    extern vsg::Names getInstanceExtensions();

    class Win32_Window : public vsg::Window
    {
    public:

        Win32_Window() = delete;
        Win32_Window(const Win32_Window&) = delete;
        Win32_Window operator = (const Win32_Window &) = delete;

        using Result = vsg::Result<vsg::Window, VkResult, VK_SUCCESS>;
        static Result create(const Traits& traits, bool debugLayer = false, bool apiDumpLayer = false, vsg::AllocationCallbacks* allocator = nullptr);

        virtual bool valid() const { return _window; /*&& !glfwWindowShouldClose(_window);*/ }

        virtual bool pollEvents();

        virtual bool resized() const;

        virtual void resize();

        operator HWND () { return _window; }
        operator const HWND () const { return _window; }

        LRESULT handleWin32Messages(UINT msg, WPARAM wParam, LPARAM lParam);

        // use these to keep track of window handles mapped to Win32_Windows
        static void registerWindow(HWND hwnd, Win32_Window* window);
        static void unregisterWindow(HWND hwnd);

        static Win32_Window* getWindow(HWND hwnd);

    protected:
        virtual ~Win32_Window();

        Win32_Window (HWND window, vsg::Instance* instance, vsg::Surface* surface, vsg::PhysicalDevice* physicalDevice, vsg::Device* device, vsg::RenderPass* renderPass, bool debugLayersEnabled);

        HWND _window;

        static std::unordered_map<HWND, Win32_Window*> s_registeredWindows;
    };

} // namespace vsg

