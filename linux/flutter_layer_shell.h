//
// Created by luca on 5/9/23.
//

#ifndef DESKTOP_MULTI_WINDOW_FLUTTER_LAYER_SHELL_H
#define DESKTOP_MULTI_WINDOW_FLUTTER_LAYER_SHELL_H

#include <cstdint>
#include <memory>
#include <cmath>

#include <gtk/gtk.h>
#include "flutter_window.h"
#include "base_flutter_window.h"

class FlutterLayerShellCallback {

public:
    virtual void OnWindowClose(int64_t id) = 0;

    virtual void OnWindowDestroy(int64_t id) = 0;

};

class FlutterLayerShell : public BaseFlutterWindow {
public:
    FlutterLayerShell(int64_t id, const std::string &args, const std::shared_ptr <FlutterLayerShellCallback> &callback);

    ~FlutterLayerShell() override;

    WindowChannel *GetWindowChannel() override;

protected:

    GtkWindow *GetWindow() override {
        return GTK_WINDOW(window_);
    }

private:

    std::weak_ptr <FlutterLayerShellCallback> callback_;

    int64_t id_;

    GtkWidget *window_ = nullptr;

    std::unique_ptr <WindowChannel> window_channel_;
};


#endif //DESKTOP_MULTI_WINDOW_FLUTTER_LAYER_SHELL_H
